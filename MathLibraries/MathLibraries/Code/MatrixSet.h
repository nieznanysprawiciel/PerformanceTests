#pragma once

#include <ExchangeData.h>
#include <vector>

struct MatrixSet : public ExchangeData
{
	std::vector< float >	matrices;
};

