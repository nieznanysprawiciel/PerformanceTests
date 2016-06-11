#include <iostream>
#include <chrono>


#include <stdio.h>
#include <fstream>



void ReadFileC( const char* fileName )
{
	FILE* f = fopen( fileName, "rb" );

	if( f != nullptr )
	{
		// Determine file size
		fseek( f, 0, SEEK_END );
		size_t size = ftell( f );

		char* where = new char[ size ];

		rewind( f );
		fread( where, sizeof( char ), size, f );

		delete[] where;
		fclose( f );
	}
}



void ReadFileFilebuf( const char* fileName )
{
	std::ifstream file( fileName, std::ios::binary | std::ios::ate );

	std::streambuf* raw_buffer = file.rdbuf();
	unsigned int size = raw_buffer->pubseekoff( 0, file.end );
	file.seekg ( 0, file.beg );

	char* block = new char[ size ];
	raw_buffer->sgetn( block, size );
	delete[] block;
}

void ReadFileIfstreamRead( const char* fileName )
{
	std::ifstream file( fileName, std::ios::binary | std::ios::ate );
	
	unsigned int size = file.tellg();
	file.seekg ( 0, file.beg );

	char* block = new char[ size ];
	file.read( block, size );
	delete[] block;
}


void ReadFileStreamIterators( const char* fileName )
{
	std::ifstream ifs( fileName, std::ios_base::in | std::ios_base::binary );
	std::string content( ( std::istreambuf_iterator<char>( ifs ) ),
						 ( std::istreambuf_iterator<char>() ) );
}





const char* fileToRead = "citylots.shp";

void WriteExecutionTime( std::chrono::time_point< std::chrono::system_clock, std::chrono::system_clock::duration > begin )
{
	auto timeEnd = std::chrono::high_resolution_clock::now();

	auto period = timeEnd - begin;
	std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" << std::endl;
}

int main()
{
	std::cout << "File reading speed test" << std::endl;

	//============================================================//
	std::cout << "Reading with C functions." << std::endl;

	auto timeBegin = std::chrono::high_resolution_clock::now();
	ReadFileC( fileToRead );
	WriteExecutionTime( timeBegin );

	//============================================================//
	std::cout << "Reading with stream iterators." << std::endl;

	timeBegin = std::chrono::high_resolution_clock::now();
	ReadFileStreamIterators( fileToRead );
	WriteExecutionTime( timeBegin );

	//============================================================//
	std::cout << "Reading with file stream buffer." << std::endl;

	timeBegin = std::chrono::high_resolution_clock::now();
	ReadFileFilebuf( fileToRead );
	WriteExecutionTime( timeBegin );

	//============================================================//
	std::cout << "Reading with ifstream.read." << std::endl;

	timeBegin = std::chrono::high_resolution_clock::now();
	ReadFileIfstreamRead( fileToRead );
	WriteExecutionTime( timeBegin );

	//============================================================//
	std::cout << "Enter sign to end..." << std::endl;
	char sign;
	std::cin >> sign;

	return 0;
}


