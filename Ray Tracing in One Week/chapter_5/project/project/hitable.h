#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
};

class hitable
{
public:
	virtual	bool hit(const ray& r, float tmin, float tmax, hit_record& record) const = 0;
};

#endif
