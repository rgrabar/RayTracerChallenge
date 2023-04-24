#pragma once
#include "../CSGShape.h"
#include "../Camera.h"
#include "../Canvas.h"
#include "../Cone.h"
#include "../Cube.h"
#include "../Cylinder.h"
#include "../Groups.h"
#include "../OBJParser.h"
#include "../Pattern.h"
#include "../Plane.h"
#include "../Shape.h"
#include "../Sphere.h"
#include "../Transformations.h"
#include "../Tuple.h"
#include "../World.h"

# define TEST_PI           3.14159265358979323846

void drawAxes(World& world);

void drawProjectile() {
	
	// CODE FOR THE PROJECTILE:
	Canvas c(900, 900);

	Tuple start = Tuple::point(0.f, 1.f, 0.f);
	Tuple velocity = Tuple::vector(1.f, 1.8f, 0.f);
	velocity = velocity.normalize() * 11.25;

	Tuple gravity = Tuple::vector(0.0, -0.1, 0.0);
	Tuple wind = Tuple::vector(-0.01, 0.0, 0.0);

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

	Canvas c(900, 900);

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
	   int canvas_Size = 900;

	   Canvas c(canvas_Size, canvas_Size);
	   auto ray_origin = Tuple::point(0, 0, -5);
	   double wall_z = 10.f;
	   double wall_size = 7.f;
	   auto pixel_size = wall_size / canvas_Size;
	   auto half = wall_size / 2;
	   auto shape = Sphere();

	   shape.material.color = Color(1, 0.2, 1);

	   PointLight* light = new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10));

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

			   for (auto test : xs.intersections) {

				   auto wPoint = r.position(test->t);
				   auto normal = ((Shape*)test->s)->normal(wPoint);
				   auto eye = -r.direction;
				   Material tmp;
				   auto co = light->lighting(shape.material, &shape, wPoint, eye, normal, 1);

				   c.writePixel(x, y, co);
				   //TODO: figure out why i need this break
				   break;
			   }
				   //intersections.emplace_back(&xs[0]);
				   //std::cout << "HIT! \n";
			   
			   //if (Intersection::hit() != nullptr) {
			   //}
		   }
	   }

	   c.canvasToImage();	   
}

