//---------------------------
//
// Nicolas Van der Noot
//
// Creation : 29/10/2013
// Last update : 29/10/2013
//---------------------------

#include "simu_def.h"

// return 'value' bounded in the [this_min; this_max] interval
double limit_function(double value, double this_min, double this_max)
{
	if (value < this_min)
	{
		return this_min;
	}
	else if (value > this_max)
	{
		return this_max;
	}
	else
	{
		return value;
	}
}