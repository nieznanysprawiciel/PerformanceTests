#include "BaseClass.h"


BaseClass::BaseClass()
{}


BaseClass::~BaseClass()
{}

float BaseClass::VirtualFunction( int i, float k )
{
	float result = 0;
	for( int j = 0; j < i; j++ )
	{
		result += k;
		result = ( result + j*k  ) / result;
	}

	return result;
}

float BaseClass::NormalFunction( int i, float k )
{
	float result = 0;
	for( int j = 0; j < i; j++ )
	{
		result += k;
		result = ( result + j*k  ) / result;
	}

	return result;
}
