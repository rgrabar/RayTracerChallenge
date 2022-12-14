#pragma once
#include "../Tuple.h"
#include "../Canvas.h"
#include "../Normal.h"

# define TEST_PI           3.14159265358979323846

void drawProjectile() {
	
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


}

void drawClock() {
	// Clock code:

	double radius = 10;

	Canvas c(900, 550);

	c.writePixel(900 / 2, 550 / 2, Color(1, 0, 0));

	double centerX = 900 / 2.f;
	double centerY = 550 / 2.f;

	Matrix  r = rotationZ(0.01745329252);
	Tuple twelve = Tuple::point(0, 10, 0);


	for (int i = 0; i < 360; ++i) {

		c.writePixel(centerX + twelve.x * radius, centerY + twelve.y * radius, Color((1.f / 360.f) * (i + 1.f), 0, 1 - ((1.f / 360.f) * (i + 1.f))));
		twelve = r * twelve;
	}
	c.canvasToImage();

}

void drawRedCircle() {
	// Code for the red circle and for the shaded circle with reflection
	   int canvas_Size = 500;

	   Canvas c(canvas_Size, canvas_Size);
	   auto ray_origin = Tuple::point(0, 0, -5);
	   double wall_z = 10.f;
	   double wall_size = 7.f;
	   auto pixel_size = wall_size / canvas_Size;
	   auto half = wall_size / 2;
	   auto shape = Sphere();

	   shape.material.color = Color(1, 0.2, 1);

	   Light light(Color(1, 1, 1), Tuple::point(-10, 10, -10));

	   //shape.transform = shearing(1, 0, 0, 0, 0, 0) * scale(0.5, 1, 1);

	   for (int y = 0; y < canvas_Size; ++y) {
		   auto world_y = half - pixel_size * y;
		   for(int x = 0; x < canvas_Size; ++x) {
			   auto world_x = -half + pixel_size * x;
			   auto position = Tuple::point(world_x, world_y, wall_z);

			   auto no = position - ray_origin;
			   no = no.normalize();
			   auto r = Ray(ray_origin, no);

			   auto xs = shape.shapeIntersect(r);

			   if (xs.size() != 0) {

				   auto wPoint = r.position(xs[0].t);
				   auto normal = ((Shape*)xs[0].s)->normal(wPoint);
				   auto eye = -r.direction;
				   Material tmp;
				   auto co = lighting( (Shape *)xs[0].s, light, wPoint, eye, normal, 0);

				   c.writePixel(x, y, co);

				   //intersections.emplace_back(&xs[0]);
				   //std::cout << "HIT! \n";
			   }
			   //if (Intersection::hit() != nullptr) {
			   //}
		   }
	   }

	   c.canvasToImage();	   
}


