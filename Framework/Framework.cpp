#include "Framework.h"

#include <iostream>
#include <chrono>
#include <iomanip>



Framework::Framework()
{}


Framework::~Framework()
{
	for( auto obs : m_datasets )
		delete obs;
	for( auto obs : m_dataGenerator )
		delete obs;
	for( auto obs : m_observables )
		delete obs;
}

/**@brief */
int Framework::AddObservable( Observable* observable )
{
	m_observables.push_back( observable );
	return 0;
}

/**@brief */
int Framework::AddDataSet( ExchangeData* dataset )
{
	m_datasets.push_back( dataset );
	return 0;
}

/**@brief */
int Framework::AddDataGenerator( DatasetGenerator* dataset )
{
	m_dataGenerator.push_back( dataset );
	return 0;
}

/**@brief */
void Framework::PerformTests()
{
	PrintPreHeader();

	for( auto dataset : m_datasets )
	{
		SingleLoop( dataset );
	}

	for( auto generator : m_dataGenerator )
	{
		ExchangeData* dataset = generator->Generate();
		SingleLoop( dataset );
		delete dataset;
	}

	PrintResults();
}

/**@brief */
void Framework::SingleLoop( ExchangeData* dataset )
{
	for( auto observable : m_observables )
	{
		observable->InitData( dataset );

		auto timeBegin = std::chrono::steady_clock::now();
		observable->ObservableFunction();
		auto period = std::chrono::steady_clock::now() - timeBegin;
	
		observable->Deinit();

		std::cout << "*";

		Result result;
		result.DatasetName = dataset->DatasetName;
		result.ObservableName = observable->GetTestName();
		result.Millis = std::chrono::duration_cast<std::chrono::milliseconds>( period ).count();

		m_results[ observable ].push_back( result );

		IntertestBreak();
	}

	std::cout << std::endl;;
}

const char separator    = ' ';
template<typename T> void printElement(T t, const int& width)
{
    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
}

#define ENDLINE std::cout << std::endl;

void Framework::PrintPreHeader	()
{
	std::cout << "Observables:";
	ENDLINE
	ENDLINE
	for( auto observable : m_observables )
	{
		std::cout << observable->GetTestName();
		std::cout << std::endl;
	}
	ENDLINE
}

void Framework::PrintResults()
{
	int numObservations = m_dataGenerator.size() + m_datasets.size();
	int maxObservableSize = 0;

	for( auto observable : m_observables )
	{
		if( (int)observable->GetTestName().size() > maxObservableSize )
			maxObservableSize = (int)observable->GetTestName().size();
	}

	auto beginIter = m_results.begin();
	for( auto& result : beginIter->second )
	{
		if( (int)result.DatasetName.size() > maxObservableSize )
			maxObservableSize = (int)result.DatasetName.size();
	}

	maxObservableSize += 4;		// Add some space between observables.

	// Header
	ENDLINE
	printElement( "Dataset Name", maxObservableSize );
	for( auto& result : m_results )
	{
		printElement( result.first->GetTestName(), maxObservableSize );
	}
	ENDLINE

	// Rows
	for( int i = 0; i < numObservations; ++i )
	{
		auto beginIter = m_results.begin();
		printElement( beginIter->second[ i ].DatasetName, maxObservableSize );

		for( auto& result : m_results )
		{
			printElement( result.second[ i ].Millis, maxObservableSize );
			//printElement( result.second[ i ].DatasetName, maxObservableSize );
			//printElement( result.second[ i ].ObservableName, maxObservableSize );
		}

		ENDLINE
	}

	std::cout << "Enter eny kay to exit";
	char sign;
	std::cin >> sign;
}


/**@brief Tutaj powinno siê zrobiæ coœ, ¿eby */
void Framework::IntertestBreak()
{ }
