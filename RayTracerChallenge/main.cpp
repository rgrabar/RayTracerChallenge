#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "Tuple.h"
#include "Matrix.h"
#include "Transformations.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Normal.h"
#include "Arena.h"

#include <chrono>
using namespace std::chrono;

# define TEST_PI           3.14159265358979323846  /* pi */

int main() {

	auto start = high_resolution_clock::now();


	/*
	// CODE FOR THE PROJECTILE: 
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
	 
	// Clock code: 
	 
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
	 // Code for the red circle
	int canvas_Size = 100;

	Canvas c(100, 100);
	auto ray_origin = Tuple::point(0, 0, -5);
	float wall_z = 10.f;
	float wall_size = 7.f;
	auto pixel_size = wall_size / canvas_Size;
	auto half = wall_size / 2;
	auto shape = Sphere();

	shape.material.color = Color(1, 0.2, 1);

	Color lightColor(1, 1, 1);
	auto lightPoint = Tuple::point(-10, 10, -10);

	Light light(lightColor, lightPoint);



	//shape.transform = shearing(1, 0, 0, 0, 0, 0) * scale(0.5, 1, 1);
		for (int y = 0; y < canvas_Size; ++y) {
		auto world_y = half - pixel_size * y;
		for(int x = 0; x < canvas_Size; ++x) {
			auto world_x = -half + pixel_size * x;
			auto position = Tuple::point(world_x, world_y, wall_z);

			auto no = position - ray_origin;
			no = no.normalize();
			auto r = Ray(ray_origin, no);
			
			auto xs = intersection(r, &shape);

			if (xs.size() != 0) {

				auto wPoint = r.position(xs[0].t);
				// TODO: i ako je tocno ca delan
				auto normal = normal_at((*(Sphere *)xs[0].s), wPoint);
				auto eye = -r.direction;
				Material tmp;
				auto co =  (*(Sphere *)xs[0].s).material.lighting(light, wPoint, eye, normal);
				c.writePixel(x, y, co);

				//intersections.emplace_back(&xs[0]);
				//std::cout << "HIT! \n";
			}
			//if (Intersection::hit() != nullptr) {
			//}
		}
	}

	std::cout << "Traced the image \n";

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	std::cout << duration.count() << std::endl;

	std::cout << "SAVING TO PPM \n";
	c.canvasToImage();

	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	std::cout << duration.count() << std::endl;
	

	return 0;
}