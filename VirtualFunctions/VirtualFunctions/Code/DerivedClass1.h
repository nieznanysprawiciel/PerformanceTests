#pragma once

#include "BaseClass.h"


class DerivedClass1 : public BaseClass
{
public:
	DerivedClass1();
	~DerivedClass1();

	virtual float			VirtualFunction		( int i, float k );
};

