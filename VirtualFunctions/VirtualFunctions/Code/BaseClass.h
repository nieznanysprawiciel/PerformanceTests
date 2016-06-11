#pragma once




class BaseClass
{
private:
public:
	BaseClass();
	virtual ~BaseClass();

	virtual float			VirtualFunction		( int i, float k );
	float					NormalFunction		( int i, float k );
	inline float			InlineFunction		( int i, float k );
};


float			BaseClass::InlineFunction		( int i, float k )
{
	float result = 0;
	for( int j = 0; j < i; j++ )
	{
		result += k;
		result = ( result + j*k  ) / result;
	}

	return result;
}
