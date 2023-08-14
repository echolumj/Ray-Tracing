#include "interval.h"

template <class T>
interval<T>::interval(T l, T r)
{
	_left = min(l, r);
	_right = max(l, r);
}

template <class T>
bool interval<T>::isContain(T num) const
{
	return num <= _right && num >= _left;
}