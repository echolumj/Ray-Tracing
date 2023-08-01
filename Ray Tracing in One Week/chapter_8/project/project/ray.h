#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
public:
	ray() {}
	ray(const vec3& o, const vec3& d) { oriPos = o; dir = d; }
	vec3 get_origin() const { return oriPos; }
	vec3 get_direction() const { return dir; }

	void set_origin(const vec3 o) { oriPos = o; }
	void set_direction(const vec3 d) { dir = d; }

	vec3 point_at_parameter(float t) const { return oriPos + t * dir; }

private:
	vec3 oriPos;
	vec3 dir;
};

#endif // !RAYH

