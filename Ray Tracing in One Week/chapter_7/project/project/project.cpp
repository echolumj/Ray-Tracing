#include <iostream>
#include <float.h>
#include  <random>
#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include "camera.h"

#define IMAGE_WIDTH  200
#define IMAGE_HEIGHT 100
#define SAMPLE_NUM 50

const float gama = 2.2f;

std::random_device e;
std::uniform_real_distribution<float> random(0, 1);

vec3 random_in_unit_sphere(void)
{
	vec3 p;
	do {
		p = 2.0 * vec3(random(e), random(e), random(e));
	} while (dot(p,p) >= 1.0f);
	return p;
}

vec3 color(const ray& r, hitable *world)
{ 
	hit_record record;
	if (world->hit(r, 0.0, FLT_MAX, record))
	{
		vec3 reflect = record.normal + random_in_unit_sphere();
		return  0.5 * color(ray(record.p, reflect), world);
	}

	//2.no intersection, return background
	vec3 unitDir = unit_vector(r.get_direction());
	float t = (unitDir.y() + 1.0f) * 0.5f; //from (-1,1) to (0,1) 
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);//linear blend
}

int main()
{
	std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

	camera* myCamera = new camera();

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitableList(list, 2);

	for(int j = IMAGE_HEIGHT-1; j >= 0; j--)
		for (int i = 0; i < IMAGE_WIDTH; i++)
		{
			vec3 myColor = vec3(0.0, 0.0, 0.0);
			for (int k = 0; k < SAMPLE_NUM; k++)
			{
				float u = float(i + random(e))/ float(IMAGE_WIDTH);
				float v = float(j + random(e))/ float(IMAGE_HEIGHT);

				ray r = myCamera->get_ray(u, v);
				myColor += color(r, world);
			}
			myColor = myColor / SAMPLE_NUM;
			int colR = int(255.99f * std::powf(myColor.r(), 1.0f/gama));
			int colG = int(255.99f * std::powf(myColor.g(), 1.0f/gama));
			int colB = int(255.99f * std::powf(myColor.b(), 1.0f/gama));

			std::cout << colR << " " << colG << " " << colB << std::endl;
		}

	delete list[0];
	delete list[1];
	delete myCamera;

	return 0;
}

