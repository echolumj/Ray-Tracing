#ifndef AABBH
#define AABBH

#include "vec3.h"
#include "interval.h"

#define INFINITE_SMALL 0.00001

class ray;

class aabb
{
public:
	aabb() {}
	aabb(vec3 a, vec3 b);
	aabb(const aabb & ab1, const aabb &ab2);

	bool hit(const ray& r, interval<float> ray_t) const;
	//static aabb merge(const aabb &ab1, const aabb &ab2);

	interval<float> operator[](int idx);

private:
	vec3 _pointa, _pointb;
	interval<float> _x;
	interval<float> _y;
	interval<float> _z;
};

#endif