void drawShadowPatternsReflection(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	
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
		world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
		//world.objects.emplace_back(&floor);
		//world.objects.emplace_back(&leftWall);
		//world.objects.emplace_back(&rightWall);
		world.objects.emplace_back(&middle);
		world.objects.emplace_back(&left);
		world.objects.emplace_back(&right);
		world.objects.emplace_back(&plane1);
		world.objects.emplace_back(&plane);
		//world.objects.emplace_back(&plane2);

		Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
		cam.transform = viewTransformation(Tuple::point(1, 1.5, -8), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
		cam.aliasingSamples = aliasing;
		cam.aliasEdges = edge;
		cam.edgeAliasHighlights = highlights;
		cam.aliasingThreshold = threshold;

		cam.render(world);	
}

void drawBadSmiley(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
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
	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
	world.objects.emplace_back(&middle);
	world.objects.emplace_back(&left);
	world.objects.emplace_back(&right);
	world.objects.emplace_back(&bottom);
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);

	Camera cam(width, height, TEST_PI / 1.5, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}


Shape* createRandomSphere(double moveX, double moveZ) {
	auto shape = new Sphere();
	shape->transform = translate(moveX, 0.25, moveZ) * scale(0.25, 0.25, 0.25);
	shape->material.color = Color(random_double(), random_double(), random_double());
	shape->material.diffuse = random_double();
	shape->material.specular = random_double();
	shape->material.reflective = random_double();
	shape->material.transparency = random_double();
	shape->material.shininess = random_double() * 200;

	return shape;
}

void drawRefractiveSphere(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	
	auto world = World();
	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));

	auto floor = Plane();
	floor.material.pattern = new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));
	floor.transform = translate(0, -0.1, 0);
	floor.material.specular = 0;
	floor.material.reflective = 0.5;

	auto shape = Sphere();
	shape.transform = translate(2.5, 0.5, 0.5) * scale(0.5, 0.5, 0.5);
	shape.material.color = Color(1, 1, 1);
	shape.material.diffuse = 0.0;
	shape.material.specular = 1;
	shape.material.reflective = 0.5;
	shape.material.transparency = 0.9;
	shape.material.refractiveIndex = 0;

	auto shape1 = Sphere();
	shape1.transform = translate(1.5, 0.5, 0.5) * scale(0.5, 0.5, 0.5);
	shape1.material.color = Color(1, 1, 1);
	shape1.material.diffuse = 0.0;
	shape1.material.specular = 1;
	shape1.material.reflective = 0.5;
	shape1.material.transparency = 0.9;
	shape1.material.refractiveIndex = 1;

	auto shape2 = Sphere();
	shape2.transform = translate(0.5, 0.5, 0.5) * scale(0.5, 0.5, 0.5);
	shape2.material.color = Color(1, 1, 1);
	shape2.material.diffuse = 0.0;
	shape2.material.specular = 1;
	shape2.material.reflective = 0.5;
	shape2.material.transparency = 0.9;
	shape2.material.refractiveIndex = 2;

	auto shape3 = Sphere();
	shape3.transform = translate(-0.5, 0.5, 0.5) * scale(0.5, 0.5, 0.5);
	shape3.material.color = Color(1, 1, 1);
	shape3.material.diffuse = 0.0;
	shape3.material.specular = 1;
	shape3.material.reflective = 0.5;
	shape3.material.transparency = 0.9;
	shape3.material.refractiveIndex = 3;

	auto shape4 = Sphere();
	shape4.transform = translate(-1.5, 0.5, 0.5) * scale(0.5, 0.5, 0.5);
	shape4.material.color = Color(1, 1, 1);
	shape4.material.diffuse = 0.0;
	shape4.material.specular = 1;
	shape4.material.reflective = 0.5;
	shape4.material.transparency = 0.9;
	shape4.material.refractiveIndex = 4;

	auto shape5 = Sphere();
	shape5.transform = translate(-2.5, 0.5, 0.5) * scale(0.5, 0.5, 0.5);
	shape5.material.color = Color(0.56, 0.58, 0.58);
	shape5.material.diffuse = 0.2775f;
	shape5.material.specular = 0.773911f;
	shape5.material.ambient = 0.23125f;
	shape5.material.reflective = 0.07;
	shape5.material.shininess = 89.6f;
	shape5.material.transparency = 0.0;
	//shape5.material.refractiveIndex = 1;

	world.objects.emplace_back(&floor);
	world.objects.emplace_back(&shape);
	world.objects.emplace_back(&shape1);
	world.objects.emplace_back(&shape2);
	world.objects.emplace_back(&shape3);
	world.objects.emplace_back(&shape4);
	world.objects.emplace_back(&shape5);


	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
	
	/*
	auto world = World();
	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(0, 10, -10)));

	auto floor = Plane();


	//shape.material.refractiveIndex = 1.52;


	world.objects.emplace_back(&floor);

	double moveX = 0; double moveZ = 0;

	auto g = Group();

	for (int j = 0; j < 20; ++j) {
		moveZ += 1;
		moveX = 0;
		for (int i = 0; i < 20; ++i) {
			g.addChild(createRandomSphere(moveX, moveZ));
			moveX += 1;
		}
	}

	g.divide();
	world.objects.emplace_back(&g);
	drawAxes(world);

	Camera cam(width, height, TEST_PI / 3);
	cam.transform = viewTransformation(Tuple::point(10, 5, -10), Tuple::point(10, 1, 10), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	auto ans = cam.render(world);
	ans.canvasToImage();*/

}

void drawAllShapes(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	
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
		world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(4, 5, -4.1)));
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

		Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
		cam.transform = viewTransformation(Tuple::point(5.0, 1.5, -5.5), Tuple::point(0.0, 0.7, 0.0), Tuple::vector(0, 1, 0));
		cam.aliasingSamples = aliasing;
		cam.aliasEdges = edge;
		cam.edgeAliasHighlights = highlights;
		cam.aliasingThreshold = threshold;

		cam.render(world);
}

Sphere* hexagonCorner() {
	auto corner = new Sphere();
	corner->transform = translate(0, 0, -1) * scale(0.25, 0.25, 0.25);
	return corner;
}

Cylinder* hexagonEdge() {
	auto edge = new Cylinder();
	edge->minimum = 0;
	edge->maximum = 1;
	edge->transform = translate(0, 0, -1) * rotationY(-TEST_PI/6) * rotationZ(-TEST_PI/2) * scale(0.25, 1, 0.25);

	return edge;
}

Group* hexagonSide() {
	auto side = new Group();
	side->addChild(hexagonEdge());
	side->addChild(hexagonCorner());
	return side;

}

Group* createHexagon() {
	auto hex = new Group();

	for (int i = 0; i < 6; ++i) {
		auto side = hexagonSide();
		side->transform = rotationY(i * TEST_PI / 3);
		hex->addChild(side);
	}
	return hex;
}

