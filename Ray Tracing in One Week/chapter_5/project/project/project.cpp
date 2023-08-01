#include <iostream>
#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include <float.h>

#define IMAGE_WIDTH  200
#define IMAGE_HEIGHT 100

const vec3 sphereCenter = vec3(0.0f, 0.0f, -1.0f);
const float radius = 0.5f;

vec3 color(const ray& r, hitable *world)
{ 
	hit_record record;
	if (world->hit(r, 0.0, FLT_MAX, record))
	{
		return  0.5 * (record.normal + vec3(1.0, 1.0, 1.0));
	}

	//2.no intersection, return background
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

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable *world = new hitableList(list, 2);

	for(int j = IMAGE_HEIGHT-1; j >= 0; j--)
		for (int i = 0; i < IMAGE_WIDTH; i++)
		{
			float u = float(i) / float(IMAGE_WIDTH);
			float v = float(j) / float(IMAGE_HEIGHT);

			ray r(origin, lowerLeft + u * horizontal + v * vertical);
			vec3 col = color(r,world); //(0, 1)

			int colR = int(col.r() * 255.99f);
			int colG = int(col.g() * 255.99f);
			int colB = int(col.b() * 255.99f);

			std::cout << colR << " " << colG << " " << colB << std::endl;
		}
}

