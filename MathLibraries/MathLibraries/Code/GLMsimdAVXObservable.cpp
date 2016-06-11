#include "Framework.h"
#include "Observable.h"
#include "MatrixSet.h"

//GLM_FORCE_PURE GLM_FORCE_SSE2 GLM_FORCE_SSE3 GLM_FORCE_AVX GLM_FORCE_AVX2
#define GLM_FORCE_AVX

#include "glm/glm.hpp"
#include "glm/gtx/simd_mat4.hpp"


class GLMsimdObservalbeAVX : public Observable
{
private:

	
	glm::mat4*		dataset;
	int				size;

	glm::mat4		result;

public:
	~GLMsimdObservalbeAVX() {}

	
	
	virtual void			InitData				( ExchangeData* data )
	{
		dataset = reinterpret_cast< glm::mat4* >( ((MatrixSet*)data)->matrices.data() );
		size = ((MatrixSet*)data)->matrices.size() / 16;
	}

	virtual void			ObservableFunction		()
	{
		for( int i = 0; i < size - 5; ++i )
		{
			glm::detail::fmat4x4SIMD world = glm::detail::fmat4x4SIMD( dataset[ i ] );
			glm::detail::fmat4x4SIMD view = glm::detail::fmat4x4SIMD( dataset[ i + 1 ] );
			glm::detail::fmat4x4SIMD projection = glm::detail::fmat4x4SIMD( dataset[ i + 2 ] );
			glm::detail::fmat4x4SIMD additional1 = glm::detail::fmat4x4SIMD( dataset[ i + 3 ] );
			glm::detail::fmat4x4SIMD additional2 = glm::detail::fmat4x4SIMD( dataset[ i + 4 ] );
			glm::detail::fmat4x4SIMD additional3 = glm::detail::fmat4x4SIMD( dataset[ i + 5 ] );


			glm::detail::fmat4x4SIMD res = projection * view * world;
			glm::detail::fmat4x4SIMD temp = additional3 * additional2 * additional1;
			res = temp * res;
			result = glm::mat4_cast( res );
		}

	}
	virtual void			Deinit					()
	{
		dataset = nullptr;
	}

	virtual std::string		GetTestName				()
	{
		return "GLM SIMD AVX";
	}
};



int shitVarGLMsimd4 = Framework::Get().AddObservable( new GLMsimdObservalbeAVX() );
