#ifndef CAMERAH
#define CAMERAH

#define M_PI 3.141592653

#include "ray.h"

class camera {
public:
	vec3 lowerLeft;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;

	//vfov : degree
	//aspect =  width / height
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
		float theta = vfov * M_PI / 180.f;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;

		origin = lookfrom;
		vec3 w = unit_vector(lookfrom - lookat);
		vec3 u = unit_vector(cross(vup, w));
		vec3 v = cross(w, u);

		lowerLeft = origin -  halfWidth * u - halfHeight * v - w;
		horizontal = 2 * halfWidth * u;
		vertical = 2 * halfHeight * v;
	}

	ray get_ray(float s, float t){return ray(origin, lowerLeft + s * horizontal + t * vertical-origin);}
};

#endif