void drawHexagon(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples){
	
	Group* hex = createHexagon();
	Group* hex1 = createHexagon();
	Group* hex2 = createHexagon();

	hex->transform = translate(0, -1, 0);

	hex1->transform = translate(-1., -1, 0) * rotationX(TEST_PI / 2);
	Material m1;
	m1.color = Color(0, 0.63922, 0.42353);
	hex1->setMaterial(m1);

	Material m2;
	m2.color = Color(0, 0.63922, 0.42353);
	hex2->transform = translate(1., -1, 0) * rotationX(TEST_PI / 2);
	m2.color = Color(0, 1, 1);
	hex2->setMaterial(m2);

	Group* mesh = new Group();
	
	double moveX = -2.5;
	double moveY = 3.5;
	double back = 0;
	double forth = 0.25;


	for (int i = 0; i < 50; ++i) {
		if (i % 10 == 0 && i != 0) {
			moveY -= 0.5;
			moveX = -2.5;
			moveX += forth;
			std::swap(back, forth);
		}

		auto tmp = createHexagon();
		tmp->transform = translate(moveX, moveY, 0) * rotationX(TEST_PI / 2) * scale(0.25, 0.25, 0.25);
		auto tmp1 = Material();
		tmp1.color = Color(random_double(), random_double(), random_double());

		tmp->setMaterial(tmp1);
		mesh->addChild(tmp);
		moveX += 0.5;
		
	}
	
	mesh->divide();

	auto world = World();
	//world.light = Light(Color(1, 1, 1), Tuple::point(-5, 10, -10));
	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(4, 5, -4.1)));

	world.objects.emplace_back(hex);
	world.objects.emplace_back(hex1);
	world.objects.emplace_back(hex2);
	world.objects.emplace_back(mesh);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 3.5, -5.5), Tuple::point(0.0, 0.7, 0.0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}



Sphere* createSphereX(double moveX, double moveY, double moveZ) {

	auto sphere = new Sphere();
	sphere->transform = translate(-2 + moveX, -1 + moveY, 0 + moveZ) * scale(0.2, 0.2, 0.2);
	sphere->material = Material();
	sphere->material.color = Color(0.1, 1, 0.5);
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	sphere->material.pattern = new StripePattern(Color(0.5123, 0.3426, 0.934906), Color(0.934906, 0.3426, 0.5123));
	sphere->material.pattern->transform = rotationZ(TEST_PI / 8) * scale(0.25, 0.25, 0.25);

	return sphere;
}

Group* createLayer() {
	Group* g = new Group();
	double moveX = 0;
	double moveY = 0;
	double moveZ = 0;

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int z = 0; z < 5; ++z) {
				g->addChild(createSphereX(moveX, moveY, moveZ));
				moveZ += 0.5;
			}
			moveY += 0.5;
			moveZ = 0;
		}
		moveY = 0;
		moveX += 0.5;
	}
	moveX = 0;

	return g;
}

