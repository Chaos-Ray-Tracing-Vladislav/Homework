#include <iostream>
#include "Image.h"
#include "Vector.h"
#include "Camera.h"

void RandomImage()
{
	int w = 1920;
	int h = 1080;

	int n_small_x = 4;
	int n_small_y = 4;

	int stepX = w / n_small_x;
	int stepY = h / n_small_y;
	Image image(w,h);
	for (int small_i = 0; small_i < n_small_x*n_small_y; small_i++)
	{
		int small_x = small_i % n_small_x;
		int small_y = small_i / n_small_x;
		for (int i = 0; i < stepX*stepY; i++)
		{
			int x =small_x * stepX + i % stepX;
			int y =small_y * stepY + i / stepX;
			
			int r = small_i == 0 ? 0 : 255 / small_i;
			int g = small_i * 16;
			int b = small_i * small_i * 4;
			image.setPixel(x, y, Color(r, g, b));
		}
	}
	image.writePPM("Squares.ppm");
}

void CircleImage()
{
	int w = 1920;
	int h = 1080;

	float radius = 100;

	Image image(w, h);
	Vector2 center(w / 2, h / 2);
	Color circleCol(255, 0, 0);
	Color bg(128, 128, 128);

	for (int i = 0; i < w*h; i++)
	{
		int x = i % w;
		int y = i / w;
		
		Vector2 pos(x, y);
		if ((pos - center).length() < radius)
			image.setPixel(x, y, circleCol);
		else
			image.setPixel(x, y, bg);
		
	}
	image.writePPM("Circle.ppm");
}

void rayImage()
{

	int w = 1920;
	int h = 1080;

	Image image(w, h);
	Camera cam(image,Frame(),90);
	Vector2 center(w / 2, h / 2);
	
	for (int i = 0; i < w * h; i++)
	{
		int x = i % w;
		int y = i / w;
		Ray ray = cam.CastRay(x, y);
		Color col(abs(ray.dir.x*255), abs(ray.dir.y*255), abs(ray.dir.z)*255);
		image.setPixel(x, y, col);
	}
	image.writePPM("Rays.ppm");
}

int main()
{
	RandomImage();
	CircleImage();
	rayImage();
}

