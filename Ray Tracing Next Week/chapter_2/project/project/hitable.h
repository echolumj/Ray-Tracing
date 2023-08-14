#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include <random>

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	std::shared_ptr<material> matPtr;
};

class hitable
{
public:
	virtual	bool hit(const ray& r, float tmin, float tmax, hit_record& record) const = 0;
	static vec3 random_in_unit_sphere(void);
};


#endif
