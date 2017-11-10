#pragma once

#include <string>
#include <Gosu\Image.hpp>

struct Planet {
	double x, y;
	double mass;
	Gosu::Image img;
	Planet(double x, double y, double mass, std::string img);
	void draw();
};