void sphereCube(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	auto plane = Plane();
	plane.transform = translate(0, -2, 0) * rotationZ(0.f);
	plane.material.specular = 0.f;

	auto plane1 = Plane();
	plane1.transform = translate(0.0, 0.f, 5.f) * rotationY(-TEST_PI / 4.f) * rotationZ(TEST_PI / 2.f);
	plane1.material.color = Color(1.0, 1.0, 1.0);
	plane1.material.specular = 0.f;

	plane.material.color = Color(1, 1, 0);
	auto world = World();

	auto grp = Group();
	auto grp1 = Group();
	auto grp2 = Group();


	//for (int i = 0; i < 5; ++i) {
		//grp.addChild(*createSphereX(move));
		//world.objects.emplace_back(createSphereX(move));
		//move += 0.5;
    //}
	world.objects.emplace_back(createLayer());

	Group* g = createLayer();
	g->transform = translate(2.5, 0, 0);

	Group* g1 = createLayer();
	g1->transform = translate(0, 2.5, 0);

	Group* g2 = createLayer();
	g2->transform = translate(2.5, 2.5, 0);

	Group* g3 = createLayer();
	g3->transform = translate(0, 0, 2.5);

	Group* g4 = createLayer();
	g4->transform = translate(2.5, 0, 2.5);

	Group* g5 = createLayer();
	g5->transform = translate(0, 2.5, 2.5);

	Group* g6 = createLayer();
	g6->transform = translate(2.5, 2.5, 2.5);

	world.objects.emplace_back(g);
	world.objects.emplace_back(g1);
	world.objects.emplace_back(g2);
	world.objects.emplace_back(g3);
	world.objects.emplace_back(g4);
	world.objects.emplace_back(g5);
	world.objects.emplace_back(g6);

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(-5, 5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void sphereCubeDivide(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	//TODO: double check everything in bounding-boxes it's a bit too slow

	auto plane = Plane();
	plane.transform = translate(0, -2, 0) * rotationZ(0.f);
	plane.material.specular = 0.f;

	auto plane1 = Plane();
	plane1.transform = translate(0.0, 0.f, 5.f) * rotationY(-TEST_PI / 4.f) * rotationZ(TEST_PI / 2.f);
	plane1.material.color = Color(1.0, 1.0, 1.0);
	plane1.material.specular = 0.f;

	plane.material.color = Color(1, 1, 0);
	auto world = World();

	double moveX = 0;
	double moveY = 0;
	double moveZ = 0;

	auto g = Group();
	g.material.color = Color(0, 0.63922, 0.42353);

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto s = new Sphere();
				s->transform = translate(-2 + moveX, -1 + moveY, 0 + moveZ) * scale(0.2, 0.2, 0.2);
				g.addChild(s);
				moveZ += 0.5;
			}
			moveZ = 0;
			moveY += 0.5;
		}
		moveY = 0;
		moveX += 0.5;
	}

	auto pattern = new StripePattern(Color(0.5123, 0.3426, 0.934906), Color(0.934906, 0.3426, 0.5123));
	pattern->transform = rotationZ(TEST_PI / 8) * scale(0.25, 0.25, 0.25);
	Material m;
	m.color = Color(0, 0.63922, 0.42353);
	m.pattern = pattern;

	g.setMaterial(m);

	g.divide(50);

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);
	world.objects.emplace_back(&g);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(-5, 5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void drawTeapot(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	OBJParser o("assets/triangles.obj");

	auto g = o.ObjToGroup();
	g->transform = translate(1, -1, -40) * scale(20, 20, 20);
	g->divide();

	auto world = World();
	world.objects.emplace_back(g);

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(10, 15, 20)));

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 20, 50), Tuple::point(0, 10, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void drawAstronaut(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	OBJParser o("assets/astronaut.obj");

	auto g = o.ObjToGroup();
	// without normalizing the obj
	//g->transform = translate(21, 25, -70);
	g->transform = translate(1, -1, -40) * scale(20, 20, 20);
	g->divide();

	auto plane = Plane();
	plane.transform = translate(1, -20, 1) * rotationY(TEST_PI / 4.9f) * scale(7, 7, 7);
	plane.material.specular = 0.f;
	plane.material.reflective = 0.3f;
	plane.material.pattern = new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));

	auto plane1 = Plane();
	// without normalizing the obj
	//plane1.transform = translate(-20, -26, -171) * rotationX(TEST_PI / 2);
	plane1.transform = translate(1, 1, -100) * rotationX(TEST_PI / 2);
	plane1.material.color = Color(1.0, 0.9, 0.9);
	plane1.material.specular = 0.f;

	auto world = World();
	world.objects.emplace_back(g);
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);


	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(10, 15, 20)));


	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 20, 50), Tuple::point(0, 10, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void drawDragon	(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	OBJParser o("assets/dragon.obj");

	auto g = o.ObjToGroup();
	g->transform = scale(20, 20, 20);
	std::cout << "dividing\n";
	g->divide();
	//g->material.color = Color(0, 0.63922, 0.42353);
	Material m;
	m.color = Color(0, 0.63922, 0.42353);

	g->setMaterial(m);

	auto world = World();
	world.objects.emplace_back(g);

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(0, 15, 20)));

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 20, 50), Tuple::point(0, 10, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;


	cam.render(world);
}


