#ifndef AABBH
#define AABBH

#include "hitable.h"
#include "interval.h"

#define INFINITE_SMALL 0.00001

class aabb
{
public:
	aabb() {}
	aabb(vec3 a, vec3 b);
	aabb(const aabb & ab1, const aabb &ab2);

	bool hit(const ray& r, interval<float> ray_t) const;
	//static aabb merge(const aabb &ab1, const aabb &ab2);

private:
	vec3 _pointa, _pointb;
	interval<float> _x;
	interval<float> _y;
	interval<float> _z;
};

#endif
