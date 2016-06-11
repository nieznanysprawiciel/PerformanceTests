#include "Framework.h"
#include "Observable.h"
#include "MatrixSet.h"

#include <DirectXMath.h>

using namespace DirectX;


class DirectXOperatorObservable : public Observable
{
private:

	XMFLOAT4X4*		dataset;
	int				size;

	XMFLOAT4X4		result;

public:
	~DirectXOperatorObservable() {}

	
	
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


			XMMATRIX res = world * view * projection;
			XMMATRIX temp = additional1 * additional2 * additional3;
			res = res * temp;
			XMStoreFloat4x4( &result, res );
		}

	}
	virtual void			Deinit					()
	{
		dataset = nullptr;
	}

	virtual std::string		GetTestName				()
	{
		return "DirectXMath operator*";
	}
};



int shitVarOp = Framework::Get().AddObservable( new DirectXOperatorObservable() );