void drawCSKnife(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	OBJParser o("assets/Bayonet.obj");

	auto g = o.ObjToGroup();
	g->transform = rotationY(TEST_PI / 2) * translate(-8, 10, 0) * scale(24, 24, 24);
	std::cout << "dividing\n";
	g->divide();

	auto world = World();
	world.objects.emplace_back(g);

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(0, 15, 20)));

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 20, 50), Tuple::point(0, 10, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

/* 
//TODO: does this scene have wrong shadows?
void drawAstronaut() {
	OBJParser o("astronaut.obj");

	auto g = o.ObjToGroup();
	//g->transform = translate(21, 25, -70);
	g->transform = translate(1, -1, -10) * scale(20, 20, 20);
	g->divide();

	auto plane = Plane();
	plane.transform = translate(1, -30, 1) * rotationY(TEST_PI / 4.9f) * scale(7, 7, 7);
	plane.material.specular = 0.f;
	plane.material.reflective = 0.3f;
	plane.material.pattern = new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));

	auto plane1 = Plane();
	//plane1.transform = translate(-20, -26, -171) * rotationX(TEST_PI / 2);
	plane1.transform = translate(1, 1, -50) * rotationX(TEST_PI / 2);
	plane1.material.color = Color(1.0, 0.9, 0.9);
	plane1.material.specular = 0.f;

	auto world = World();
	world.objects.emplace_back(g);
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);


	world.light = Light(Color(1, 1, 1), Tuple::point(-20, 30, 20));


	Camera cam(200, 200, TEST_PI / 3);
	cam.transform = viewTransformation(Tuple::point(0, 20, 50), Tuple::point(0, 10, 0), Tuple::vector(0, 1, 0));
	auto ans = cam.render(world);

	ans.canvasToImage();
}

*/

void CSGScene(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	auto sphere = Sphere();
	sphere.material.color = Color(1, 0, 0);
	auto cone = Cone();
	cone.minimum = -1;
	cone.maximum = 1;
	cone.closed = true;
	cone.material.color = Color(0.126587, 0.13865, 0.932786);

	auto cone1 = Cone();
	cone1.minimum = -1;
	cone1.maximum = 0;
	cone1.closed = true;
	cone1.transform = scale(1, 2, 1);

	auto cylinder = Cylinder();
	cylinder.minimum = -1;
	cylinder.maximum = 1;
	cylinder.closed = true;
	cylinder.material.color = Color(0.126587, 0.13865, 0.932786);
	cylinder.transform = scale(0.5, 0.5, 1) * rotationX(TEST_PI / 2);

	auto csg = CSGShape(CSGOperation::OPERATION::UNION, &cylinder, &cone);
	auto csg1 = CSGShape(CSGOperation::OPERATION::DIFFERENCE, &csg, &sphere);
	csg1.transform = translate(3, 0, 0);

	auto cube = Cube();
	cube.transform = translate(-3, 0, 3);
	cube.material.color = Color(0.215, 0.6489, 0.948);

	auto sphere1 = Sphere();
	sphere1.transform = translate(-3, 1, 2.5);
	sphere1.material.pattern = new UVCheckers(8, 8, Color(1, 1, 1), Color(0, 0, 0));
	sphere1.optOutShadow = 1;

	auto csg2 = CSGShape(CSGOperation::OPERATION::DIFFERENCE, &cube, &sphere1);

	auto world = World();

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));

	world.objects.emplace_back(&csg1);
	world.objects.emplace_back(&csg2);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(-5, 5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void areaLightScene(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	auto world = World();

	auto corner = Tuple::point(-1, 2, 4);
	auto v1 = Tuple::vector(2, 0, 0);
	auto v2 = Tuple::vector(0, 2, 0);

	auto light = AreaLight(corner, v1, 10, v2, 10, Color(1.5, 1.5, 1.5));
	light.jitter = true;
	light.isSoft = true;

	//auto light = PointLight(Color(1.5, 1.5, 1.5), Tuple::point(-1, 2, 4));

	auto plane = Plane();
	plane.material.color = Color(1, 1, 1);
	plane.material.ambient = 0.025;
	plane.material.diffuse = 0.67;
	plane.material.specular = 0.;

	auto sphere = Sphere();
	sphere.transform = translate(0.5, 0.5, 0) * scale(0.5, 0.5, 0.5);
	sphere.material.color = Color(1, 0, 0);
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.6;
	sphere.material.specular = 0.;
	sphere.material.reflective = 0.3;

	auto sphere1 = Sphere();
	sphere1.transform = translate(-0.25, 0.33, 0) * scale(0.33, 0.33, 0.33);
	sphere1.material.color = Color(0.5, 0.5, 1);
	sphere1.material.ambient = 0.1;
	sphere1.material.diffuse = 0.6;
	sphere1.material.specular = 0.;
	sphere1.material.reflective = 0.3;

	auto cube = Cube();

	cube.material.color = Color(1.5, 1.5, 1.5);
	cube.material.ambient = 1;
	cube.material.diffuse = 0;
	cube.material.specular = 0;

	cube.transform = translate(0, 3, 4) * scale(1, 1, 0.01);
	cube.optOutShadow = true;

	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&sphere);
	world.objects.emplace_back(&sphere1);
	world.objects.emplace_back(&cube);

	world.lights.emplace_back(&light);

	//drawAxes(world);

	Camera cam(width, height, 0.7854, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(-3, 1, 2.5), Tuple::point(0, 0.5, 0), Tuple::vector(0, 1, 0));
	//cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void spotLightScene(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {
	auto plane = Plane();
	plane.transform = rotationY(TEST_PI / 4.9f) * scale(0.4, 0.4, 0.4);
	plane.material.color = Color(1, 1, 1);
	plane.material.ambient = 0.025;
	plane.material.diffuse = 0.67;
	plane.material.specular = 0.;

	auto sphere = Sphere();
	sphere.transform = translate(0, 2, 0);
	sphere.material.color = Color(0.1, 0.4, 0.9);
	//sphere.optOutShadow = true;

	auto world = World();

	auto spotlight = new SpotLight(Color(1, 1, 1), Tuple::point(-10, 10, 0), Tuple::point(0., 0., 0.), TEST_PI / 6, 100, 1);
	spotlight->isSoft = 1;
	spotlight->fadeIntensity = 1;

	auto spotlight1 = new SpotLight(Color(1, 0, 0), Tuple::point(10, 10, 0), Tuple::point(10., 0., 6.), TEST_PI / 20, 100, 1);
	spotlight1->fadeIntensity = 100;
	spotlight1->isSoft = 0;

	auto spotlight2 = new SpotLight(Color(0, 1, 0), Tuple::point(10, 10, 0), Tuple::point(11., 0., 6.), TEST_PI / 20, 100, 1);
	spotlight2->fadeIntensity = 100;
	spotlight2->isSoft = 0;

	auto spotlight3 = new SpotLight(Color(0, 0, 1), Tuple::point(10, 10, 0), Tuple::point(10., 0., 5.), TEST_PI / 20, 100, 1);
	spotlight3->fadeIntensity = 100;
	spotlight3->isSoft = 1;

	auto cube = Cube();

	cube.transform = translate(10.5, 1, 5.5) * scale(0.25, 0.25, 0.25);

	world.lights.emplace_back(spotlight);
	world.lights.emplace_back(spotlight1);
	world.lights.emplace_back(spotlight2);
	world.lights.emplace_back(spotlight3);

	world.objects.emplace_back(&cube);
	world.objects.emplace_back(&sphere);
	world.objects.emplace_back(&plane);

	//drawAxes(world);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	cam.transform = viewTransformation(Tuple::point(0, 10, -12), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	//cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void aliasingScene(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	auto plane = Plane();
	//plane.transform = /*rotationY(TEST_PI / 4.9f) * scale(0.4, 0.4, 0.4);*/
	plane.material.specular = 0.f;
	plane.material.reflective = 0.3f;
	//plane.material.pattern = new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));
	//plane.material.pattern = new StripePattern(Color(1, 1, 1), Color(0, 0, 0));
	auto pat = StripePattern(Color(1, 0, 0), Color(0, 0, 0));
	pat.transform = scale(0.5, 0.5, 0.5) * rotationY(TEST_PI / 6);
	auto pat1 =  RingPattern(Color(0, 1, 0), Color(0, 0, 1));
	pat1.transform = scale(0.3, 0.3, 0.3) * rotationZ(TEST_PI / 2);
	//plane.material.pattern = new BlendedPattern(&pat, &pat1);
	plane.material.pattern = new RingPattern(&pat, &pat1);
	//plane.material.pattern->transform = scale(1.5, 1.5, 1.5);
	//plane.material.pattern = &pat;

	auto plane1 = Plane();
	plane1.transform = translate(0, 0, 5) * rotationX(TEST_PI / 2);
	plane1.material.color = Color(1.0, 0.9, 0.9);
	plane1.material.specular = 0.f;

	auto sphere = Sphere();
	sphere.transform = translate(-0.5, 1, 0.5);
	sphere.material.color = Color(0.1, 0.4, 0.9);
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.3;
	sphere.material.reflective = 0.8;
	
	//sphere.material.pattern = new StripePattern(Color(1, 0, 0), Color(0, 0, 0));
	//sphere.material.pattern->transform = scale(0.25, 0.25, 0.25) * rotationZ(TEST_PI / 3);

	auto world = World();

	//auto spotlight = new SpotLight(Color(1, 1, 1), Tuple::point(0, 10, 0), Tuple::point(0., 0., 0.), TEST_PI / 6);
//	spotlight->fadeIntensity = 1;

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
	//world.lights.emplace_back(new Light(Color(0.4, 0.4, 0.4), Tuple::point(10, 10, -10)));
	//world.lights.emplace_back(spotlight);
	world.objects.emplace_back(&sphere);
	world.objects.emplace_back(&plane);
	world.objects.emplace_back(&plane1);

	drawAxes(world);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	//cam.transform = viewTransformation(Tuple::point(0, 10, -15), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;

	cam.render(world);
}

