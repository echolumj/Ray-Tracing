#include <iostream>
#include <float.h>
#include  <random>
#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#define IMAGE_WIDTH  600
#define IMAGE_HEIGHT 300
#define SAMPLE_NUM 100
#define RECURSIVE_DEPTH 50
#define OBJECT_NUM 4

const float gama = 2.f;

std::random_device e;
std::uniform_real_distribution<float> random(0, 1);

vec3 color(const ray& r, hitable *world, int depth)
{ 
	hit_record record;
	if (world->hit(r, 0.001, FLT_MAX, record))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < RECURSIVE_DEPTH && record.matPtr->scatter(r, record, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth+1);
		}
		else
		{
			return vec3(0.0, 0.0, 0.0);
		}
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

	hitable *list[OBJECT_NUM];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.0));

	hitable *world = new hitableList(list, OBJECT_NUM);

	for(int j = IMAGE_HEIGHT-1; j >= 0; j--)
		for (int i = 0; i < IMAGE_WIDTH; i++)
		{
			vec3 myColor = vec3(0.0, 0.0, 0.0);
			for (int k = 0; k < SAMPLE_NUM; k++)
			{
				float u = float(i + random(e))/ float(IMAGE_WIDTH);
				float v = float(j + random(e))/ float(IMAGE_HEIGHT);

				ray r = myCamera->get_ray(u, v);
				myColor += color(r, world, 0);
			}
			myColor = myColor / SAMPLE_NUM;
			int colR = int(255.99f * std::powf(myColor.r(), 1.0f/gama));
			int colG = int(255.99f * std::powf(myColor.g(), 1.0f/gama));
			int colB = int(255.99f * std::powf(myColor.b(), 1.0f/gama));

			std::cout << colR << " " << colG << " " << colB << std::endl;
		}

	for(int i = 0; i < OBJECT_NUM; i++)
		delete list[i];

	delete myCamera;

	return 0;
}

