#include "stdafx.h"
#include "Vektor2d.h"
#include "Gosu/Gosu.hpp"


Vektor2d::Vektor2d()
{
}

Vektor2d::Vektor2d(double x, double y)
	:x(x), y(y)
{
}


Vektor2d::~Vektor2d()
{
}

double Vektor2d::get_x() const
{
	return x;
}

double Vektor2d::get_y() const
{
	return y;
}

Vektor2d Vektor2d::operator+(const Vektor2d& other) const
{
	return Vektor2d(other.x + x, other.y + y);
}

Vektor2d& Vektor2d::operator+=(const Vektor2d& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vektor2d Vektor2d::operator-(const Vektor2d& other) const
{
	return Vektor2d(other.x - x, other.y - y);
}

Vektor2d& Vektor2d::operator-=(const Vektor2d& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vektor2d Vektor2d::operator*(const double& d) const
{
	return Vektor2d(x * d, y * d);
}

Vektor2d& Vektor2d::operator*=(const double& d)
{
	x *= d;
	y *= d;
	return *this;
}

Vektor2d Vektor2d::operator/(const double& d) const
{
	return Vektor2d(x * d, y * d);
}

Vektor2d& Vektor2d::operator/=(const double& d)
{
	x /= d;
	y /= d;
	return *this;
}

double Vektor2d::length_squared() const
{
	return Gosu::distance_sqr(0, 0, x, y);
}

double Vektor2d::angle(const Vektor2d& other) const
{
	return Gosu::angle(x, y, other.x, other.y);
}

Vektor2d Vektor2d::from_angle(double angle, double speed)
{
	return Vektor2d(
		Gosu::offset_x(angle, speed),
		Gosu::offset_y(angle, speed)
	);
}

std::ostream& operator<<(std::ostream& o, const Vektor2d& v)
{
	return o << v.get_x() << "," << v.get_y();
}