void cubeTest(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	auto world = World();

	world.lights.emplace_back(new PointLight(Color(0.25, 0.25, 0.25), Tuple::point(0, 100, -100)));
	world.lights.emplace_back(new PointLight(Color(0.25, 0.25, 0.25), Tuple::point(0, -100, -100)));
	world.lights.emplace_back(new PointLight(Color(0.25, 0.25, 0.25), Tuple::point(-100, 0, -100)));
	world.lights.emplace_back(new PointLight(Color(0.25, 0.25, 0.25), Tuple::point(100, 0, -100)));
	
	AlignCheck front = AlignCheck(Color(0, 1, 1), Color(1, 0, 0), Color(1, 1, 0), Color(1, 0.5, 0), Color(0, 1, 0));
	AlignCheck back = AlignCheck(Color(0, 1, 0), Color(1, 0, 1), Color(0, 1, 1), Color(1, 1, 1), Color(0, 0, 1));
	AlignCheck left = AlignCheck(Color(1, 1, 0), Color(0, 1, 1), Color(1, 0, 0), Color(0, 0, 1), Color(1, 0.5, 0));
	AlignCheck right = AlignCheck(Color(1, 0, 0), Color(1, 1, 0), Color(1, 0, 1), Color(0, 1, 0), Color(1, 1, 1));
	AlignCheck up = AlignCheck(Color(1, 0.5, 0), Color(0, 1, 1), Color(1, 0, 1), Color(1, 0, 0), Color(1, 1, 0));
	AlignCheck down = AlignCheck(Color(1, 0, 1), Color(1, 0.5, 0), Color(0, 1, 0), Color(0, 0, 1), Color(1, 1, 1));

	CubeMap map = CubeMap(&front, &back, &left, &right, &up, &down);


	auto cube = Cube();
	auto cube1 = Cube();
	auto cube2 = Cube();
	auto cube3 = Cube();
	auto cube4 = Cube();
	auto cube5 = Cube();
	auto cube6 = Cube();
	auto cube7 = Cube();

	cube.material.pattern = &map;
	cube1.material.pattern = &map;
	cube2.material.pattern = &map;
	cube3.material.pattern = &map;
	cube4.material.pattern = &map;
	cube5.material.pattern = &map;
	cube6.material.pattern = &map;
	cube7.material.pattern = &map;

	cube.transform = translate(-6, 2, 0) * rotationX(0.7854) * rotationY(0.7854);
	cube1.transform = translate(-2, 2, 0) * rotationX(0.7854) * rotationY(2.3562);
	cube2.transform = translate(2, 2, 0) * rotationX(0.7854) * rotationY(3.927);
	cube3.transform = translate(6, 2, 0) * rotationX(0.7854) * rotationY(5.4978);
	cube4.transform = translate(-6, -2, 0) * rotationX(-0.7854) * rotationY(0.7854);
	cube5.transform = translate(-2, -2, 0) * rotationX(-0.7854) * rotationY(2.3562);
	cube6.transform = translate(2, -2, 0) * rotationX(-0.7854) * rotationY(3.927);
	cube7.transform = translate(6, -2, 0) * rotationX(-0.7854) * rotationY(5.4978);

	world.objects.emplace_back(&cube);
	world.objects.emplace_back(&cube1);
	world.objects.emplace_back(&cube2);
	world.objects.emplace_back(&cube3);
	world.objects.emplace_back(&cube4);
	world.objects.emplace_back(&cube5);
	world.objects.emplace_back(&cube6);
	world.objects.emplace_back(&cube7);

	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	//cam.transform = viewTransformation(Tuple::point(0, 10, -15), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.transform = viewTransformation(Tuple::point(0, 0, -20), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;
	cam.render(world);
}

