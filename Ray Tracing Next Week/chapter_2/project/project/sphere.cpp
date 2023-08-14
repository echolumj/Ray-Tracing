#include "sphere.h"

//--------------------class:sphere-------------------------
sphere::sphere() 
{

}

sphere::sphere(vec3 center, float r, std::shared_ptr<material> mater): _centerStart(center), _radius(r), _mater(mater), _isMoving(false)
{

}

sphere::sphere(float time0, float time1, vec3 center0, vec3 center1, float radius, std::shared_ptr<material> material) : 
	_timeStart(time0), _timeEnd(time1), _centerStart(center0), _centerEnd(center1),_radius(radius), _mater(material), _isMoving(true)
{

}

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& record) const
{	
	vec3 center = _isMoving ? getCurrentCenter(r.get_time()) : _centerStart;
	vec3 oc = r.get_origin() - center;
	float a = dot(r.get_direction(), r.get_direction());
	float b = 2.0f * dot(oc, r.get_direction());
	float c = dot(oc, oc) - _radius * _radius;
	float discriminant = b * b - 4 * a*c;

	if (discriminant > 0) // two ans point
	{
		float temp = (-b - std::sqrtf(discriminant)) / (2 * a);
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(temp);
			record.normal = (record.p - center) / _radius;
			record.matPtr = _mater;
			return true;
		}
		temp = (-b + std::sqrtf(discriminant)) / (2 * a);
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(temp);
			record.normal = (record.p - center) / _radius;
			record.matPtr = _mater;
			return true;
		}
	}
	//one ans + no ans
	return false;
}

vec3 sphere::getCurrentCenter(float time) const
{
	return _centerStart + (time - _timeStart) / (_timeEnd - _timeStart) * (_centerEnd - _centerStart);
}
