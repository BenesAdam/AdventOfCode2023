#pragma once

#include <numeric>

namespace nsNumeric
{
	//----------------------------------------------------------------------------
	// Declarations
	//----------------------------------------------------------------------------
	template<typename T>
	T LeastCommonMultiple(const T arg_a, const T arg_b);

	template<typename T>
	T GreatestCommonDivisor(const T arg_a, const T arg_b);

	//----------------------------------------------------------------------------
	// Definitions
	//----------------------------------------------------------------------------
	template<typename T>
	T LeastCommonMultiple(const T arg_a, const T arg_b)
	{
		T a = std::max(arg_a, arg_b);
		T b = std::min(arg_a, arg_b);

		return (a / GreatestCommonDivisor<T>(a, b)) * b;
	}

	template<typename T>
	T GreatestCommonDivisor(const T arg_a, const T arg_b)
	{
		return (arg_b == static_cast<T>(0)) ? arg_a : GreatestCommonDivisor<T>(arg_b, arg_a % arg_b);
	}
}