void earth(int aliasing, int width, int height, int highlights, int edge, double threshold, double focalLenght, double apertureRadius, int apertureSamples) {

	auto world = World();

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-100, 100, -100)));

	auto cube = Cube();

	auto sphere = Sphere();

	auto canvas = canvasFromPPM("assets/farinaWp6.ppm");

	sphere.transform = translate(-2, 1.1, 0) * rotationY(1.9);
	cube.transform = translate(1, 1.1, 0) * rotationY(1.9);

	
	UVImagePattern front = UVImagePattern(&canvas);
	UVImagePattern back = UVImagePattern(&canvas);
	UVImagePattern left = UVImagePattern(&canvas);
	UVImagePattern right = UVImagePattern(&canvas);
	UVImagePattern up = UVImagePattern(&canvas);
	UVImagePattern down = UVImagePattern(&canvas);
	CubeMap map = CubeMap(&front, &back, &left, &right, &up, &down);

	cube.material.pattern = &map;
	
	auto canvasEarth = canvasFromPPM("assets/earthmap1k.ppm");
	sphere.material.pattern = new UVImagePattern(&canvasEarth);

	
	sphere.material.diffuse = 0.9;
	sphere.material.specular = 0.1;
	sphere.material.ambient = 0.1;
	sphere.material.shininess = 10;
	
	world.objects.emplace_back(&sphere);
	world.objects.emplace_back(&cube);
	
	Camera cam(width, height, TEST_PI / 3, focalLenght, apertureRadius, apertureSamples);
	//cam.transform = viewTransformation(Tuple::point(0, 10, -15), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.transform = viewTransformation(Tuple::point(1, 2, -10), Tuple::point(0, 1.1, 0), Tuple::vector(0, 1, 0));
	cam.aliasingSamples = aliasing;
	cam.aliasEdges = edge;
	cam.edgeAliasHighlights = highlights;
	cam.aliasingThreshold = threshold;
	cam.render(world);
}

void loadOBJ(std::string path) {

	OBJParser o(path);

	auto g = o.ObjToGroup();
	g->transform = translate(1, -1, -40) * scale(20, 20, 20) * rotationX(-TEST_PI / 2);
	g->divide();

	auto world = World();
	world.objects.emplace_back(g);

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(10, 15, 20)));

	Camera cam(900, 900, TEST_PI / 3);
	cam.transform = viewTransformation(Tuple::point(0, 20, 50), Tuple::point(0, 10, 0), Tuple::vector(0, 1, 0));

	cam.render(world);
}

