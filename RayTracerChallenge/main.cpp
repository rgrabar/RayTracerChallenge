#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Tuple.h"
#include "Matrix.h"
#include "Transformations.h"
#include "Sphere.h"
#include "Intersection.h"

# define TEST_PI           3.14159265358979323846  /* pi */

int main() {
	/*
	* CODE FOR THE PROJECTILE: 
	Canvas c(900, 550);
	
	Tuple start = Tuple::point(0.f, 1.f, 0.f);
	Tuple velocity = Tuple::vector(1.f, 1.8f, 0.f);
	velocity = velocity.normalize() * 11.25;

	Tuple gravity = Tuple::vector(0.0, -0.1, 0.0);
	Tuple wind = Tuple::vector(-0.01, 0.0, 0.0);

	int i = 0;
	while(start.y >= 0.0){
		//std::cout << "x: " << (int)start.x << " " << " y: " << c.h - (int)start.y << std::endl;
		c.writePixel((int)start.x, c.h - (int)start.y, Color(1, 0.8, 0.6));
		start = start + velocity;
		velocity = velocity + gravity + wind;
	}

	c.canvasToImage();
	*/

	/*
	* 
	* Clock code: 
	* 
	float radius = 10;

	Canvas c(900, 550);

	c.writePixel(900 / 2, 550 / 2, Color(1, 0, 0));

	float centerX = 900 / 2.f;
	float centerY = 550 / 2.f;

	Matrix  r = rotationZ(0.01745329252);
	Tuple twelve = Tuple::point(0, 10, 0);


	for (int i = 0; i < 360; ++i) {

		c.writePixel(centerX + twelve.x * radius, centerY + twelve.y * radius, Color((1.f / 360.f) * (i + 1.f), 0, 1 - ((1.f / 360.f) * (i + 1.f))));
		twelve = r * twelve;
	}
	c.canvasToImage();

	*/
	
	int canvas_Size = 100;

	Canvas c(100, 100);
	auto ray_origin = Tuple::point(0, 0, -5);
	float wall_z = 10.f;
	float wall_size = 7.f;
	auto pixel_size = wall_size / canvas_Size;
	auto half = wall_size / 2;
	auto shape = Sphere();

	for (int y = 0; y < canvas_Size; ++y) {
		auto world_y = half - pixel_size * y;
		for(int x = 0; x < canvas_Size; ++x) {
			auto world_x = -half + pixel_size * x;
			auto position = Tuple::point(world_x, world_y, wall_z);

			auto no = position - ray_origin;
			no = no.normalize();
			auto r = Ray(ray_origin, no);
			
			auto xs = intersection(r, &shape);
			if(xs.size() != 0)
				intersections.emplace_back(&xs[0]);
				//std::cout << "HIT! \n";
			if (Intersection::hit() != nullptr) {
				c.writePixel(x, y, Color(1, 0, 0));
			}
		}
	}

	c.canvasToImage();



	return 0;
}