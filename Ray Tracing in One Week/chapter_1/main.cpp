#include <iostream>

int main()
{
	int colume = 200; //ÁÐ
	int row = 100; //ÐÐ
	std::count << "P3\n" << row << " " << colume << "\n255\n";

	for (int j = row - 1; j >= 0; j--)
	{
		for (int i = 0; i < colume; i++)
		{
			float r = i * 1.0f / colume;
			float g = j * 1.0f / row;
			float b = 0.2;

			int colorR = int(255.99 * r);
			int colorG = int(255.99 * g);
			int colorB = int(255.99 * b);

			std::cout << colorR << " " << colorG << " " << colorB << "\n";
		}
	}

	return 0;
}