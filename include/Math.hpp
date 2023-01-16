#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>

struct vector2f
{
	vector2f(float p_x, float p_y)
	: x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl; 
	}

	float x, y;
};