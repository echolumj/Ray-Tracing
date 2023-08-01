#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "vec3.h"
#include "hitable.h"

extern std::random_device e;
extern std::uniform_real_distribution<float> random;

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

	vec3 reflect_dir(const vec3& indir, const vec3& normal) const
	{
		vec3 unitDir = unit_vector(indir);
		return unitDir - 2 * dot(unitDir, normal)* normal;
	}

	//the direction of inlight(from eye to object)
	bool refract_dir(const vec3 &inlight, const vec3 &normal, float ni_over_nt, vec3& refracted)const
	{
		//ni_over_nt * (c1 * n + in)-c2*n;
		//c1 = dot(n, -in)
		vec3 rin = unit_vector(inlight);
		float c1 = dot(-rin, normal);
		float pow_c2 = 1.0 - ni_over_nt * ni_over_nt*(1 - c1 * c1);
		if (pow_c2 > 0)
		{
			float c2 = sqrt(pow_c2); 
			refracted = ni_over_nt * (c1 * normal + rin) - c2 * normal;
			return true;
		}
		return false;
	}

	float schlick(float cosine, float refractIndex) const
	{
		float r0 = (1 - refractIndex) / (1 + refractIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cosine), 5);
	}
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
};

class dielectrics :public material {
public:
	float refractIndex;

	dielectrics(float r):refractIndex(r){}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 normal = rec.normal;
		attenuation = vec3(1.0, 1.0, 1.0);
		float ni_over_nt = refractIndex;
		vec3 refracted;
		vec3 indir = unit_vector(r_in.get_direction());
		float cosine;

		if (dot(indir, rec.normal) > 0)
		{
			normal = -normal;
		}	
		else
		{
			ni_over_nt = 1.0 / ni_over_nt;
			
		}
		cosine = -dot(indir, normal);	
		float p;

		float currentP = random(e);
		if (refract_dir(r_in.get_direction(), normal, ni_over_nt, refracted))
		{
			//scattered = ray(rec.p, refracted);
			p = schlick(cosine, ni_over_nt);
		}
		else
		{
			//vec3 reflected = reflect_dir(r_in.get_direction(), normal);
			//scattered = ray(rec.p, reflected);
			//return false;//refract failed
			p = 1.0f;
		}

		if(currentP > p)
			scattered = ray(rec.p, refracted);
		else
		{
			vec3 reflected = reflect_dir(r_in.get_direction(), normal);
			scattered = ray(rec.p, reflected);
		}
		return true;
	}

};
#endif
