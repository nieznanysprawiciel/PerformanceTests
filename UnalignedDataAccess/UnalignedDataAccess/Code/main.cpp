#include <iostream>
#include <chrono>

#include <DirectXMath.h>

const unsigned int iterations	= 1000000000;
const unsigned int size			= iterations + 3;
const int startOffset			= 0;

typedef int CheckType;


/// @brief Struktura wierzcho³ka stworzona z myœl¹ o GUI.
typedef struct VertexTexCord1
{
	DirectX::XMFLOAT3	position;		///<Pozycja wierzcho³ka.
	DirectX::XMFLOAT2	tex_cords;		///<Wspó³rzêdne tekstury.
} VertexTexCord1;

/// @brief Struktura wierzcho³ka dla bezteksturowych obiektów.
typedef struct VertexColor
{
	DirectX::XMFLOAT3 position;		///<Pozycja wierzcho³ka
	DirectX::XMFLOAT3 color;		///<Kolor wierzcho³ka
} VertexColor;

/// @brief Struktura u¿ywana do produkowania lightmap.
typedef struct CoordColor
{
	DirectX::XMFLOAT2 texCoords;	///<Wspo³rzêdne lightmapy.
	DirectX::XMFLOAT3 color;		///<Kolor dla danej wspó³rzêdnej.
} CoordColor;

struct Test4Struct
{
	uint32_t	var1;
	bool		var2;
};

struct Test5Struct
{
	bool		var1;
	short		var2;
	bool		var3;
};

int main()
{
	char* data = (char*) new unsigned int[ size / 4 + 1 ];		// Alokujemy pamiêæ z zapasem, bo bêdziemy zmieniaæ offset
	memset( data, 1, size );
	
	for( int offset = startOffset; offset < 4; ++offset )
	{
		auto timeBegin = std::chrono::high_resolution_clock::now();

		CheckType accum = 0;
		for( unsigned int i = offset; i < iterations + offset; i += 4 )
		{
			CheckType number = static_cast<CheckType>( *(data + i) );
			accum += number;
			//if( data[ i ] % 4 == 0 )
			//	std::cout << "Fail";
		}

		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto period = timeEnd - timeBegin;
		std::cout << "Execution time for offset: " << offset << " is: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;
	}

	delete[] data;

	std::cout << "Size and alignment test" << std::endl;
	std::cout << "VertexTexCord1 size: " << sizeof( VertexTexCord1 ) << std::endl;
	std::cout << "VertexColor size: "<< sizeof( VertexColor ) << std::endl;
	std::cout << "CoordColor size: " << sizeof( CoordColor ) << std::endl;
	std::cout << "Test4Struct size: " << sizeof( Test4Struct ) << std::endl;
	std::cout << "Test5Struct size: " << sizeof( Test5Struct ) << std::endl;

	char sign;
	std::cin >> sign;

	return 0;
}