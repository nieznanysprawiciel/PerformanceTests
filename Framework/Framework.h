#pragma once


#include "Observable.h"
#include "ExchangeData.h"
#include "DatasetGenerator.h"

#include <vector>
#include <map>


struct Result
{
	std::string			DatasetName;
	std::string			ObservableName;
	long long			Millis;
};

class Framework;

class Framework
{
private:

	std::vector< Observable* >			m_observables;
	std::vector< ExchangeData* >		m_datasets;
	std::vector< DatasetGenerator* >	m_dataGenerator;

	std::map< Observable*, std::vector< Result > >	m_results;

public:
	Framework();
	~Framework();

	int			AddObservable	( Observable* observable );
	int			AddDataSet		( ExchangeData* dataset );
	int			AddDataGenerator( DatasetGenerator* dataset );

	void		PerformTests	();

private:

	void		IntertestBreak	();
	void		SingleLoop		( ExchangeData* );
	void		PrintResults	();
	void		PrintPreHeader	();

public:
	static Framework& Get()
	{
		static Framework framework;
		return framework;
	}

};

