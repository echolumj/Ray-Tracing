#include "hitable.h"

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