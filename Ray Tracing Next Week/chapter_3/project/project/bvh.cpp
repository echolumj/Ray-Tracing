#include "bvh.h"

bool bvh::hit(const ray& r, float tmin, float tmax, hit_record& record) const
{
	if (_aabb.hit(r, interval<float>(tmin, tmax)) == false)
		return false;

	bool isLeft = _left->hit(r, tmin, tmax, record);
	bool isRight = _right->hit(r, tmin, (isLeft? record.t: tmax), record);

	return isLeft || isRight;
}
