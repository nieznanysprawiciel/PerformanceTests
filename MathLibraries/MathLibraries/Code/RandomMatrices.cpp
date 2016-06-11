#include "DatasetGenerator.h"
#include "Framework.h"
#include "MatrixSet.h"


#include <random>


struct RandomMatrices : public DatasetGenerator
{
	__int64 NumMat;

	RandomMatrices(__int64 numMat)
	{
		NumMat = numMat;
	}
	virtual ~RandomMatrices() {};

	virtual ExchangeData*		Generate		()
	{
		MatrixSet* newSet = new MatrixSet();
		newSet->DatasetName = "Random matrices " + std::to_string( NumMat );

		newSet->matrices.reserve( 16 * NumMat );

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis( -40.0f, 40.0f );

		for( int i = 0; i < NumMat * 16; ++i )
		{
			newSet->matrices.push_back( dis( gen ) );
		}

	
		return newSet;
	}
};

int shit1 = Framework::Get().AddDataGenerator( new RandomMatrices( 1000000 ) );
int shit2 = Framework::Get().AddDataGenerator( new RandomMatrices( 10000000 ) );
int shit3 = Framework::Get().AddDataGenerator( new RandomMatrices( 30000000 ) );

