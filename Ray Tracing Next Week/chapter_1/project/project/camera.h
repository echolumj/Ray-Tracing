#ifndef CAMERAH
#define CAMERAH

#define M_PI 3.141592653

#include "ray.h"

class hitable;
class camera {
public:
	vec3 lowerLeft;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	vec3 u, v, w;

	float lens_radius;

	//vfov : degree
	//aspect =  width / height
	//depth of field (DOF): aperture, focus_dist
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
		float theta = vfov * M_PI / 180.f;
		float halfHeight = focus_dist * tan(theta / 2);
		float halfWidth = aspect * halfHeight; // the position of plane(≥…œÒ∆Ω√Ê)

		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		lowerLeft = origin -  halfWidth * u - halfHeight * v - focus_dist * w;
		horizontal = 2 * halfWidth * u;
		vertical = 2 * halfHeight * v;

		lens_radius = aperture / 2.f;
	}

	static vec3 random_in_unit_disk(void);

	ray get_ray(float s, float t)
	{
		vec3 rdir = lens_radius * random_in_unit_disk();
		vec3 offset = rdir.x() * u + rdir.y() * v;
		return ray(origin + offset, lowerLeft + s * horizontal + t * vertical-origin-offset);
	}
};

vec3 camera::random_in_unit_disk(void)
{
	vec3 p;
	std::random_device e;
	std::uniform_real_distribution<float> random(0, 1);
	do {
		p = 2.0 * vec3(random(e), random(e), 0) - vec3(1.0, 1.0, 0.0);
	} while (dot(p, p) >= 1.0f);
	return p;
}

#endif