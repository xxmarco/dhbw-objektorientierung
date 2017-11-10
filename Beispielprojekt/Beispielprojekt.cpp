#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>

#include "Planet.h"

const double DT = 100.0;

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(800, 600)
		, bild("rakete.png")
		, x(graphics().width() / 2.0)
	{
		set_caption("Gosu Tutorial Game mit Git");
		planets.push_back(Planet(200.0, 200.0, 0.1, "planet1.png"));
		planets.push_back(Planet(600.0, 200.0, 0.1, "planet2.png"));
		planets.push_back(Planet(400.0, 500.0, 0.1, "planet3.png"));
	}

	void draw() override
	{
		bild.draw_rot(x, y, 10.0,
			rot, // Rotationswinkel in Grad
			0.5, 0.5 // Position der "Mitte"
		);

		graphics().draw_line(x, y, Gosu::Color::GREEN, input().mouse_x(), input().mouse_y(), Gosu::Color::GREEN, -10.0);

		for (auto planet : planets) {
			planet.draw();
		}
	}

	double rot = 0.0;
	double x = 400.0;
	double y = 300.0;
	double speedx = 0.0;
	double speedy = 0.0;
	double accel = 0.0;
	std::vector<Planet> planets;

	void update() override
	{
		x += speedx * DT;
		y += speedy * DT;
		if (input().down(Gosu::KB_W)) {
			accel += 0.00001;
		}
		else {
			accel -= 0.00002;
		}
		accel = Gosu::clamp(accel, 0.0, 0.0001);
		speedx += Gosu::offset_x(rot, accel);
		speedy += Gosu::offset_y(rot, accel);

		for (auto planet : planets) {
			double dist = Gosu::distance_sqr(x, y, planet.x, planet.y);
			double angle = Gosu::angle(x, y, planet.x, planet.y);
			double pull = planet.mass / dist;
			// collision
			if (dist < 1000) {
				speedx = -Gosu::offset_x(angle, pull);
				speedy = -Gosu::offset_y(angle, pull);
				break;
			}
			speedx += Gosu::offset_x(angle, pull);
			speedy += Gosu::offset_y(angle, pull);
		}

		double angle = Gosu::angle(x, y, input().mouse_x(), input().mouse_y());
		rot -= Gosu::angle_diff(angle, rot) / 36.0;
	}
};

int main()
{
	GameWindow window;
	window.show();
}