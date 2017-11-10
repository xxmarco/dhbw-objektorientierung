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
		// Rakete startet in der Mitte des Bildschirmes
		, x(graphics().width() / 2.0)
	{
		set_caption("Gosu Tutorial Game mit Git");

		// Erzeuge Planeten
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

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		// Geschwindigkeit führt zu Positionsänderung
		x += speedx * DT;
		y += speedy * DT;

		// Beschleunigung während "W" gedrückt
		if (input().down(Gosu::KB_W)) {
			accel += 0.00001;
		}
		else {
			accel -= 0.00002;
		}

		// Maximale Beschleunigung
		accel = Gosu::clamp(accel, 0.0, 0.0001);

		// Geschwindigkeit wird in Flugrichtung geändert
		speedx += Gosu::offset_x(rot, accel);
		speedy += Gosu::offset_y(rot, accel);

		// Planeten ziehen Raumschiff an
		for (auto planet : planets) {

			// Entfernung im Quadrat
			double dist = Gosu::distance_sqr(x, y, planet.x, planet.y);

			// Winkel des Vektors vom Raumschiff zum Planet
			double angle = Gosu::angle(x, y, planet.x, planet.y);

			// Anziehungskraft
			double pull = planet.mass / dist;

			// Kollision
			if (dist < 1000) {
				speedx = -Gosu::offset_x(angle, pull);
				speedy = -Gosu::offset_y(angle, pull);
				break;
			}
			speedx += Gosu::offset_x(angle, pull);
			speedy += Gosu::offset_y(angle, pull);
		}

		// Raumschiff in Richtung Mauszeiger drehen
		double angle = Gosu::angle(x, y, input().mouse_x(), input().mouse_y());
		rot -= Gosu::angle_diff(angle, rot) / 36.0;
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}