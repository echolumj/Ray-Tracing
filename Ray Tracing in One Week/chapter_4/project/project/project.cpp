#include <iostream>
#include "ray.h"

#define IMAGE_WIDTH  200
#define IMAGE_HEIGHT 100

const vec3 sphereCenter = vec3(0.0f, 0.0f, -1.0f);
const float radius = 0.5f;

bool hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.get_origin() - center;
	float a = dot(r.get_direction(), r.get_direction());
	float b = 2.0f * dot(oc, r.get_direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - 4 * a*c;
	return (discriminant > 0.0f);
}

vec3 color(const ray& r)
{ 
	if (hit_sphere(sphereCenter, radius, r))
		return vec3(1.0f, 0.0f, 0.0f);
	vec3 unitDir = unit_vector(r.get_direction());
	float t = (unitDir.y() + 1.0f) * 0.5f; //from (-1,1) to (0,1) 
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);//linear blend
}

int main()
{
	std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

	vec3 lowerLeft(-2, -1, -1);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0, 2, 0);
	vec3 origin(0.0, 0.0, 0.0);

	for(int j = IMAGE_HEIGHT-1; j >= 0; j--)
		for (int i = 0; i < IMAGE_WIDTH; i++)
		{
			float u = float(i) / float(IMAGE_WIDTH);
			float v = float(j) / float(IMAGE_HEIGHT);

			ray r(origin, lowerLeft + u * horizontal + v * vertical);
			vec3 col = color(r); //(0, 1)

			int colR = int(col.r() * 255.99f);
			int colG = int(col.g() * 255.99f);
			int colB = int(col.b() * 255.99f);

			std::cout << colR << " " << colG << " " << colB << std::endl;
		}
}