void coneTexture() {

	//TODO: double check everything in bounding-boxes it's a bit too slow
	
	auto plane = Plane();
	plane.transform = rotationY(TEST_PI / 4.9f); //* scale(0.4, 0.4, 0.4);
	plane.material.specular = 0.f;
	plane.material.reflective = 0.3f;
	//plane.material.pattern = new StripePattern(new StripePattern(Color(1, 0, 0), Color(1, 1, 1)), new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0)));
	//plane.material.pattern = new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));
	//plane.material.pattern = new RingPattern(new StripePattern(Color(1, 0, 0), Color(0, 0, 1)), new CheckerPattern(Color(1, 1, 1), Color(0, 0, 0)));
	plane.material.pattern = new UVCheckers(2, 2, Color(1, 1, 1), Color(0, 0, 0));
	//plane.material.pattern = new AlignCheck(Color(1, 1, 1), Color(1, 0, 0), Color(1, 1, 0), Color(0, 1, 0), Color(0, 1, 1));

	auto plane1 = Plane();
	plane1.transform = translate(0, 0, 5) * rotationX(TEST_PI / 2);
	plane1.material.color = Color(1.0, 0.9, 0.9);
	plane1.material.specular = 0.f;

	auto sphere = Sphere();
	sphere.transform = translate(-0.5, 1, 0.5);
	
	auto tmp = new UVCheckers(20, 10,  Color(1, 1, 1), Color(0, 0, 0));
	//tmp->transform = scale(0.25, 0.25, 0.25);

	sphere.material.pattern = tmp;

	//sphere.material.color = Color(0.1, 0.4, 0.9);
	//sphere.material.diffuse = 0.7;
	//sphere.material.specular = 0.3;
	//sphere.material.reflective = 0.8;

	auto cilindro = Cylinder();
	cilindro.minimum = 0;
	cilindro.maximum = 1;
	cilindro.closed = 1;
	cilindro.transform = scale(1, 1, 1);
	//cilindro.material.color = Color(1, 0, 0);
	cilindro.material.pattern = new UVCheckers(8, 8, Color(1, 1, 1), Color(0, 0, 0));

	auto world = World();

	//auto spotlight = new SpotLight(Color(1, 1, 1), Tuple::point(0, 10, 0), Tuple::point(0., 0., 0.), TEST_PI / 6);
//	spotlight->fadeIntensity = 1;

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
	//world.lights.emplace_back(new Light(Color(0.4, 0.4, 0.4), Tuple::point(10, 10, -10)));
	//world.lights.emplace_back(spotlight);
	//world.objects.emplace_back(&sphere);
	world.objects.emplace_back(&cilindro);
	world.objects.emplace_back(&plane);
	//world.objects.emplace_back(&plane1);

	//drawAxes(world);

	Camera cam(1280, 720, TEST_PI / 3);
	//cam.transform = viewTransformation(Tuple::point(0, 10, -15), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	/*cam.aliasingSamples = 16;
	cam.aliasEdges = 1;
	cam.edgeAliasHighlights = 1;
	cam.aliasingThreshold = 0.01;
	*/
	//cam.aliasingSamples = 16;
	cam.render(world);
}

void testScene() {

	auto sphere1 = Sphere();

	sphere1.transform = translate(-0.75, 1, 1) * scale(0.25, 0.25, 0.25);

	auto sphere2 = Sphere(); 
	sphere2.transform = translate(0, 1, -2) * scale(0.25, 0.25, 0.25);

	auto sphere3 = Sphere();
	sphere3.transform = translate(0.5, 1, -3) * scale(0.25, 0.25, 0.25);

	auto world = World();

	world.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(-10, 10, -10)));
	world.objects.emplace_back(&sphere1);
	world.objects.emplace_back(&sphere2);
	world.objects.emplace_back(&sphere3);

	Camera cam(1280, 720, TEST_PI / 3, 3, 0.04, 8);
	cam.transform = viewTransformation(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0));
	//cam.aliasingSamples = 8;

	cam.render(world);
}

void drawAxes(World& world) {
	
	auto x = new Cylinder();

	x->minimum = 0;
	x->maximum = 1;
	x->transform = rotationZ(-TEST_PI / 2) * scale(0.05, 2, 0.05);
	x->material.color = Color(1, 0, 0);
	x->closed = true;

	auto y = new Cylinder();

	y->minimum = 0;
	y->maximum = 1;
	y->transform =  scale(0.05, 2, 0.05);
	y->material.color = Color(0, 1, 0);
	y->closed = true;

	auto z = new Cylinder();

	z->minimum = 0;
	z->maximum = 1;
	z->transform = rotationX(-TEST_PI / 2) * scale(0.05, 2, 0.05);
	z->material.color = Color(0, 0, 1);
	z->closed = true;

	world.objects.emplace_back(x);
	world.objects.emplace_back(y);
	world.objects.emplace_back(z);

}