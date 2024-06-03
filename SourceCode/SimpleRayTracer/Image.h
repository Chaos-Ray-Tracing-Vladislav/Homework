#pragma once
#include "Color.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <format>

class Image {
public:
	const int w, h;
	std::vector<Color> image;

	Image(int w, int h) : w(w), h(h)
	{
		image.insert(image.begin(),w*h,Color());
	}

	void setPixel(int x, int y, Color value)
	{
		if (x > w || x<0 || y>h || y < 0)
		{
			std::invalid_argument("Pixel coordinate is outside of image!");
		}
		image[y * h + x] = value;
	}

	Color getPixel(int x,int y)
	{
		return image.at(y * h + x);
	}

	void clear()
	{
		image.clear();
	}

	void writePPM(std::string name)
	{
		//Write header
		std::ofstream imageFile(name);
		imageFile << "P3\n";
		imageFile << w << " " << h << std::endl;
		imageFile << "255\n";

		//Write image content
		for (int i = 0; i < w * h; i++)
		{
			Color pixel = image.at(i);
			
			imageFile << std::format("{} {} {} \n", pixel.r, pixel.g, pixel.b);
		}

		imageFile.close();
	}
};