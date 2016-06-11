#include <iostream>
#include <chrono>
#include <thread>

#include "Common/SpinLock.h"
#include <mutex>

class TestAccess
{
public:
	unsigned int		value;

public:
	TestAccess() { value = 0; }
};


TestAccess object;
const unsigned int outerIterations = 10000;
const unsigned int innerIterations = 10000;
std::mutex mutex;
SpinLock spinLock;
#define THREADS_COUNT 1


void ThreadFunctionWithoutSynchronization()
{
	int x = 3;
	for( unsigned int i = 0; i < outerIterations; ++i )
	{
		for( unsigned int j = 0; j < innerIterations; ++j )
		{
			{
				++object.value;
			}
			x *= 3;
		}
		for( unsigned int j = 0; j < innerIterations; ++j )
		{
			{
				--object.value;
			}
			x /= 3;
		}
	}
	x;
}

void ThreadFunctionSpinLock()
{
	int x = 3;
	for( unsigned int i = 0; i < outerIterations; ++i )
	{
		for( unsigned int j = 0; j < innerIterations; ++j )
		{
			{
				std::lock_guard<SpinLock> guard( spinLock );
				//spinLock.lock();
				++object.value;
				//spinLock.unlock();
			}
			x *= 3;
		}
		for( unsigned int j = 0; j < innerIterations; ++j )
		{
			{
				std::lock_guard<SpinLock> guard( spinLock );
				//spinLock.lock();
				--object.value;
				//spinLock.unlock();
			}
			x /= 3;
		}
	}
	x;
}

void ThreadFunctionMutex()
{
	int x = 3;
	for( unsigned int i = 0; i < outerIterations; ++i )
	{
		for( unsigned int j = 0; j < innerIterations; ++j )
		{
			{
				std::lock_guard<std::mutex> guard( mutex );
				//mutex.lock();
				++object.value;
				//mutex.unlock();
			}
			x *= 3;
		}
		for( unsigned int j = 0; j < innerIterations; ++j )
		{
			{
				std::lock_guard<std::mutex> guard( mutex );
				//mutex.lock();
				--object.value;
				//mutex.unlock();
			}
			x /= 3;
		}
	}
}

// Odpala 8 w¹tków. Najpierw mierzy czas dla SpinLocka, a potem dla std::mutexu.
int main()
{

	auto timeBegin = std::chrono::high_resolution_clock::now();

	std::thread threads[ THREADS_COUNT ];
	for( unsigned int i = 0; i < THREADS_COUNT; ++i )
		threads[ i ] = std::thread( &ThreadFunctionWithoutSynchronization );
	
	//auto timeBegin = std::chrono::high_resolution_clock::now();

	for( auto& thread : threads )
		thread.join();

	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto period = timeEnd - timeBegin;
	std::cout << "Execution time without synchronization is: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;

	if( object.value != 0 )
		std::cout << "Niepoprawna wartoœæ obiektu: " << object.value << std::endl;
	object.value = 0;


	// ========================================================== //

	timeBegin = std::chrono::high_resolution_clock::now();

	for( unsigned int i = 0; i < THREADS_COUNT; ++i )
		threads[ i ] = std::thread( &ThreadFunctionSpinLock );
	
	//timeBegin = std::chrono::high_resolution_clock::now();

	for( auto& thread : threads )
		thread.join();

	timeEnd = std::chrono::high_resolution_clock::now();
	period = timeEnd - timeBegin;
	std::cout << "Execution time for SpinLock: is: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;

	if( object.value != 0 )
		std::cout << "Niepoprawna wartoœæ obiektu: " << object.value << std::endl;
	object.value = 0;

	// ========================================================== //

	timeBegin = std::chrono::high_resolution_clock::now();

	for( unsigned int i = 0; i < THREADS_COUNT; ++i )
		threads[ i ] = std::thread( &ThreadFunctionMutex );

	//timeBegin = std::chrono::high_resolution_clock::now();

	for( auto& thread : threads )
		thread.join();

	timeEnd = std::chrono::high_resolution_clock::now();
	period = timeEnd - timeBegin;
	std::cout << "Execution time for std::mutex is: " << std::chrono::duration_cast<std::chrono::milliseconds>( period ).count() << " ms" <<std::endl;

	if( object.value != 0 )
		std::cout << "Niepoprawna wartoœæ obiektu: " << object.value << std::endl;

	char sign;
	std::cin >> sign;
	return 0;
}
