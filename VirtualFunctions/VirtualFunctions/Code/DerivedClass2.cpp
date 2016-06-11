#include "DerivedClass2.h"



DerivedClass2::DerivedClass2()
{ }


DerivedClass2::~DerivedClass2()
{ }


float DerivedClass2::VirtualFunction( int i, float k )
{
	float result = 0;
	for( int j = 0; j < i; j++ )
	{
		result += k;
		result = ( result + j*k  ) / result;
	}

	return result;
}
