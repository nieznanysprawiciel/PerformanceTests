#include "DerivedClass1.h"



DerivedClass1::DerivedClass1()
{ }


DerivedClass1::~DerivedClass1()
{ }

float DerivedClass1::VirtualFunction( int i, float k )
{
	float result = 0;
	for( int j = 0; j < i; j++ )
	{
		result += k;
		result = ( result + j*k  ) / result;
	}

	return result;
}
