#pragma once


#include "ExchangeData.h"

#include <string>


class DatasetGenerator
{
private:
public:

	virtual ~DatasetGenerator() {};

	virtual ExchangeData*		Generate		()	= 0;
};

