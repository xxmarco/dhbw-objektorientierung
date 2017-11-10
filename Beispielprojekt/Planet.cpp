#include "stdafx.h"
#include "Planet.h"

Planet::Planet(double x, double y, double mass, std::string img)
	: x(x)
	, y(y)
	, mass(mass)
	, img(img)
{

}

void Planet::draw() {
	img.draw_rot(x, y, 0.0, 0.0, 0.5, 0.5, 0.1, 0.1);
}
