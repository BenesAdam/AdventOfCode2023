#pragma once

#include <iostream>

template <typename T>
struct sPosition
{
	T i;
	T j;

	sPosition(void);
	sPosition(T arg_i, T arg_j);
	sPosition(const sPosition<T>* const arg_original);

	sPosition<T> operator+(T arg_value);
	sPosition<T> operator-(T arg_value);
	sPosition<T> operator*(T arg_value);
	sPosition<T> operator/(T arg_value);

	sPosition<T>& operator+=(T arg_value);
	sPosition<T>& operator-=(T arg_value);
	sPosition<T>& operator*=(T arg_value);
	sPosition<T>& operator/=(T arg_value);

	sPosition<T> operator+(const sPosition& arg_other);
	sPosition<T> operator-(const sPosition& arg_other);
	sPosition<T> operator*(const sPosition& arg_other);
	sPosition<T> operator/(const sPosition& arg_other);

	sPosition<T>& operator+=(const sPosition& arg_other);
	sPosition<T>& operator-=(const sPosition& arg_other);
	sPosition<T>& operator*=(const sPosition& arg_other);
	sPosition<T>& operator/=(const sPosition& arg_other);

	T GetManhattanDistance(const sPosition& arg_other);
};

namespace nsNumeric
{
	template<typename T, typename S>
	T ManhattanDistance(const sPosition<T>& arg_pos1, const sPosition<T>& arg_pos2);
}

//-----------------------------------------------------------------------------

template<typename T>
inline sPosition<T>::sPosition(void) :
	i(T(0)),
	j(T(0))
{
}

template<typename T>
inline sPosition<T>::sPosition(T arg_i, T arg_j) :
	i(arg_i),
	j(arg_j)
{
}

template<typename T>
inline sPosition<T>::sPosition(const sPosition<T>* const arg_original) :
	i(arg_original->i),
	j(arg_original->j)
{
}

template<typename T>
inline sPosition<T> sPosition<T>::operator+(T arg_value)
{
	sPosition<T> result(this);
	result.i += arg_value;
	result.j += arg_value;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator-(T arg_value)
{
	sPosition<T> result(this);
	result.i -= arg_value;
	result.j -= arg_value;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator*(T arg_value)
{
	sPosition<T> result(this);
	result.i *= arg_value;
	result.j *= arg_value;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator/(T arg_value)
{
	sPosition<T> result(this);
	result.i /= arg_value;
	result.j /= arg_value;
	return result;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator+=(T arg_value)
{
	this->i += arg_value;
	this->j += arg_value;

	return *this;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator-=(T arg_value)
{
	this->i -= arg_value;
	this->j -= arg_value;

	return *this;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator*=(T arg_value)
{
	this->i *= arg_value;
	this->j *= arg_value;

	return *this;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator/=(T arg_value)
{
	this->i /= arg_value;
	this->j /= arg_value;

	return *this;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator+(const sPosition& arg_other)
{
	sPosition<T> result(this);
	result += arg_other.i;
	result += arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator-(const sPosition& arg_other)
{
	sPosition<T> result(this);
	result -= arg_other.i;
	result -= arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator*(const sPosition& arg_other)
{
	sPosition<T> result(this);
	result *= arg_other.i;
	result *= arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator/(const sPosition& arg_other)
{
	sPosition<T> result(this);
	result /= arg_other.i;
	result /= arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator+=(const sPosition& arg_other)
{
	this->i += arg_other.i;
	this->j += arg_other.j;

	return *this;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator-=(const sPosition& arg_other)
{
	this->i -= arg_other.i;
	this->j -= arg_other.j;

	return *this;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator*=(const sPosition& arg_other)
{
	this->i *= arg_other.i;
	this->j *= arg_other.j;

	return *this;
}

template<typename T>
inline sPosition<T>& sPosition<T>::operator/=(const sPosition& arg_other)
{
	this->i /= arg_other.i;
	this->j /= arg_other.j;

	return *this;
}

template<typename T>
inline T sPosition<T>::GetManhattanDistance(const sPosition& arg_other)
{
	return 
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const sPosition<T>& a)
{
	o << "[" << a.i << ", " << a.j << "]";
	return o;
}

template<typename T, typename S>
T ManhattanDistance(const sPosition<T>& arg_pos1, const sPosition<T>& arg_pos2)
{
	S x1 = static_cast<S>(arg_pos1.i);
	S y1 = static_cast<S>(arg_pos1.j);
	S x2 = static_cast<S>(arg_pos2.i);
	S y2 = static_cast<S>(arg_pos2.j);

	return static_cast<T>(abs(x1 - x2) + abs(y1 - y2));
}
