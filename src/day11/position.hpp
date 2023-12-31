#pragma once

#include <iostream>

template <typename T>
struct sPosition
{
	T i;
	T j;

	sPosition(void);
	sPosition(T arg_value);
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

	sPosition<T>& operator=(T arg_value);
	bool operator==(T arg_value);
	bool operator!=(T arg_value);

	sPosition<T> operator+(const sPosition<T>& arg_other) const;
	sPosition<T> operator-(const sPosition<T>& arg_other) const;
	sPosition<T> operator*(const sPosition<T>& arg_other) const;
	sPosition<T> operator/(const sPosition<T>& arg_other) const;

	sPosition<T>& operator+=(const sPosition<T>& arg_other);
	sPosition<T>& operator-=(const sPosition<T>& arg_other);
	sPosition<T>& operator*=(const sPosition<T>& arg_other);
	sPosition<T>& operator/=(const sPosition<T>& arg_other);

	sPosition<T>& operator=(const sPosition<T>& arg_other);
	bool operator==(const sPosition<T>& arg_other);
	bool operator!=(const sPosition<T>& arg_other);
	bool operator<(const sPosition<T>& arg_other) const;

	bool IsInBoundary(const T arg_width, const T arg_height) const;
	bool IsInBoundary(const sPosition<T>& arg_dimensions) const;

	T ManhattanDistance(const sPosition<T>& arg_other);
};

//-----------------------------------------------------------------------------

template<typename T>
inline sPosition<T>::sPosition(void) :
	i(T(0)),
	j(T(0))
{
}

template<typename T>
inline sPosition<T>::sPosition(T arg_value) :
	i(arg_value),
	j(arg_value)
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
inline sPosition<T>& sPosition<T>::operator=(T arg_value)
{
	this->i = arg_value;
	this->j = arg_value;

	return *this;
}

template<typename T>
inline bool sPosition<T>::operator==(T arg_value)
{
	return (this->i == arg_value) && (this->j == arg_value);
}

template<typename T>
inline bool sPosition<T>::operator!=(T arg_value)
{
	return !(*this == arg_value);
}

template<typename T>
inline sPosition<T> sPosition<T>::operator+(const sPosition& arg_other) const
{
	sPosition<T> result(this);
	result.i += arg_other.i;
	result.j += arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator-(const sPosition& arg_other) const
{
	sPosition<T> result(this);
	result.i -= arg_other.i;
	result.j -= arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator*(const sPosition& arg_other) const
{
	sPosition<T> result(this);
	result.i *= arg_other.i;
	result.j *= arg_other.j;
	return result;
}

template<typename T>
inline sPosition<T> sPosition<T>::operator/(const sPosition& arg_other) const
{
	sPosition<T> result(this);
	result.i /= arg_other.i;
	result.j /= arg_other.j;
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
inline sPosition<T>& sPosition<T>::operator=(const sPosition<T>& arg_other)
{
	this->i = arg_other.i;
	this->j = arg_other.j;

	return *this;
}

template<typename T>
inline bool sPosition<T>::operator==(const sPosition<T>& arg_other)
{
	return (this->i == arg_other.i) && (this->j == arg_other.j);
}

template<typename T>
inline bool sPosition<T>::operator!=(const sPosition<T>& arg_other)
{
	return !(*this == arg_other);
}

template<typename T>
inline bool sPosition<T>::operator<(const sPosition<T>& arg_other) const
{
	if (this->i < arg_other.i)
	{
		return true;
	}
	else if (this->i > arg_other.i)
	{
		return false;
	}
	else
	{
		return this->j < arg_other.j;
	}
}

template<typename T>
inline bool sPosition<T>::IsInBoundary(const T arg_height, const T arg_width) const
{
	return (i >= T(0)) && (i < arg_height) && (j >= T(0)) && (j < arg_width);
}

template<typename T>
inline bool sPosition<T>::IsInBoundary(const sPosition<T>& arg_dimensions) const
{
	return IsInBoundary(arg_dimensions.i, arg_dimensions.j);
}

template<typename T>
inline T sPosition<T>::ManhattanDistance(const sPosition<T>& arg_other)
{
	T x1 = std::max(this->i, arg_other.i);
	T x2 = std::min(this->i, arg_other.i);
	T y1 = std::max(this->j, arg_other.j);
	T y2 = std::min(this->j, arg_other.j);

	return (x1 - x2) + (y1 - y2);
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const sPosition<T>& a)
{
	o << "[" << a.i << ", " << a.j << "]";
	return o;
}
