#ifndef INTERVALH
#define INTERVALH

template <class T>
class interval
{
public:
	interval() {}
	interval(T l, T r)
	{
		_left = min(l, r);
		_right = max(l, r);
	}
	interval(const interval<T>& x, const interval<T> &y):
		_left(min(x._left, y._left)), _right(max(x._right, y._right)){}

	bool isContain(T num) const { return num <= _right && num >= _left; }
	T max(T l, T r)
	{
		if (l < r) return r;
		return l;
	}

	T min(T l, T r)
	{
		if (l < r) return l;
		return r;
	}

public:
	T _left;
	T _right;
};


#endif 