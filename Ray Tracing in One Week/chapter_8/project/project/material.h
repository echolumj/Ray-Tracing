#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "vec3.h"
#include "hitable.h"

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian :public material{
public:
	vec3 albedo;

	lambertian(const vec3& a):albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 direction = rec.normal + hitable::random_in_unit_sphere();
		scattered = ray(rec.p, direction);
		attenuation = albedo;
		return true;
	}
};

class metal :public material{
public:
	vec3 albedo;
	float fuzziness;

	metal(const vec3& a, float fuzz) :albedo(a) { if (fuzz < 1) fuzziness = fuzz; else fuzziness = 1.f; }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect_dir(r_in.get_direction(), rec.normal);
		scattered = ray(rec.p, reflected + fuzziness * hitable::random_in_unit_sphere());
		attenuation = albedo;
		return dot(scattered.get_direction(), rec.normal) > 0;

	}

	vec3 reflect_dir(const vec3& indir, const vec3& normal) const
	{
		vec3 unitDir = unit_vector(indir);
		return unitDir - 2 * dot(unitDir, normal)* normal;
	}
};
#endif
