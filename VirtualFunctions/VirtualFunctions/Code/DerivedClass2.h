#pragma once

#include "BaseClass.h"


class DerivedClass2 : public BaseClass
{
public:
	DerivedClass2();
	virtual ~DerivedClass2();

	virtual float			VirtualFunction		( int i, float k );
};

