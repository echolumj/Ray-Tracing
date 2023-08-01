﻿#include <iostream>
#include <float.h>
#include  <random>
#include <thread>
#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#define IMAGE_WIDTH  1200
#define IMAGE_HEIGHT 800
#define SAMPLE_NUM 100
#define RECURSIVE_DEPTH 50
#define OBJECT_NUM 5

const float gama = 2.2f;

std::random_device e;
std::uniform_real_distribution<float> random(0, 1);

//scene
hitable *random_scene(void)
{
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000.f, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = random(e);
			vec3 center(a + 0.9 * random(e), 0.2, b + 0.9 * random(e));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)//diffuse
				{
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(random(e)*random(e), random(e)*random(e), random(e)*random(e))));
				}
				else if (choose_mat < 0.95) //metal
				{
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(random(e)+1), 0.5*(random(e) + 1), 0.5*(random(e) + 1)), 0.5 * random(e)));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectrics(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectrics(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitableList(list, i);
}

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

	float aperture = 0.1f;

	vec3 lookFrom = vec3(13, 2, 3);
	vec3 lookAt = vec3(0, 0, 0);
	float focus_dist = 10.0;
	camera* myCamera = new camera(lookFrom, lookAt, vec3(0,1,0), 20, IMAGE_WIDTH * 1.0 /IMAGE_HEIGHT, aperture , focus_dist);

	hitable *world = random_scene();

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

	//for(int i = 0; i < ; i++)
	//	delete list[i];

	delete myCamera;

	return 0;
}

