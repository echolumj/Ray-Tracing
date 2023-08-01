#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
	vec3 lowerLeft;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;

	camera():lowerLeft(-2, -1, -1),horizontal(4.0, 0.0, 0.0),vertical(0, 2, 0),origin(0.0, 0.0, 0.0) {}
	ray get_ray(float u, float v){return ray(origin, lowerLeft + u * horizontal + v * vertical-origin);}
};

#endif