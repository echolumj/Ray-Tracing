#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable
{
public:
	vec3 center;
	float radius;
	material *mater;

	sphere() {}
	sphere(vec3 c, float r, material* mater) :center(c), radius(r), mater(mater){};

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& record) const; 
};

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& record) const
{
	vec3 oc = r.get_origin() - center;
	float a = dot(r.get_direction(), r.get_direction());
	float b = 2.0f * dot(oc, r.get_direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;

	if (discriminant > 0) // two ans point
	{
		float temp = (-b - std::sqrtf(discriminant)) / (2 * a);
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(temp);
			record.normal = (record.p - center) / radius;
			record.matPtr = mater;
			return true;
		}
		temp = (-b + std::sqrtf(discriminant)) / (2 * a);
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(temp);
			record.normal = (record.p - center) / radius;
			record.matPtr = mater;
			return true;
		}
	}
	//one ans + no ans
	return false;
}


#endif
