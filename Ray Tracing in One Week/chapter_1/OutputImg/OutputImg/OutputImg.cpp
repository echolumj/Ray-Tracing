#include <iostream>
#include <cstdlib>

#define __STDC_LIB_EXT1__ //use sprintf_s instead sprintf

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define COLOR_PASSAGE 4

int main()
{
	int colume = 200; //列
	int row = 100; //行

	unsigned char* data = (unsigned char*)std::malloc(colume * row * COLOR_PASSAGE);

	std::cout << "P3\n" << colume << " " << row << "\n255\n";


	for (int j = 0; j < row - 1; j++)
	{
		for (int i = 0; i < colume; i++)
		{
			float r = i * 1.0f / row;
			float g = j * 1.0f / (row+50);
			float b = j * 1.0f / colume;

			unsigned char colorR = unsigned char(255.99 * r);
			unsigned char colorG = unsigned char(255.99 * g);
			unsigned char colorB = unsigned char(255.99 * b);

			data[j *  colume * COLOR_PASSAGE + i * COLOR_PASSAGE + 0] = colorR;
			data[j *  colume * COLOR_PASSAGE + i * COLOR_PASSAGE + 1] = colorG;
			data[j *  colume * COLOR_PASSAGE + i * COLOR_PASSAGE + 2] = colorB;
			data[j *  colume * COLOR_PASSAGE + i * COLOR_PASSAGE + 3] = 255;

			std::cout << int(colorR) << " " << int(colorG) << " " << int(colorB) << "\n";
		}
	}

	stbi_write_png("write.png", colume, row, COLOR_PASSAGE, data, colume * COLOR_PASSAGE); //200 * 100
	std::free(data);

	return 0;
}