void drawShadowPatternsReflection() {
	
		// CODE FOR SHADOWS CHAPTER, PATTERNS, REFLECTION
		auto plane = Plane();
		auto pat = StripePattern(Color(1, 0, 0), Color(0, 0, 0));
		auto pat1 = StripePattern(Color(0, 1, 0), Color(0, 0, 1));
		pat1.transform = rotationY(TEST_PI / 2);
		plane.material.pattern = new BlendedPattern(&pat, &pat1);
		plane.material.reflective = 0.5;
		//plane.material.pattern = &pat;

		//plane.material.pattern = new CheckerPattern(Color(0.f, 0.f, 0.f), Color(1.f, 1.f, 1.f));
		//plane.material.pattern->transform = scale(0.25, 0.25, 0.25);

		auto plane1 = Plane();
		plane1.transform = translate(0, 0, 3) * rotationY(-TEST_PI / 4.f) * rotationZ(TEST_PI / 2.f);
		//plane1.material.pattern = new RingPattern(Color(1, 0.25098, 0), Color(0, 0, 0));
		plane1.material.pattern = new RadialGradientPattern(Color(0, 1, 0), Color(0, 0, 1));

		//auto plane2 = Plane();
		//plane2.transform = translate(0, 0, 5) * rotationY(TEST_PI / 4) * rotationX(TEST_PI / 2);

		auto middle = Sphere();
		middle.transform = translate(-0.5, 1, 0.5);
		middle.material = Material();
		middle.material.color = Color(0.1, 1, 0.5);
		middle.material.diffuse = 0.7;
		middle.material.specular = 0.3;
		middle.material.pattern = new StripePattern(Color(0.5123, 0.3426, 0.934906), Color(0.934906 , 0.3426, 0.5123));
		middle.material.pattern->transform = rotationZ(TEST_PI / 8) * scale(0.25,0.25,0.25);
		//middle.material.reflective = 0.5;

		auto right = Sphere();
		right.transform = translate(1.5, 0.5, -0.5) * scale(0.5, 0.5, 0.5);
		right.material = Material();
		right.material.color = Color(0.5, 1, 0.1);
		right.material.diffuse = 0.7;
		right.material.specular = 0.3;
		right.material.pattern = new GradientPattern(Color(1, 0, 0), Color(0, 0, 1));
		right.material.pattern->transform = scale(1, 2, 1) * translate(1, 1.5, 1) * rotationZ(TEST_PI / 2);

		auto left = Sphere();
		left.transform = translate(-1.5, 0.33, -0.75) * scale(0.33, 0.33, 0.33);
		left.material = Material();
		left.material.color = Color(1, 0.8, 0.1);
		left.material.diffuse = 0.7;
		left.material.specular = 0.3;
		left.material.pattern = new StripePattern(Color(0, 0, 0), Color(1, 1, 0));

		auto world = World();
		world.light = Light(Color(1, 1, 1), Tuple::point(-10, 10, -10));
		//world.objects.emplace_back(&floor);
		//world.objects.emplace_back(&leftWall);
		//world.objects.emplace_back(&rightWall);
		world.objects.emplace_back(&middle);
		world.objects.emplace_back(&left);
		world.objects.emplace_back(&right);
		world.objects.emplace_back(&plane1);
		world.objects.emplace_back(&plane);
		//world.objects.emplace_back(&plane2);

		Camera cam(550, 450, TEST_PI / 3);
		cam.transform = viewTransformation(Tuple::point(1, 1.5, -8), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
		auto ans = cam.render(world);

		ans.canvasToImage();		
}

void drawBadSmiley() {
	 // shit smiley
	auto plane = Plane();
	plane.transform = rotationZ(0.f);
	plane.material.specular = 0.f;

	auto plane1 = Plane();
	plane1.transform = translate(0.0, 0.f, 5.f) * rotationY(-TEST_PI / 4.f) * rotationZ(TEST_PI / 2.f);
	plane1.material.color = Color(1.0, 1.0, 1.0);
	plane1.material.specular = 0.f;

	plane.material.color = Color(1, 1, 0);

	auto middle = Sphere();
	middle.transform = translate(-0.55, 1.4, -1.25) * scale(0.25, 0.25, 0.25);
	middle.material = Material();
	middle.material.color = Color(1, 1, 0.3);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	auto right = Sphere();
	right.transform = translate(0.3, 1.4, -1.25) * scale(0.25, 0.25, 0.25);
	right.material = Material();
	right.material.color = Color(1, 1, 0.3);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	auto left = Sphere();
	left.transform = rotationX(-TEST_PI / 2) * translate(-0.25, 1, 1) * scale(1, 0.25, 1);
	left.material = Material();
	left.material.color = Color(1, 1, 0);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	auto bottom = Sphere();
	bottom.transform = translate(-0.1, 0.6, -1.25) * scale(0.65, 0.1, 0.25);
	bottom.material = Material();
	bottom.material.color = Color(0.1, 1, 0.5);
	bottom.material.diffuse = 0.7;
	bottom.material.specular = 0.3;


	auto world = World();
	world.light = Light(Color(1, 1, 1), Tuple::point(-10, 10, -10));
	world.objects.emplace_back(&middle);
	world.objects.emplace_back(&left);
	world.objects.emplace_back(&right);
	world.objects.emplace_back(&bottom);
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);

	Camera cam(800, 800, TEST_PI / 1.5);
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	auto ans = cam.render(world);

	ans.canvasToImage();
}

