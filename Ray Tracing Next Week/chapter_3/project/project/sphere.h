#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable
{
public:
	sphere();
	sphere(vec3 center, float r, std::shared_ptr<material> mater);
	sphere(float time0, float time1, vec3 center0, vec3 center1, float radius,
		std::shared_ptr<material> material);

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& record) const;
	virtual aabb bounding_box() const override { return this->_aabb; }

public:
	vec3 _centerStart;
	vec3 _centerEnd;
	float _timeStart;
	float _timeEnd;

	float _radius;
	std::shared_ptr<material> _mater;

private:
	vec3 getCurrentCenter(float time) const;

private:
	bool _isMoving = false;
	aabb _aabb;
};

#endif
