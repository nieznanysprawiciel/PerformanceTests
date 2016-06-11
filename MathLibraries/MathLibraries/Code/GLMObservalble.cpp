#include "Framework.h"
#include "Observable.h"
#include "MatrixSet.h"

#include "glm/glm.hpp"

class GLMObservalbe : public Observable
{
private:

	glm::mat4*		dataset;
	int				size;

	glm::mat4		result;

public:
	~GLMObservalbe() {}

	
	
	virtual void			InitData				( ExchangeData* data )
	{
		dataset = reinterpret_cast< glm::mat4* >( ((MatrixSet*)data)->matrices.data() );
		size = ((MatrixSet*)data)->matrices.size() / 16;
	}

	virtual void			ObservableFunction		()
	{
		for( int i = 0; i < size - 5; ++i )
		{
			glm::mat4& world = dataset[ i ];
			glm::mat4& view = dataset[ i + 1 ];
			glm::mat4& projection = dataset[ i + 2 ];
			glm::mat4& additional1 = dataset[ i + 3 ];
			glm::mat4& additional2 = dataset[ i + 4 ];
			glm::mat4& additional3 = dataset[ i + 5 ];


			glm::mat4 res = projection * view * world;
			glm::mat4 temp = additional3 * additional2 * additional1;
			res = temp * res;
			result = res;
		}

	}
	virtual void			Deinit					()
	{
		dataset = nullptr;
	}

	virtual std::string		GetTestName				()
	{
		return "GLM";
	}
};



int shitVarGLM = Framework::Get().AddObservable( new GLMObservalbe() );