void drawRefractiveSphere() {

	auto world = World();
	world.light = Light(Color(1, 1, 1), Tuple::point(-10, 10, -10));

	auto floor = Plane();
	floor.material.pattern = new CheckerPattern(Color(1, 0.9, 0.9), Color(0, 0.1, 0.1));
	floor.transform = translate(0, -0.1, 0);
	floor.material.specular = 0;
	floor.material.reflective = 0.5;

	auto shape = Sphere();
	shape.transform = scale(0.5, 0.5, 0.5) * translate(1.5, 0.5, 0.5);
	shape.material.color = Color(0, 0, 0.4);
	shape.material.diffuse = 0.0;
	shape.material.specular = 1;
	shape.material.reflective = 0.5;
	shape.material.transparency = 0.9;
	shape.material.refractiveIndex = 1.52;


	world.objects.emplace_back(&floor);
	world.objects.emplace_back(&shape);


	Camera cam(600, 300, TEST_PI / 3);
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	auto ans = cam.render(world);

	ans.canvasToImage();

}

void drawAllShapes() {
	
		auto plane = Plane();
		auto pat = CheckerPattern(Color(1.0, 1.0, 1.0), Color(0.5, 0.5, 0.5));
		plane.material.pattern = &pat;
		//plane.material.pattern = &pat;

		//plane.material.pattern = new CheckerPattern(Color(0.f, 0.f, 0.f), Color(1.f, 1.f, 1.f));
		//plane.material.pattern->transform = scale(0.25, 0.25, 0.25);

		auto plane1 = Plane();
		plane1.transform = translate(0, 0, 3) * rotationY(-TEST_PI / 4.f) * rotationZ(TEST_PI / 2.f);
		//plane1.material.pattern = new RingPattern(Color(1, 0.25098, 0), Color(0, 0, 0));
		plane1.material.pattern = new CheckerPattern(Color(1.0, 1.0, 1.0), Color(0.5, 0.5, 0.5));


		auto plane2 = Plane();
		plane2.transform = translate(0, 0, 5) * rotationY(TEST_PI / 4) * rotationX(TEST_PI / 2);
		plane2.material.pattern = new CheckerPattern(Color(1.0, 1.0, 1.0), Color(0.5, 0.5, 0.5));
		plane2.transform = rotationZ(1.570795) * translate(-15, 0, 0);

		auto middle = Sphere();
		middle.transform = translate(-0.5, 1, 0.5);
		middle.material = Material();
		middle.material.color = Color(0.1, 1, 0.5);
		middle.material.diffuse = 0.7;
		middle.material.specular = 0.3;
		middle.material.pattern = new StripePattern(Color(0.5123, 0.3426, 0.934906), Color(0.934906, 0.3426, 0.5123));
		middle.material.pattern->transform = rotationZ(TEST_PI / 8) * scale(0.25, 0.25, 0.25);
		//middle.material.reflective = 0.5;

		auto right = Sphere();
		right.transform = translate(1.5, 0.5, -0.5) * scale(0.5, 0.5, 0.5);
		right.material = Material();
		right.material.color = Color(0.5, 1, 0.1);
		right.material.diffuse = 0.7;
		right.material.specular = 0.3;
		right.material.pattern = new GradientPattern(Color(1, 0, 0), Color(0, 0, 1));
		right.material.pattern->transform = scale(1, 2, 1) * translate(1, 1.5, 1) * rotationZ(TEST_PI / 2);

		auto left = Sphere();
		left.transform = translate(-1.5, 0.33, -0.75) * scale(0.33, 0.33, 0.33);
		left.material = Material();
		left.material.color = Color(1, 0.8, 0.1);
		left.material.diffuse = 0.7;
		left.material.specular = 0.3;
		left.material.pattern = new RingPattern(Color(0, 0, 0), Color(1, 1, 0));
		left.material.pattern->transform = rotationZ(TEST_PI / 2) * scale(0.33, 0.33, 0.33);


		auto cube = Cube();
		cube.transform = translate(-3, 0.5, -1.5) * scale(0.5, 0.5, 0.5);
		cube.material.pattern = new CheckerPattern(Color(0, 1, 0), Color(0, 1, 1));


		auto kanta = Sphere();
		kanta.transform = translate(1, 0.5, -1.5) * scale(0.5, 0.5, 0.5);
		kanta.material = Material();
		kanta.material.color = Color(0.1, 0.1, 0.1);
		kanta.material.transparency = 1;
		kanta.material.refractiveIndex = 1.5;

		auto cilindro = Cylinder();
		cilindro.minimum = 0;
		cilindro.maximum = 1;
		cilindro.transform = translate(3, 0, -3.1) * scale(1, 0.1, 1);
		cilindro.material.color = Color(1, 0, 0);

		auto cilindro1 = Cylinder();
		cilindro1.minimum = 0;
		cilindro1.maximum = 1;
		cilindro1.transform = translate(3, 0, -3.1) * scale(0.8, 0.1, 0.8);
		cilindro1.material.color = Color(1, 0, 0);

		auto cilindro2 = Cylinder();
		cilindro2.minimum = 0;
		cilindro2.maximum = 1;
		cilindro2.transform = translate(3, 0, -3.1) * scale(0.6, 0.1, 0.6);
		cilindro2.material.color = Color(1, 0.63529, 0);

		auto cilindro3 = Cylinder();
		cilindro3.minimum = 0;
		cilindro3.maximum = 1;
		cilindro3.transform = translate(3, 0, -3.1) * scale(0.4, 0.4, 0.4);
		cilindro3.material.color = Color(0.99608, 0.96471, 0.06275);
		cilindro3.closed = true;
		cilindro3.material.pattern = new GradientPattern(Color(0.99608, 0.96471, 0.06275), Color(1, 0, 0));
		cilindro3.material.pattern->transform = scale(1, 2, 1) * translate(1, 1.5, 1) * rotationZ(TEST_PI / 2);

		auto cilindro4 = Cylinder();
		cilindro4.minimum = 0;
		cilindro4.maximum = 1;
		cilindro4.transform = translate(3, 0, -3.1) * scale(0.2, 0.6, 0.2);
		cilindro4.material.color = Color(0, 1, 0);
		cilindro4.closed = true;

		auto cone = Cone();
		cone.minimum = -1;
		cone.maximum = 0;
		cone.transform = translate(3, 0.9, -3.1) * scale(0.2, 0.3, 0.2);
		cone.material.color = Color(0, 1, 0);
		cone.closed = true;

		auto world = World();
		//world.light = Light(Color(1, 1, 1), Tuple::point(-5, 10, -10));
		world.light = Light(Color(1, 1, 1), Tuple::point(4, 5, -4.1));
		//world.objects.emplace_back(&floor);
		//world.objects.emplace_back(&leftWall);
		//world.objects.emplace_back(&rightWall);
		world.objects.emplace_back(&middle);
		world.objects.emplace_back(&left);
		world.objects.emplace_back(&right);
		world.objects.emplace_back(&plane1);
		world.objects.emplace_back(&plane);
		world.objects.emplace_back(&kanta);
		world.objects.emplace_back(&cube);
		world.objects.emplace_back(&cilindro);
		world.objects.emplace_back(&cilindro1);
		world.objects.emplace_back(&cilindro2);
		world.objects.emplace_back(&cilindro3);
		world.objects.emplace_back(&cilindro4);
		world.objects.emplace_back(&cone);
		//world.objects.emplace_back(&plane2);
		//world.objects.emplace_back(&plane2);

		Camera cam(1920, 1580, TEST_PI / 3);
		cam.transform = viewTransformation(Tuple::point(5.0, 1.5, -5.5), Tuple::point(0.0, 0.7, 0.0), Tuple::vector(0, 1, 0));
		auto ans = cam.render(world);

		ans.canvasToImage();
		

}