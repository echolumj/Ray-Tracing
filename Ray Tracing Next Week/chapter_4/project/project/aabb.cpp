#include "aabb.h"
#include "ray.h"
#include "interval.h"

aabb::aabb(vec3 a, vec3 b)
{
	_x = interval<float>(a.x(), b.x());
	_y = interval<float>(a.y(), b.y());
	_z = interval<float>(a.z(), b.z());

	_pointa = a;
	_pointb = b;
}

interval<float> aabb::operator[](int idx)
{
	return idx == 0 ? _x : (idx == 1 ? _y : _z);
}

aabb::aabb(const aabb &ab1, const aabb &ab2)
{
	_x = interval<float>(ab1._x, ab2._x);
	_y = interval<float>(ab1._y, ab2._y);
	_z = interval<float>(ab1._z, ab2._z);

	_pointa = vec3(_x._left, _y._left, _z._left);
	_pointb = vec3(_x._right, _y._right, _z._right);
}

bool aabb::hit(const ray& r, interval<float> ray_t)  const
{
	auto origin = r.get_origin();

	//origin in aabb
	//if (_x.isContain(origin.x()) && _y.isContain(origin.y()) && _z.isContain(origin.z()))
	//	return false; 

	auto dir = r.get_direction();
	//parallel
	if (abs(dir.x()) < INFINITE_SMALL && !(_x.isContain(dir.x())) || abs(dir.y()) < INFINITE_SMALL && !(_y.isContain(dir.y())) ||
		abs(dir.z()) < INFINITE_SMALL && !(_z.isContain(dir.z())))
	{
		return false;
	}

	vec3 tMin = (_pointa - origin) / dir;
	vec3 tMax = (_pointb - origin) / dir;

	float t0 = 0;
	float t1 = FLT_MAX;
	for (int i = 0; i < 3; ++i)
	{
		t0 = fmax(t0, fmin(tMin[i], tMax[i]));
		t1 = fmin(t1, fmax(tMin[i], tMax[i]));
	}

	//reverse or no intersection
	if (t0 > t1 || t1 < 0)
		return false;

	//is in range [ts,te]?
	if (t0 > ray_t._left) ray_t._left = t0;
	if (t1 < ray_t._right) ray_t._right = t1;

	if (ray_t._right <= ray_t._left)
		return false;

	return true;
}
