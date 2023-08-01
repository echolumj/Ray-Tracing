#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material* matPtr;
};

class hitable
{
public:
	virtual	bool hit(const ray& r, float tmin, float tmax, hit_record& record) const = 0;
	static vec3 random_in_unit_sphere(void);
};

 vec3 hitable::random_in_unit_sphere(void)
{
	vec3 p;
	std::random_device e;
	std::uniform_real_distribution<float> random(0, 1);
	do {
		p = 2.0 * vec3(random(e), random(e), random(e)) - vec3(1.0, 1.0, 1.0);
	} while (dot(p, p) >= 1.0f);
	return p;
}

#endif
