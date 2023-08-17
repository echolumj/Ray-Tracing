#include <iostream>
#include <float.h>
#include  <random>
#include <thread>
#include <ctime>
#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "bvh.h"


#define IMAGE_WIDTH  900
#define IMAGE_HEIGHT 600
#define SAMPLE_NUM 30
#define RECURSIVE_DEPTH 30
#define OBJECT_NUM 13

const float gama = 2.2f;

std::random_device e;
std::uniform_real_distribution<float> random(0, 1);

//scene
void random_scene(hitableList &world)
{
	world.add(std::make_shared<sphere>(vec3(0, -1000, 0), 1000.f, std::make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

	for (int a = -5; a < 5; a++)
	{
		for (int b = -5; b < 5; b++)
		{
			float choose_mat = random(e);
			vec3 center(a + 0.9 * random(e), 0.2, b + 0.9 * random(e));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)//diffuse
				{
					auto center1 = center + vec3(0.0, camera::random_double(0, 0.5), 0.0);
					world.add(std::make_shared<sphere>(0.0, 1.0, center, center1, 0.2, std::make_shared<lambertian>(vec3(random(e)*random(e), random(e)*random(e), random(e)*random(e)))));
				}
				else if (choose_mat < 0.95) //metal
				{
					world.add(std::make_shared<sphere>(center, 0.2f, std::make_shared<metal>(vec3(0.5*(random(e) + 1), 0.5*(random(e) + 1), 0.5*(random(e) + 1)), 0.5 * random(e))));
				}
				else
				{
					world.add(std::make_shared<sphere>(center, 0.2f, std::make_shared<dielectrics>(1.5)));
				}
			}
		}
	}
	world.add(std::make_shared<sphere>(vec3(0, 1, 0), 1.0f, std::make_shared<dielectrics>(1.5)));
	world.add(std::make_shared<sphere>(vec3(-4, 1, 0), 1.0f, std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));
	world.add(std::make_shared<sphere>(vec3(4, 1, 0), 1.0f, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

	//world = hitableList(std::make_shared<bvh>(world));
	return;
}

vec3 color(const ray& r, const hitableList &world, int depth)
{ 
	hit_record record;
	if (world.hit(r, 0.001, FLT_MAX, record))
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

camera* myCamera;
hitableList world;

void threadFunction(int h1, int h2, int w1, int w2)
{
	for (int j = h2 - 1; j >= h1; j--)
		for (int i = w1; i <= w2; i++)
		{
			vec3 myColor = vec3(0.0, 0.0, 0.0);
			for (int k = 0; k < SAMPLE_NUM; k++)
			{
				float u = float(i + random(e)) / float(IMAGE_WIDTH);
				float v = float(j + random(e)) / float(IMAGE_HEIGHT);

				ray r = myCamera->get_ray(u, v);
				myColor += color(r, world, 0);
			}
			myColor = myColor / SAMPLE_NUM;
			int colR = int(255.99f * std::powf(myColor.r(), 1.0f / gama));
			int colG = int(255.99f * std::powf(myColor.g(), 1.0f / gama));
			int colB = int(255.99f * std::powf(myColor.b(), 1.0f / gama));

			std::cout << colR << " " << colG << " " << colB << std::endl;
		}
}

int main()
{
	std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

	clock_t startTime, endTime;
	startTime = clock();
	//std::cout << std::chrono::steady_clock::now() << std::endl;

	float aperture = 0.1f;

	vec3 lookFrom = vec3(13, 2, 3);
	vec3 lookAt = vec3(0, 0, 0);
	float focus_dist = 10.0;
	//camera* 
	myCamera = new camera(lookFrom, lookAt, vec3(0,1,0), 20, IMAGE_WIDTH * 1.0 /IMAGE_HEIGHT, aperture , focus_dist, 0.0, 1.0);

	//hitableList world;
	random_scene(world);
	/*
	int threadNum = 5;

	auto stepHeight = IMAGE_HEIGHT / threadNum;
	auto stepWidth = IMAGE_WIDTH / threadNum;

	std::vector<std::thread> threadS(threadNum);
	for (int i = 0; i < threadNum; ++i)
	{
		threadS[i] =  std::thread(threadFunction, i * stepHeight, (i+1) * stepHeight - 1,
			i * stepWidth, (i + 1) * stepWidth - 1);

	}
	for (int i = 0; i < threadNum; ++i)
	{
		threadS[i].join();
	}
	*/

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
	endTime = clock();//计时结束
	std::cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
	//system("pause");

	return 0;
}

