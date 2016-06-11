#pragma once

#include "ExchangeData.h"

#include <string>


class Observable
{
private:

public:
	Observable() = default;
	virtual ~Observable() {};

	virtual void			InitData				( ExchangeData* data )	= 0;
	virtual void			ObservableFunction		()						= 0;
	virtual void			Deinit					()						= 0;

	virtual std::string		GetTestName				()						= 0;
};


