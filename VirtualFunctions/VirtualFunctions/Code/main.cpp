#include <iostream>
#include <chrono>
#include <random>


#include "DerivedClass1.h"
#include "DerivedClass2.h"

#include <vector>

const int numObjects = 4000;
const int numLoops = 1000;


int main()
{
	std::vector< BaseClass* >	objects;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis( 0, 2 );


	for( int i = 0; i < numObjects; i++ )
	{
		int classId = dis( gen );
		if( classId == 0 )
			objects.push_back( new BaseClass );
		else if( classId == 1 )
			objects.push_back( new DerivedClass1 );
		else if( classId == 2 )
			objects.push_back( new DerivedClass2 );
	}

//====================================================================================//
//				VirtualFunction
//====================================================================================//
	auto timeBegin = std::chrono::high_resolution_clock::now();

	float result = 0;
	for( int i = 0; i < numLoops; i++ )
	{
		for( auto obj : objects )
			result += obj->VirtualFunction( i, 0.55f );
	}

	auto period = std::chrono::high_resolution_clock::now() - timeBegin;
	std::cout << "Execution time [VirtualFunction]: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;
	std::cout << result << std::endl;

//====================================================================================//
//				NormalFunction
//====================================================================================//
	timeBegin = std::chrono::high_resolution_clock::now();

	result = 0;
	for( int i = 0; i < numLoops; i++ )
	{
		for( auto obj : objects )
			result += obj->NormalFunction( i, 0.55f );
	}

	period = std::chrono::high_resolution_clock::now() - timeBegin;
	std::cout << "Execution time [NormalFunction]: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;
	std::cout << result << std::endl;

//====================================================================================//
//				InlineFunction
//====================================================================================//
	timeBegin = std::chrono::high_resolution_clock::now();

	result = 0;
	for( int i = 0; i < numLoops; i++ )
	{
		for( auto obj : objects )
			result += obj->InlineFunction( i, 0.55f );
	}

	period = std::chrono::high_resolution_clock::now() - timeBegin;
	std::cout << "Execution time [InlineFunction]: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;
	std::cout << result << std::endl;


	// End
	char sign;
	std::cin >> sign;
	return 0;

	for( auto obj : objects )
		delete obj;
}