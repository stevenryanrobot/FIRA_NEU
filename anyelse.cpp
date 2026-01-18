#include "stdafx.h"

namespace rcsc
{
	const double fmax(const double& a, const double& b)
	{
	return (a > b ? a : b);
	}
 
	const double fmin(const double& a, const double& b)
	{
		return (a < b ? a : b);
	}
}