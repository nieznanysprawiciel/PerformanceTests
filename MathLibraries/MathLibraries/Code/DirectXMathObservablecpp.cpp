#include "Framework.h"
#include "Observable.h"
#include "MatrixSet.h"

#include <DirectXMath.h>

using namespace DirectX;


class DirectXMathObservable : public Observable
{
private:

	XMFLOAT4X4*		dataset;
	int				size;

	XMFLOAT4X4		result;

public:
	~DirectXMathObservable() {}

	
	
	virtual void			InitData				( ExchangeData* data )
	{
		dataset = reinterpret_cast< XMFLOAT4X4* >( ((MatrixSet*)data)->matrices.data() );
		size = ((MatrixSet*)data)->matrices.size() / 16;
	}

	virtual void			ObservableFunction		()
	{
		for( int i = 0; i < size - 5; ++i )
		{
			XMMATRIX world = XMLoadFloat4x4( &dataset[ i ] );
			XMMATRIX view = XMLoadFloat4x4( &dataset[ i + 1 ] );
			XMMATRIX projection = XMLoadFloat4x4( &dataset[ i + 2 ] );
			XMMATRIX additional1 = XMLoadFloat4x4( &dataset[ i + 3 ] );
			XMMATRIX additional2 = XMLoadFloat4x4( &dataset[ i + 4 ] );
			XMMATRIX additional3 = XMLoadFloat4x4( &dataset[ i + 5 ] );


			XMMATRIX res = XMMatrixMultiply( world, XMMatrixMultiply( view, projection ) );
			XMMATRIX temp = XMMatrixMultiply( additional1, XMMatrixMultiply( additional2, additional3 ) );
			res = XMMatrixMultiply( res, temp );
			XMStoreFloat4x4( &result, res );
		}

	}
	virtual void			Deinit					()
	{
		dataset = nullptr;
	}

	virtual std::string		GetTestName				()
	{
		return "DirectXMath";
	}
};



int shitVar = Framework::Get().AddObservable( new DirectXMathObservable() );

