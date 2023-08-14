#ifndef INTERVALH
#define INTERVALH

template <class T>
class interval
{
public:
	interval() {}
	interval(T l, T r);
	interval(const interval& x, const interval &y):
		_left(fmin(x._left, y._left)), _right(fmax(x._right, y._right)){}

	bool isContain(T num) const;

public:
	T _left;
	T _right;
};


#endif 