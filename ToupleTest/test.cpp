#include "pch.h"

#define FOR_TEST

#include <limits.h>

#include "../RayTracerChallenge/Tuple.h"
#include "../RayTracerChallenge/Tuple.cpp"

#include "../RayTracerChallenge/Canvas.h"
#include "../RayTracerChallenge/Canvas.cpp"

#include "../RayTracerChallenge/Color.h"
#include "../RayTracerChallenge/Color.cpp"

#include "../RayTracerChallenge/Matrix.h"
#include "../RayTracerChallenge/Matrix.cpp"

#include "../RayTracerChallenge/Transformations.h"
#include "../RayTracerChallenge/Transformations.cpp"

#include "../RayTracerChallenge/Ray.h"
#include "../RayTracerChallenge/Ray.cpp"

#include "../RayTracerChallenge/Sphere.h"
#include "../RayTracerChallenge/Sphere.cpp"

#include "../RayTracerChallenge/Intersection.h"
#include "../RayTracerChallenge/Intersection.cpp"

#include "../RayTracerChallenge/Light.h"
#include "../RayTracerChallenge/Light.cpp"

#include "../RayTracerChallenge/Material.h"
#include "../RayTracerChallenge/Material.cpp"

#include "../RayTracerChallenge/World.h"
#include "../RayTracerChallenge/World.cpp"

#include "../RayTracerChallenge/PreComputations.h"
#include "../RayTracerChallenge/PreComputations.cpp"

#include "../RayTracerChallenge/Camera.h"
#include "../RayTracerChallenge/Camera.cpp"

#include "../RayTracerChallenge/Plane.h"
#include "../RayTracerChallenge/Plane.cpp"

#include "../RayTracerChallenge/Pattern.h"
#include "../RayTracerChallenge/Pattern.cpp"

#include "../RayTracerChallenge/Cube.h"
#include "../RayTracerChallenge/Cube.cpp"

#include "../RayTracerChallenge/Cylinder.h"
#include "../RayTracerChallenge/Cylinder.cpp"

#include "../RayTracerChallenge/Cone.h"
#include "../RayTracerChallenge/Cone.cpp"

#include "../RayTracerChallenge/Groups.h"
#include "../RayTracerChallenge/Groups.cpp"

#include "../RayTracerChallenge/BoundingBox.h"
#include "../RayTracerChallenge/BoundingBox.cpp"

#include "../RayTracerChallenge/Triangle.h"
#include "../RayTracerChallenge/Triangle.cpp"

#include "../RayTracerChallenge/OBJParser.h"
#include "../RayTracerChallenge/OBJParser.cpp"

#include "../RayTracerChallenge/CSGShape.h"
#include "../RayTracerChallenge/CSGShape.cpp"

// TODO: tmp = 1; for shade hit, better way to make it work with defaults

TEST(TupleTest, PointBasic) {
	Tuple tuple = Tuple(4.3, -4.2, 3.1, 1.0);

	EXPECT_FLOAT_EQ(tuple.x, 4.3);
	EXPECT_FLOAT_EQ(tuple.y, -4.2);
	EXPECT_FLOAT_EQ(tuple.z, 3.1);
	EXPECT_FLOAT_EQ(tuple.w, 1.0);

	EXPECT_TRUE(tuple.isPoint());
	EXPECT_FALSE(tuple.isVector());
}

TEST(TupleTest, VectorBasic) {
	Tuple tuple = Tuple(4.3, -4.2, 3.1, 0.0);

	EXPECT_FLOAT_EQ(tuple.x, 4.3);
	EXPECT_FLOAT_EQ(tuple.y, -4.2);
	EXPECT_FLOAT_EQ(tuple.z, 3.1);
	EXPECT_FLOAT_EQ(tuple.w, 0.0);

	EXPECT_TRUE(tuple.isVector());
	EXPECT_FALSE(tuple.isPoint());
}

TEST(TupleTest, CreatePoint) {
	Tuple p = Tuple::point(4, -4, 3);
	Tuple pointTuple = Tuple(4, -4, 3, 1);

	ASSERT_TRUE(p == pointTuple);
}

TEST(TupleTest, CreateVector) {
	Tuple v = Tuple::vector(4, -4, 3);
	Tuple vectorTuple = Tuple(4, -4, 3, 0);

	ASSERT_TRUE(v == vectorTuple);
}

TEST(TupleTest, AddTuple) {
	Tuple t1 = Tuple(3, -2, 5, 1);
	Tuple t2 = Tuple(-2, 3, 1, 0);

	ASSERT_TRUE(t1 + t2 == Tuple(1, 1, 6, 1));
}

TEST(TupleTest, SubtractPoints) {
	Tuple t1 = Tuple::point(3, 2, 1);
	Tuple t2 = Tuple::point(5, 6, 7);

	ASSERT_TRUE(t1 - t2 == Tuple::vector(-2, -4, -6));
}

TEST(TupleTest, SubtractVectors) {
	Tuple t1 = Tuple::vector(3, 2, 1);
	Tuple t2 = Tuple::vector(5, 6, 7);

	ASSERT_TRUE(t1 - t2 == Tuple::vector(-2, -4, -6));
}

TEST(TupleTest, SubtractVectorFromPoint) {
	Tuple t1 = Tuple::point(3, 2, 1);
	Tuple t2 = Tuple::vector(5, 6, 7);

	ASSERT_TRUE(t1 - t2 == Tuple::point(-2, -4, -6));
}

TEST(TupleTest, NegateTuple) {
	ASSERT_TRUE(-Tuple(1, -2, 3, -4) == Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, SubVectorFromZeroVector) {
	Tuple zero = Tuple::vector(0, 0, 0);
	Tuple v = Tuple::vector(1, -2, 3);

	ASSERT_TRUE(zero - v == Tuple::vector(-1, 2, -3));
}

TEST(TupleTest, TupleMultipliedWihtScalar) {
	Tuple t1 = Tuple(1, -2, 3, -4);
	double a = 3.5;

	ASSERT_TRUE(t1 * a == Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, TupleDividedWihtScalar) {
	Tuple t1 = Tuple(1, -2, 3, -4);
	double a = 3.5;

	ASSERT_TRUE(t1 * a == Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, Magnitude) {
	Tuple t1 = Tuple::vector(1, 0, 0);
	Tuple t2 = Tuple::vector(0, 1, 0);
	Tuple t3 = Tuple::vector(0, 0, 1);
	Tuple t4 = Tuple::vector(1, 2, 3);
	Tuple t5 = Tuple::vector(-1, -2, -3);

	ASSERT_FLOAT_EQ(t1.magnitude(), 1.f);
	ASSERT_FLOAT_EQ(t2.magnitude(), 1.f);
	ASSERT_FLOAT_EQ(t3.magnitude(), 1.f);
	ASSERT_FLOAT_EQ(t4.magnitude(), std::sqrt(14.f));
	ASSERT_FLOAT_EQ(t5.magnitude(), std::sqrt(14.f));
}

TEST(TupleTest, Normalize) {
	Tuple t1 = Tuple::vector(4, 0, 0);
	ASSERT_TRUE(t1.normalize() == Tuple::vector(1, 0, 0));

	Tuple t2 = Tuple::vector(1, 2, 3);
	ASSERT_TRUE((t2.normalize()) == Tuple::vector(0.26726, 0.53452, 0.80178));

	ASSERT_FLOAT_EQ(t2.normalize().magnitude(), 1);
}

TEST(TupleTest, DotProduct) {
	Tuple t1 = Tuple::vector(1, 2, 3);
	Tuple t2 = Tuple::vector(2, 3, 4);

	ASSERT_FLOAT_EQ(t1.dotProduct(t2), 20);
}

TEST(TupleTest, CrossProduct) {
	Tuple t1 = Tuple::vector(1, 2, 3);
	Tuple t2 = Tuple::vector(2, 3, 4);

	ASSERT_TRUE(t1.crossProduct(t2) == Tuple::vector(-1, 2, -1));
	ASSERT_TRUE(t2.crossProduct(t1) == Tuple::vector(1, -2, 1));
}


TEST(ColorTest, ColorBasic) {
	Color color = Color(-0.5, 0.4, 1.7);

	EXPECT_FLOAT_EQ(color.r, -0.5);
	EXPECT_FLOAT_EQ(color.g, 0.4);
	EXPECT_FLOAT_EQ(color.b, 1.7);
}

TEST(ColorTest, Addition) {
	Color color = Color(0.9, 0.6, 0.75);
	Color color1 = Color(0.7, 0.1, 0.25);

	ASSERT_EQ(color + color1, Color(1.6, 0.7, 1.0));
}

TEST(ColorTest, Subtraction) {
	Color color = Color(0.9, 0.6, 0.75);
	Color color1 = Color(0.7, 0.1, 0.25);

	ASSERT_EQ(color - color1, Color(0.2, 0.5, 0.5));
}

TEST(ColorTest, ScalarMultiplication) {
	Color color = Color(0.2, 0.3, 0.4);

	ASSERT_EQ(color * 2, Color(0.4, 0.6, 0.8));
}

TEST(ColorTest, ColorMultiplication) {
	Color color = Color(1, 0.2, 0.4);
	Color color1 = Color(0.9, 1.0, 0.1);

	ASSERT_EQ(color * color1, Color(0.9, 0.2, 0.04));
}

TEST(MatrixTest, MatrixConstruction) {
	Matrix m(4, 4);
	m.matrix[0 * m.w + 0] = 1;
	m.matrix[0 * m.w + 1] = 2;
	m.matrix[0 * m.w + 2] = 3;
	m.matrix[0 * m.w + 3] = 4;
	m.matrix[1 * m.w + 0] = 5.5;
	m.matrix[1 * m.w + 1] = 6.5;
	m.matrix[1 * m.w + 2] = 7.5;
	m.matrix[1 * m.w + 3] = 8.5;
	m.matrix[2 * m.w + 0] = 9;
	m.matrix[2 * m.w + 1] = 10;
	m.matrix[2 * m.w + 2] = 11;
	m.matrix[2 * m.w + 3] = 12;
	m.matrix[3 * m.w + 0] = 13.5;
	m.matrix[3 * m.w + 1] = 14.5;
	m.matrix[3 * m.w + 2] = 15.5;
	m.matrix[3 * m.w + 3] = 16.5;

	ASSERT_FLOAT_EQ(m.matrix[0], 1);
	ASSERT_FLOAT_EQ(m.matrix[1], 2);
	ASSERT_FLOAT_EQ(m.matrix[2], 3);
	ASSERT_FLOAT_EQ(m.matrix[3], 4);
	ASSERT_FLOAT_EQ(m.matrix[4], 5.5);
	ASSERT_FLOAT_EQ(m.matrix[5], 6.5);
	ASSERT_FLOAT_EQ(m.matrix[6], 7.5);
	ASSERT_FLOAT_EQ(m.matrix[7], 8.5);
	ASSERT_FLOAT_EQ(m.matrix[8], 9);
	ASSERT_FLOAT_EQ(m.matrix[9], 10);
	ASSERT_FLOAT_EQ(m.matrix[10], 11);
	ASSERT_FLOAT_EQ(m.matrix[11], 12);
	ASSERT_FLOAT_EQ(m.matrix[12], 13.5);
	ASSERT_FLOAT_EQ(m.matrix[13], 14.5);
	ASSERT_FLOAT_EQ(m.matrix[14], 15.5);
	ASSERT_FLOAT_EQ(m.matrix[15], 16.5);

	Matrix m1(2, 2);
	m1.matrix[0 * m1.w + 0] = -3;
	m1.matrix[0 * m1.w + 1] = 5;
	m1.matrix[1 * m1.w + 0] = 1;
	m1.matrix[1 * m1.w + 1] = -2;

	ASSERT_FLOAT_EQ(m1.matrix[0], -3);
	ASSERT_FLOAT_EQ(m1.matrix[1], 5);
	ASSERT_FLOAT_EQ(m1.matrix[2], 1);
	ASSERT_FLOAT_EQ(m1.matrix[3], -2);

	Matrix m2(3, 3);
	m2.matrix[0 * m2.w + 0] = -3;
	m2.matrix[0 * m2.w + 1] = 5;
	m2.matrix[0 * m2.w + 2] = 0;
	m2.matrix[1 * m2.w + 0] = 1;
	m2.matrix[1 * m2.w + 1] = -2;
	m2.matrix[1 * m2.w + 2] = -7;
	m2.matrix[2 * m2.w + 0] = 0;
	m2.matrix[2 * m2.w + 1] = 1;
	m2.matrix[2 * m2.w + 2] = 1;

	ASSERT_FLOAT_EQ(m2.matrix[0], -3);
	ASSERT_FLOAT_EQ(m2.matrix[1], 5);
	ASSERT_FLOAT_EQ(m2.matrix[2], 0);
	ASSERT_FLOAT_EQ(m2.matrix[3], 1);
	ASSERT_FLOAT_EQ(m2.matrix[4], -2);
	ASSERT_FLOAT_EQ(m2.matrix[5], -7);
	ASSERT_FLOAT_EQ(m2.matrix[6], 0);
	ASSERT_FLOAT_EQ(m2.matrix[7], 1);
	ASSERT_FLOAT_EQ(m2.matrix[8], 1);

}

TEST(MatrixTest, MatrixEquality) {
	Matrix m(4, 4);
	m.matrix[0 * m.w + 0] = 1;
	m.matrix[0 * m.w + 1] = 2;
	m.matrix[0 * m.w + 2] = 3;
	m.matrix[0 * m.w + 3] = 4;
	m.matrix[1 * m.w + 0] = 5;
	m.matrix[1 * m.w + 1] = 6;
	m.matrix[1 * m.w + 2] = 7;
	m.matrix[1 * m.w + 3] = 8;
	m.matrix[2 * m.w + 0] = 9;
	m.matrix[2 * m.w + 1] = 8;
	m.matrix[2 * m.w + 2] = 7;
	m.matrix[2 * m.w + 3] = 6;
	m.matrix[3 * m.w + 0] = 5;
	m.matrix[3 * m.w + 1] = 4;
	m.matrix[3 * m.w + 2] = 3;
	m.matrix[3 * m.w + 3] = 2;

	Matrix m1(4, 4);
	m1.matrix[0 * m1.w + 0] = 1;
	m1.matrix[0 * m1.w + 1] = 2;
	m1.matrix[0 * m1.w + 2] = 3;
	m1.matrix[0 * m1.w + 3] = 4;
	m1.matrix[1 * m1.w + 0] = 5;
	m1.matrix[1 * m1.w + 1] = 6;
	m1.matrix[1 * m1.w + 2] = 7;
	m1.matrix[1 * m1.w + 3] = 8;
	m1.matrix[2 * m1.w + 0] = 9;
	m1.matrix[2 * m1.w + 1] = 8;
	m1.matrix[2 * m1.w + 2] = 7;
	m1.matrix[2 * m1.w + 3] = 6;
	m1.matrix[3 * m1.w + 0] = 5;
	m1.matrix[3 * m1.w + 1] = 4;
	m1.matrix[3 * m1.w + 2] = 3;
	m1.matrix[3 * m1.w + 3] = 2;

	Matrix m2(4, 4);
	m2.matrix[0 * m2.w + 0] = 2;
	m2.matrix[0 * m2.w + 1] = 3;
	m2.matrix[0 * m2.w + 2] = 4;
	m2.matrix[0 * m2.w + 3] = 5;
	m2.matrix[1 * m2.w + 0] = 6;
	m2.matrix[1 * m2.w + 1] = 7;
	m2.matrix[1 * m2.w + 2] = 8;
	m2.matrix[1 * m2.w + 3] = 9;
	m2.matrix[2 * m2.w + 0] = 8;
	m2.matrix[2 * m2.w + 1] = 7;
	m2.matrix[2 * m2.w + 2] = 6;
	m2.matrix[2 * m2.w + 3] = 5;
	m2.matrix[3 * m2.w + 0] = 4;
	m2.matrix[3 * m2.w + 1] = 3;
	m2.matrix[3 * m2.w + 2] = 2;
	m2.matrix[3 * m2.w + 3] = 1;

	EXPECT_TRUE(m == m1);
	EXPECT_FALSE(m == m2);
}

TEST(MatrixTest, MatrixMultiplication) {

	Matrix m1(4, 4);
	m1.matrix[0 * m1.w + 0] = 1;
	m1.matrix[0 * m1.w + 1] = 2;
	m1.matrix[0 * m1.w + 2] = 3;
	m1.matrix[0 * m1.w + 3] = 4;
	m1.matrix[1 * m1.w + 0] = 5;
	m1.matrix[1 * m1.w + 1] = 6;
	m1.matrix[1 * m1.w + 2] = 7;
	m1.matrix[1 * m1.w + 3] = 8;
	m1.matrix[2 * m1.w + 0] = 9;
	m1.matrix[2 * m1.w + 1] = 8;
	m1.matrix[2 * m1.w + 2] = 7;
	m1.matrix[2 * m1.w + 3] = 6;
	m1.matrix[3 * m1.w + 0] = 5;
	m1.matrix[3 * m1.w + 1] = 4;
	m1.matrix[3 * m1.w + 2] = 3;
	m1.matrix[3 * m1.w + 3] = 2;

	Matrix m2(4, 4);
	m2.matrix[0 * m1.w + 0] = -2;
	m2.matrix[0 * m1.w + 1] = 1;
	m2.matrix[0 * m1.w + 2] = 2;
	m2.matrix[0 * m1.w + 3] = 3;
	m2.matrix[1 * m1.w + 0] = 3;
	m2.matrix[1 * m1.w + 1] = 2;
	m2.matrix[1 * m1.w + 2] = 1;
	m2.matrix[1 * m1.w + 3] = -1;
	m2.matrix[2 * m1.w + 0] = 4;
	m2.matrix[2 * m1.w + 1] = 3;
	m2.matrix[2 * m1.w + 2] = 6;
	m2.matrix[2 * m1.w + 3] = 5;
	m2.matrix[3 * m1.w + 0] = 1;
	m2.matrix[3 * m1.w + 1] = 2;
	m2.matrix[3 * m1.w + 2] = 7;
	m2.matrix[3 * m1.w + 3] = 8;

	Matrix m3(4, 4);
	m3.matrix[0 * m3.w + 0] = 20;
	m3.matrix[0 * m3.w + 1] = 22;
	m3.matrix[0 * m3.w + 2] = 50;
	m3.matrix[0 * m3.w + 3] = 48;
	m3.matrix[1 * m3.w + 0] = 44;
	m3.matrix[1 * m3.w + 1] = 54;
	m3.matrix[1 * m3.w + 2] = 114;
	m3.matrix[1 * m3.w + 3] = 108;
	m3.matrix[2 * m3.w + 0] = 40;
	m3.matrix[2 * m3.w + 1] = 58;
	m3.matrix[2 * m3.w + 2] = 110;
	m3.matrix[2 * m3.w + 3] = 102;
	m3.matrix[3 * m3.w + 0] = 16;
	m3.matrix[3 * m3.w + 1] = 26;
	m3.matrix[3 * m3.w + 2] = 46;
	m3.matrix[3 * m3.w + 3] = 42;

	EXPECT_EQ(m1 * m2, m3);
}

TEST(MatrixTest, MatrixTupleMultiplication) {
	Matrix m(4, 4);

	m.matrix[0 * m.w + 0] = 1;
	m.matrix[0 * m.w + 1] = 2;
	m.matrix[0 * m.w + 2] = 3;
	m.matrix[0 * m.w + 3] = 4;
	m.matrix[1 * m.w + 0] = 2;
	m.matrix[1 * m.w + 1] = 4;
	m.matrix[1 * m.w + 2] = 4;
	m.matrix[1 * m.w + 3] = 2;
	m.matrix[2 * m.w + 0] = 8;
	m.matrix[2 * m.w + 1] = 6;
	m.matrix[2 * m.w + 2] = 4;
	m.matrix[2 * m.w + 3] = 1;
	m.matrix[3 * m.w + 0] = 0;
	m.matrix[3 * m.w + 1] = 0;
	m.matrix[3 * m.w + 2] = 0;
	m.matrix[3 * m.w + 3] = 1;

	Tuple tp(1, 2, 3, 1);

	EXPECT_EQ(m * tp, Tuple(18, 24, 33, 1));
}

TEST(MatrixTest, MatrixTranspose) {
	Matrix mt(4, 4);
	mt.matrix[0 * mt.w + 0] = 0;
	mt.matrix[0 * mt.w + 1] = 9;
	mt.matrix[0 * mt.w + 2] = 3;
	mt.matrix[0 * mt.w + 3] = 0;
	mt.matrix[1 * mt.w + 0] = 9;
	mt.matrix[1 * mt.w + 1] = 8;
	mt.matrix[1 * mt.w + 2] = 0;
	mt.matrix[1 * mt.w + 3] = 8;
	mt.matrix[2 * mt.w + 0] = 1;
	mt.matrix[2 * mt.w + 1] = 8;
	mt.matrix[2 * mt.w + 2] = 5;
	mt.matrix[2 * mt.w + 3] = 3;
	mt.matrix[3 * mt.w + 0] = 0;
	mt.matrix[3 * mt.w + 1] = 0;
	mt.matrix[3 * mt.w + 2] = 5;
	mt.matrix[3 * mt.w + 3] = 8;

	Matrix cmp(4, 4);
	cmp.matrix[0 * mt.w + 0] = 0;
	cmp.matrix[0 * mt.w + 1] = 9;
	cmp.matrix[0 * mt.w + 2] = 1;
	cmp.matrix[0 * mt.w + 3] = 0;
	cmp.matrix[1 * mt.w + 0] = 9;
	cmp.matrix[1 * mt.w + 1] = 8;
	cmp.matrix[1 * mt.w + 2] = 8;
	cmp.matrix[1 * mt.w + 3] = 0;
	cmp.matrix[2 * mt.w + 0] = 3;
	cmp.matrix[2 * mt.w + 1] = 0;
	cmp.matrix[2 * mt.w + 2] = 5;
	cmp.matrix[2 * mt.w + 3] = 5;
	cmp.matrix[3 * mt.w + 0] = 0;
	cmp.matrix[3 * mt.w + 1] = 8;
	cmp.matrix[3 * mt.w + 2] = 3;
	cmp.matrix[3 * mt.w + 3] = 8;

	ASSERT_EQ(mt.transpose(), cmp);
}

TEST(MatrixTest, MatrixDeterminant2x2) {

	Matrix d(2, 2);
	d.matrix[0 * d.w + 0] = 1;
	d.matrix[0 * d.w + 1] = 5;

	d.matrix[1 * d.w + 0] = -3;
	d.matrix[1 * d.w + 1] = 2;

	ASSERT_FLOAT_EQ(d.determinant(), 17);
}

TEST(MatrixTest, MatrixSubmatrix) {

	Matrix sub3(3, 3);
	sub3.matrix[0 * sub3.w + 0] = 1;
	sub3.matrix[0 * sub3.w + 1] = 5;
	sub3.matrix[0 * sub3.w + 2] = 0;
	sub3.matrix[1 * sub3.w + 0] = -3;
	sub3.matrix[1 * sub3.w + 1] = 2;
	sub3.matrix[1 * sub3.w + 2] = 7;
	sub3.matrix[2 * sub3.w + 0] = 0;
	sub3.matrix[2 * sub3.w + 1] = 6;
	sub3.matrix[2 * sub3.w + 2] = -3;

	Matrix cmp(2, 2);
	cmp.matrix[0 * cmp.w + 0] = -3;
	cmp.matrix[0 * cmp.w + 1] = 2;
	cmp.matrix[1 * cmp.w + 0] = 0;
	cmp.matrix[1 * cmp.w + 1] = 6;

	ASSERT_EQ(sub3.submatrix(0, 2), cmp);

	Matrix sub4(4, 4);
	sub4.matrix[0 * sub4.w + 0] = -6;
	sub4.matrix[0 * sub4.w + 1] = 1;
	sub4.matrix[0 * sub4.w + 2] = 1;
	sub4.matrix[0 * sub4.w + 3] = 6;
	sub4.matrix[1 * sub4.w + 0] = -8;
	sub4.matrix[1 * sub4.w + 1] = 5;
	sub4.matrix[1 * sub4.w + 2] = 8;
	sub4.matrix[1 * sub4.w + 3] = 6;
	sub4.matrix[2 * sub4.w + 0] = -1;
	sub4.matrix[2 * sub4.w + 1] = 0;
	sub4.matrix[2 * sub4.w + 2] = 8;
	sub4.matrix[2 * sub4.w + 3] = 2;
	sub4.matrix[3 * sub4.w + 0] = -7;
	sub4.matrix[3 * sub4.w + 1] = 1;
	sub4.matrix[3 * sub4.w + 2] = -1;
	sub4.matrix[3 * sub4.w + 3] = 1;

	Matrix cmp1(3, 3);
	cmp1.matrix[0 * cmp1.w + 0] = -6;
	cmp1.matrix[0 * cmp1.w + 1] = 1;
	cmp1.matrix[0 * cmp1.w + 2] = 6;
	cmp1.matrix[1 * cmp1.w + 0] = -8;
	cmp1.matrix[1 * cmp1.w + 1] = 8;
	cmp1.matrix[1 * cmp1.w + 2] = 6;
	cmp1.matrix[2 * cmp1.w + 0] = -7;
	cmp1.matrix[2 * cmp1.w + 1] = -1;
	cmp1.matrix[2 * cmp1.w + 2] = 1;

	ASSERT_EQ(sub4.submatrix(2, 1), cmp1);
}

TEST(MatrixTest, MatrixMinor) {

	Matrix mino(3, 3);
	mino.matrix[0 * mino.w + 0] = 3;
	mino.matrix[0 * mino.w + 1] = 5;
	mino.matrix[0 * mino.w + 2] = 0;
	mino.matrix[1 * mino.w + 0] = 2;
	mino.matrix[1 * mino.w + 1] = -1;
	mino.matrix[1 * mino.w + 2] = -7;
	mino.matrix[2 * mino.w + 0] = 6;
	mino.matrix[2 * mino.w + 1] = -1;
	mino.matrix[2 * mino.w + 2] = 5;

	ASSERT_FLOAT_EQ(mino.minor(1, 0), 25);
	ASSERT_FLOAT_EQ(mino.submatrix(1, 0).determinant(), 25);
}

TEST(MatrixTest, MatrixCofactor) {
	Matrix detmino1(3, 3);
	detmino1.matrix[0 * detmino1.w + 0] = 3;
	detmino1.matrix[0 * detmino1.w + 1] = 5;
	detmino1.matrix[0 * detmino1.w + 2] = 0;
	detmino1.matrix[1 * detmino1.w + 0] = 2;
	detmino1.matrix[1 * detmino1.w + 1] = -1;
	detmino1.matrix[1 * detmino1.w + 2] = -7;
	detmino1.matrix[2 * detmino1.w + 0] = 6;
	detmino1.matrix[2 * detmino1.w + 1] = -1;
	detmino1.matrix[2 * detmino1.w + 2] = 5;

	ASSERT_FLOAT_EQ(detmino1.minor(0, 0), -12);
	ASSERT_FLOAT_EQ(detmino1.cofactor(0, 0), -12);
	ASSERT_FLOAT_EQ(detmino1.minor(1, 0), 25);
	ASSERT_FLOAT_EQ(detmino1.cofactor(1, 0), -25);
}

TEST(MatrixTest, MatrixDeterminantLarge) {

	Matrix detmino1(3, 3);
	detmino1.matrix[0 * detmino1.w + 0] = 1;
	detmino1.matrix[0 * detmino1.w + 1] = 2;
	detmino1.matrix[0 * detmino1.w + 2] = 6;
	detmino1.matrix[1 * detmino1.w + 0] = -5;
	detmino1.matrix[1 * detmino1.w + 1] = 8;
	detmino1.matrix[1 * detmino1.w + 2] = -4;
	detmino1.matrix[2 * detmino1.w + 0] = 2;
	detmino1.matrix[2 * detmino1.w + 1] = 6;
	detmino1.matrix[2 * detmino1.w + 2] = 4;

	ASSERT_FLOAT_EQ(detmino1.cofactor(0, 0), 56);
	ASSERT_FLOAT_EQ(detmino1.cofactor(0, 1), 12);
	ASSERT_FLOAT_EQ(detmino1.cofactor(0, 2), -46);
	ASSERT_FLOAT_EQ(detmino1.determinant(), -196);

	Matrix detmino2(4, 4);
	detmino2.matrix[0 * detmino2.w + 0] = -2;
	detmino2.matrix[0 * detmino2.w + 1] = -8;
	detmino2.matrix[0 * detmino2.w + 2] = 3;
	detmino2.matrix[0 * detmino2.w + 3] = 5;
	detmino2.matrix[1 * detmino2.w + 0] = -3;
	detmino2.matrix[1 * detmino2.w + 1] = 1;
	detmino2.matrix[1 * detmino2.w + 2] = 7;
	detmino2.matrix[1 * detmino2.w + 3] = 3;
	detmino2.matrix[2 * detmino2.w + 0] = 1;
	detmino2.matrix[2 * detmino2.w + 1] = 2;
	detmino2.matrix[2 * detmino2.w + 2] = -9;
	detmino2.matrix[2 * detmino2.w + 3] = 6;
	detmino2.matrix[3 * detmino2.w + 0] = -6;
	detmino2.matrix[3 * detmino2.w + 1] = 7;
	detmino2.matrix[3 * detmino2.w + 2] = 7;
	detmino2.matrix[3 * detmino2.w + 3] = -9;


	ASSERT_FLOAT_EQ(detmino2.cofactor(0, 0), 690);
	ASSERT_FLOAT_EQ(detmino2.cofactor(0, 1), 447);
	ASSERT_FLOAT_EQ(detmino2.cofactor(0, 2), 210);
	ASSERT_FLOAT_EQ(detmino2.cofactor(0, 3), 51);
	ASSERT_FLOAT_EQ(detmino2.determinant(), -4071);
}

TEST(MatrixTest, MatrixInvertibility) {
	Matrix invertible1(4, 4);
	invertible1.matrix[0 * invertible1.w + 0] = 6;
	invertible1.matrix[0 * invertible1.w + 1] = 4;
	invertible1.matrix[0 * invertible1.w + 2] = 4;
	invertible1.matrix[0 * invertible1.w + 3] = 4;
	invertible1.matrix[1 * invertible1.w + 0] = 5;
	invertible1.matrix[1 * invertible1.w + 1] = 5;
	invertible1.matrix[1 * invertible1.w + 2] = 7;
	invertible1.matrix[1 * invertible1.w + 3] = 6;
	invertible1.matrix[2 * invertible1.w + 0] = 4;
	invertible1.matrix[2 * invertible1.w + 1] = -9;
	invertible1.matrix[2 * invertible1.w + 2] = 3;
	invertible1.matrix[2 * invertible1.w + 3] = -7;
	invertible1.matrix[3 * invertible1.w + 0] = 9;
	invertible1.matrix[3 * invertible1.w + 1] = 1;
	invertible1.matrix[3 * invertible1.w + 2] = 7;
	invertible1.matrix[3 * invertible1.w + 3] = -6;

	ASSERT_FLOAT_EQ(invertible1.determinant(), -2120);
	ASSERT_TRUE(invertible1.invertible() == 1);


	Matrix invertible2(4, 4);
	invertible2.matrix[0 * invertible2.w + 0] = -4;
	invertible2.matrix[0 * invertible2.w + 1] = 2;
	invertible2.matrix[0 * invertible2.w + 2] = -2;
	invertible2.matrix[0 * invertible2.w + 3] = -3;
	invertible2.matrix[1 * invertible2.w + 0] = 9;
	invertible2.matrix[1 * invertible2.w + 1] = 6;
	invertible2.matrix[1 * invertible2.w + 2] = 2;
	invertible2.matrix[1 * invertible2.w + 3] = 6;
	invertible2.matrix[2 * invertible2.w + 0] = 0;
	invertible2.matrix[2 * invertible2.w + 1] = -5;
	invertible2.matrix[2 * invertible2.w + 2] = 1;
	invertible2.matrix[2 * invertible2.w + 3] = -5;
	invertible2.matrix[3 * invertible2.w + 0] = 0;
	invertible2.matrix[3 * invertible2.w + 1] = 0;
	invertible2.matrix[3 * invertible2.w + 2] = 0;
	invertible2.matrix[3 * invertible2.w + 3] = 0;

	ASSERT_TRUE(invertible2.invertible() == 0);
}


TEST(MatrixTest, MatrixInverse) {

	Matrix inverse1(4, 4);
	inverse1.matrix[0 * inverse1.w + 0] = -5;
	inverse1.matrix[0 * inverse1.w + 1] = 2;
	inverse1.matrix[0 * inverse1.w + 2] = 6;
	inverse1.matrix[0 * inverse1.w + 3] = -8;
	inverse1.matrix[1 * inverse1.w + 0] = 1;
	inverse1.matrix[1 * inverse1.w + 1] = -5;
	inverse1.matrix[1 * inverse1.w + 2] = 1;
	inverse1.matrix[1 * inverse1.w + 3] = 8;
	inverse1.matrix[2 * inverse1.w + 0] = 7;
	inverse1.matrix[2 * inverse1.w + 1] = 7;
	inverse1.matrix[2 * inverse1.w + 2] = -6;
	inverse1.matrix[2 * inverse1.w + 3] = -7;
	inverse1.matrix[3 * inverse1.w + 0] = 1;
	inverse1.matrix[3 * inverse1.w + 1] = -3;
	inverse1.matrix[3 * inverse1.w + 2] = 7;
	inverse1.matrix[3 * inverse1.w + 3] = 4;

	Matrix cmp1(4, 4);
	cmp1.matrix[0 * cmp1.w + 0] = 0.21805;
	cmp1.matrix[0 * cmp1.w + 1] = 0.45113;
	cmp1.matrix[0 * cmp1.w + 2] = 0.24060;
	cmp1.matrix[0 * cmp1.w + 3] = -0.04511;
	cmp1.matrix[1 * cmp1.w + 0] = -0.80827;
	cmp1.matrix[1 * cmp1.w + 1] = -1.45677;
	cmp1.matrix[1 * cmp1.w + 2] = -0.44361;
	cmp1.matrix[1 * cmp1.w + 3] = 0.52068;
	cmp1.matrix[2 * cmp1.w + 0] = -0.07895;
	cmp1.matrix[2 * cmp1.w + 1] = -0.22368;
	cmp1.matrix[2 * cmp1.w + 2] = -0.05263;
	cmp1.matrix[2 * cmp1.w + 3] = 0.19737;
	cmp1.matrix[3 * cmp1.w + 0] = -0.522561;
	cmp1.matrix[3 * cmp1.w + 1] = -0.81391;
	cmp1.matrix[3 * cmp1.w + 2] = -0.30075;
	cmp1.matrix[3 * cmp1.w + 3] = 0.30639;

	ASSERT_EQ((*inverse1.inverse()), cmp1);


	Matrix inverse2(4, 4);
	inverse2.matrix[0 * inverse2.w + 0] = 8;
	inverse2.matrix[0 * inverse2.w + 1] = -5;
	inverse2.matrix[0 * inverse2.w + 2] = 9;
	inverse2.matrix[0 * inverse2.w + 3] = 2;
	inverse2.matrix[1 * inverse2.w + 0] = 7;
	inverse2.matrix[1 * inverse2.w + 1] = 5;
	inverse2.matrix[1 * inverse2.w + 2] = 6;
	inverse2.matrix[1 * inverse2.w + 3] = 1;
	inverse2.matrix[2 * inverse2.w + 0] = -6;
	inverse2.matrix[2 * inverse2.w + 1] = 0;
	inverse2.matrix[2 * inverse2.w + 2] = 9;
	inverse2.matrix[2 * inverse2.w + 3] = 6;
	inverse2.matrix[3 * inverse2.w + 0] = -3;
	inverse2.matrix[3 * inverse2.w + 1] = 0;
	inverse2.matrix[3 * inverse2.w + 2] = -9;
	inverse2.matrix[3 * inverse2.w + 3] = -4;

	Matrix cmp2(4, 4);
	cmp2.matrix[0 * cmp2.w + 0] = -0.15385;
	cmp2.matrix[0 * cmp2.w + 1] = -0.15385;
	cmp2.matrix[0 * cmp2.w + 2] = -0.28205;
	cmp2.matrix[0 * cmp2.w + 3] = -0.53846;
	cmp2.matrix[1 * cmp2.w + 0] = -0.07692;
	cmp2.matrix[1 * cmp2.w + 1] = 0.12308;
	cmp2.matrix[1 * cmp2.w + 2] = 0.02564;
	cmp2.matrix[1 * cmp2.w + 3] = 0.03077;
	cmp2.matrix[2 * cmp2.w + 0] = 0.35897;
	cmp2.matrix[2 * cmp2.w + 1] = 0.35897;
	cmp2.matrix[2 * cmp2.w + 2] = 0.43590;
	cmp2.matrix[2 * cmp2.w + 3] = 0.92308;
	cmp2.matrix[3 * cmp2.w + 0] = -0.69231;
	cmp2.matrix[3 * cmp2.w + 1] = -0.69231;
	cmp2.matrix[3 * cmp2.w + 2] = -0.76923;
	cmp2.matrix[3 * cmp2.w + 3] = -1.92308;

	ASSERT_EQ(*inverse2.inverse(), cmp2);


	Matrix inverse3(4, 4);
	inverse3.matrix[0 * inverse3.w + 0] = 9;
	inverse3.matrix[0 * inverse3.w + 1] = 3;
	inverse3.matrix[0 * inverse3.w + 2] = 0;
	inverse3.matrix[0 * inverse3.w + 3] = 9;
	inverse3.matrix[1 * inverse3.w + 0] = -5;
	inverse3.matrix[1 * inverse3.w + 1] = -2;
	inverse3.matrix[1 * inverse3.w + 2] = -6;
	inverse3.matrix[1 * inverse3.w + 3] = -3;
	inverse3.matrix[2 * inverse3.w + 0] = -4;
	inverse3.matrix[2 * inverse3.w + 1] = 9;
	inverse3.matrix[2 * inverse3.w + 2] = 6;
	inverse3.matrix[2 * inverse3.w + 3] = 4;
	inverse3.matrix[3 * inverse3.w + 0] = -7;
	inverse3.matrix[3 * inverse3.w + 1] = 6;
	inverse3.matrix[3 * inverse3.w + 2] = 6;
	inverse3.matrix[3 * inverse3.w + 3] = 2;

	Matrix cmp3(4, 4);
	cmp3.matrix[0 * cmp3.w + 0] = -0.04074;
	cmp3.matrix[0 * cmp3.w + 1] = -0.07778;
	cmp3.matrix[0 * cmp3.w + 2] = 0.14444;
	cmp3.matrix[0 * cmp3.w + 3] = -0.22222;
	cmp3.matrix[1 * cmp3.w + 0] = -0.07778;
	cmp3.matrix[1 * cmp3.w + 1] = 0.03333;
	cmp3.matrix[1 * cmp3.w + 2] = 0.36667;
	cmp3.matrix[1 * cmp3.w + 3] = -0.33333;
	cmp3.matrix[2 * cmp3.w + 0] = -0.02901;
	cmp3.matrix[2 * cmp3.w + 1] = -0.14630;
	cmp3.matrix[2 * cmp3.w + 2] = -0.10926;
	cmp3.matrix[2 * cmp3.w + 3] = 0.12963;
	cmp3.matrix[3 * cmp3.w + 0] = 0.17778;
	cmp3.matrix[3 * cmp3.w + 1] = 0.06667;
	cmp3.matrix[3 * cmp3.w + 2] = -0.26667;
	cmp3.matrix[3 * cmp3.w + 3] = 0.33333;

	ASSERT_EQ(*inverse3.inverse(), cmp3);

}

TEST(MatrixTest, MatrixMultiplicationByInverse) {
	Matrix mat1(4, 4);
	mat1.matrix[0 * mat1.w + 0] = 3;
	mat1.matrix[0 * mat1.w + 1] = -9;
	mat1.matrix[0 * mat1.w + 2] = 7;
	mat1.matrix[0 * mat1.w + 3] = 3;
	mat1.matrix[1 * mat1.w + 0] = 3;
	mat1.matrix[1 * mat1.w + 1] = -8;
	mat1.matrix[1 * mat1.w + 2] = 2;
	mat1.matrix[1 * mat1.w + 3] = -9;
	mat1.matrix[2 * mat1.w + 0] = -4;
	mat1.matrix[2 * mat1.w + 1] = 4;
	mat1.matrix[2 * mat1.w + 2] = 4;
	mat1.matrix[2 * mat1.w + 3] = 1;
	mat1.matrix[3 * mat1.w + 0] = -6;
	mat1.matrix[3 * mat1.w + 1] = 5;
	mat1.matrix[3 * mat1.w + 2] = -1;
	mat1.matrix[3 * mat1.w + 3] = 1;

	Matrix mat2(4, 4);
	mat2.matrix[0 * mat2.w + 0] = 8;
	mat2.matrix[0 * mat2.w + 1] = 2;
	mat2.matrix[0 * mat2.w + 2] = 2;
	mat2.matrix[0 * mat2.w + 3] = 2;
	mat2.matrix[1 * mat2.w + 0] = 3;
	mat2.matrix[1 * mat2.w + 1] = -1;
	mat2.matrix[1 * mat2.w + 2] = 7;
	mat2.matrix[1 * mat2.w + 3] = 0;
	mat2.matrix[2 * mat2.w + 0] = 7;
	mat2.matrix[2 * mat2.w + 1] = 0;
	mat2.matrix[2 * mat2.w + 2] = 5;
	mat2.matrix[2 * mat2.w + 3] = 4;
	mat2.matrix[3 * mat2.w + 0] = 6;
	mat2.matrix[3 * mat2.w + 1] = -2;
	mat2.matrix[3 * mat2.w + 2] = 0;
	mat2.matrix[3 * mat2.w + 3] = 5;

	Matrix mat3 = mat1 * mat2;
	mat3 = mat3 * (*mat2.inverse());

	ASSERT_EQ(mat3, mat1);
}


TEST(TransformationTest, Translation) {
	Tuple p = Tuple::point(-3, 4, 5);
	Matrix t = translate(5, -3, 2);

	ASSERT_EQ(t * p, Tuple::point(2, 1, 7));
}

TEST(TransformationTest, MulInverseOfTranslation) {

	Matrix t = translate(5, -3, 2);
	Matrix inv = *t.inverse();
	Tuple p = Tuple::point(-3, 4, 5);

	ASSERT_EQ(inv * p, Tuple::point(-8, 7, 3));
}

TEST(TransformationTest, VectorTranslation) {

	Matrix t = translate(5, -3, 2);
	Tuple v = Tuple::vector(-3, 4, 5);

	ASSERT_EQ(t * v, v);
}

TEST(TransformationTest, PointScale) {

	Tuple p = Tuple::point(-4, 6, 8);
	Matrix t = scale(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(-8, 18, 32));
}

TEST(TransformationTest, VectorScale) {

	Tuple v = Tuple::vector(-4, 6, 8);
	Matrix t = scale(2, 3, 4);

	ASSERT_EQ(t * v, Tuple::vector(-8, 18, 32));
}

TEST(TransformationTest, MulInverseOfScale) {

	Tuple v = Tuple::vector(-4, 6, 8);
	Matrix t = scale(2, 3, 4);
	Matrix inv = *t.inverse();

	ASSERT_EQ(inv * v, Tuple::vector(-2, 2, 2));
}

TEST(TransformationTest, Reflection) {

	Matrix t = scale(-1, 1, 1);
	Tuple p = Tuple::point(2, 3, 4);
	ASSERT_EQ(t * p, Tuple::point(-2, 3, 4));
}

TEST(TransformationTest, RotatonX) {

	Tuple p = Tuple::point(0, 1, 0);
	Matrix halfQuarter = rotationX(M_PI / 4);
	Matrix fullQuarter = rotationX(M_PI / 2);

	ASSERT_EQ(halfQuarter * p, Tuple::point(0, sqrt(2) / 2, sqrt(2) / 2));
	ASSERT_EQ(fullQuarter * p, Tuple::point(0, 0, 1));
}

TEST(TransformationTest, RotatonY) {

	Tuple p = Tuple::point(0, 0, 1);
	Matrix halfQuarter = rotationY(M_PI / 4);
	Matrix fullQuarter = rotationY(M_PI / 2);

	ASSERT_EQ(halfQuarter * p, Tuple::point(sqrt(2) / 2, 0, sqrt(2) / 2));
	ASSERT_EQ(fullQuarter * p, Tuple::point(1, 0, 0));
}

TEST(TransformationTest, RotatonZ) {

	Tuple p = Tuple::point(0, 1, 0);
	Matrix halfQuarter = rotationZ(M_PI / 4);
	Matrix fullQuarter = rotationZ(M_PI / 2);

	ASSERT_EQ(halfQuarter * p, Tuple::point(-sqrt(2) / 2, sqrt(2) / 2, 0));
	ASSERT_EQ(fullQuarter * p, Tuple::point(-1, 0, 0));
}


TEST(TransformationTest, ShearingXY) {

	Matrix t = shearing(1, 0, 0, 0, 0, 0);
	Tuple p = Tuple::point(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(5, 3, 4));
}

TEST(TransformationTest, ShearingXZ) {

	Matrix t = shearing(0, 1, 0, 0, 0, 0);
	Tuple p = Tuple::point(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(6, 3, 4));
}

TEST(TransformationTest, ShearingYX) {

	Matrix t = shearing(0, 0, 1, 0, 0, 0);
	Tuple p = Tuple::point(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(2, 5, 4));
}

TEST(TransformationTest, ShearingYZ) {

	Matrix t = shearing(0, 0, 0, 1, 0, 0);
	Tuple p = Tuple::point(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(2, 7, 4));
}

TEST(TransformationTest, ShearingZX) {

	Matrix t = shearing(0, 0, 0, 0, 1, 0);
	Tuple p = Tuple::point(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(2, 3, 6));
}

TEST(TransformationTest, ShearingZY) {

	Matrix t = shearing(0, 0, 0, 0, 0, 1);
	Tuple p = Tuple::point(2, 3, 4);

	ASSERT_EQ(t * p, Tuple::point(2, 3, 7));
}

TEST(TransformationTest, TransformationSeq) {

	Tuple p = Tuple::point(1, 0, 1);
	Matrix A = rotationX(M_PI / 2);
	Matrix B = scale(5, 5, 5);
	Matrix C = translate(10, 5, 7);

	Tuple p2 = A * p;

	ASSERT_EQ(p2, Tuple::point(1, -1, 0));

	Tuple p3 = B * p2;
	ASSERT_EQ(p3, Tuple::point(5, -5, 0));

	Tuple p4 = C * p3;

	ASSERT_EQ(p4, Tuple::point(15, 0, 7));

}

TEST(TransformationTest, TransformationChained) {

	Tuple p = Tuple::point(1, 0, 1);
	Matrix A = rotationX(M_PI / 2);
	Matrix B = scale(5, 5, 5);
	Matrix C = translate(10, 5, 7);

	Matrix T = C * B * A;

	ASSERT_EQ(T * p, Tuple::point(15, 0, 7));

}


TEST(RayTest, Contructor) {

	Tuple origin = Tuple::point(1, 2, 3);
	Tuple direction = Tuple::vector(4, 5, 6);

	Ray r(origin, direction);

	ASSERT_EQ(r.origin, origin);
	ASSERT_EQ(r.direction, direction);

}

TEST(RayTest, Position) {

	Ray r(Tuple::point(2, 3, 4), Tuple::vector(1, 0, 0));

	ASSERT_EQ(r.position(0), Tuple::point(2, 3, 4));
	ASSERT_EQ(r.position(1), Tuple::point(3, 3, 4));
	ASSERT_EQ(r.position(-1), Tuple::point(1, 3, 4));
	ASSERT_EQ(r.position(2.5), Tuple::point(4.5, 3, 4));

}

TEST(INTERSECTION, TwoPoints) {

	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	Sphere s;

	auto i = s.intersect(r);

	ASSERT_EQ(i.intersections.size(), 2);

	int cnt = 0;
	double ans[] = { 4, 6 };
	
	for (auto inter : i.intersections) {
		ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
		cnt++;
	}

}

TEST(INTERSECTION, Tangent) {

	Ray r(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
	Sphere s;


	auto i = s.intersect(r);

	ASSERT_EQ(i.intersections.size(), 2);

	int cnt = 0;
	double ans[] = { 5, 5 };

	for (auto inter : i.intersections) {
		ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
		cnt++;
	}

}

TEST(INTERSECTION, Miss) {

	Ray r(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
	Sphere s;

	auto i = s.intersect(r);

	ASSERT_EQ(i.intersections.size(), 0);
}

TEST(INTERSECTION, RayInsideSphere) {

	Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
	Sphere s;

	auto i = s.intersect(r);

	ASSERT_EQ(i.intersections.size(), 2);

	int cnt = 0;
	double ans[] = { -1, 1};

	for (auto inter : i.intersections) {
		ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
		cnt++;
	}
}

TEST(INTERSECTION, SphereBehindRay) {

	Ray r(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
	Sphere s;

	auto i = s.intersect(r);

	ASSERT_EQ(i.intersections.size(), 2);
	int cnt = 0;
	double ans[] = { -6, -4 };

	for (auto inter : i.intersections) {
		ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
		cnt++;
	}

}

TEST(TrackingIntersections, EncapsulatingTandObject) {

	Sphere s;
	auto x = Intersection(3.5f, &s);
	ASSERT_FLOAT_EQ(x.t, 3.5);
	ASSERT_EQ(x.s, &s);

}

TEST(TrackingIntersections, AggregatingIntersections) {

	Sphere s;
	auto x = Intersection(1, &s);
	auto x1 = Intersection(2, &s);

	Intersections i;

	i.intersections.insert(&x);
	i.intersections.insert(&x1);

	ASSERT_EQ(i.intersections.size(), 2);
	
	int cnt = 0;
	double ans[] = { 1, 2 };

	for (auto inter : i.intersections) {
		ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
		cnt++;
	}

}

TEST(TrackingIntersections, ObjectOnTheIntersection) {

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto s = Sphere();

	auto i = s.intersect(r);

	ASSERT_EQ(i.intersections.size(), 2);

	for (auto inter : i.intersections) {
		ASSERT_EQ(inter->s, &s);
	}

}

TEST(HitTest, PositiveT) {

	auto s = Sphere();

	auto i1 = Intersection(1.f, &s);
	auto i2 = Intersection(2.f, &s);

	Intersections i;

	i.intersections.insert(&i1);
	i.intersections.insert(&i2);

	auto ht = i.hit();

	ASSERT_EQ(ht, &i1);

}


TEST(HitTest, NegativeT) {

	auto s = Sphere();
	Intersections i;

	auto i1 = Intersection(-1.f, &s);
	auto i2 = Intersection(1.f, &s);

	i.intersections.insert(&i1);
	i.intersections.insert(&i2);

	auto ht = i.hit();

	ASSERT_EQ(ht, &i2);

}

TEST(HitTest, LowestNonNegative) {

	auto s = Sphere();

	Intersections i;

	auto i1 = Intersection(5.f, &s);
	auto i2 = Intersection(7.f, &s);
	auto i3 = Intersection(-3.f, &s);
	auto i4 = Intersection(2.f, &s);

	i.intersections.insert(&i1);
	i.intersections.insert(&i2);
	i.intersections.insert(&i3);
	i.intersections.insert(&i4);

	auto ht = i.hit();

	ASSERT_EQ(ht, &i4);
}

TEST(RayTest, RayTranslation) {

	Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));

	Matrix m = translate(3, 4, 5);

	auto r2 = r.transform(m);

	ASSERT_EQ(r2.origin, Tuple::point(4, 6, 8));
	ASSERT_EQ(r2.direction, Tuple::vector(0, 1, 0));

}


TEST(RayTest, RayScaling) {

	Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));

	Matrix m = scale(2, 3, 4);

	auto r2 = r.transform(m);

	ASSERT_EQ(r2.origin, Tuple::point(2, 6, 12));
	ASSERT_EQ(r2.direction, Tuple::vector(0, 3, 0));

}

TEST(RayTest, DefaultTransformation) {

	Sphere s;

	Matrix id(4, 4);
	id = identityMatrix(4);

	ASSERT_EQ(s.transform, id);

	Ray r(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));

	Matrix m = scale(2, 3, 4);

	auto r2 = r.transform(m);

	ASSERT_EQ(r2.origin, Tuple::point(2, 6, 12));
	ASSERT_EQ(r2.direction, Tuple::vector(0, 3, 0));

	auto t = translate(2, 3, 4);

	s.transform = t;

	ASSERT_EQ(s.transform, t);

}

TEST(RayTest, ScaledSphereAndRay) {
	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto s = Sphere();
	s.transform = scale(2, 2, 2);

	auto xs = s.shapeIntersect(r);

	ASSERT_EQ(xs.intersections.size(), 2);
	int cnt = 0;
	double ans[] = { 3, 7 };

	for (auto inter : xs.intersections) {
		ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
		cnt++;
	}
}

TEST(RayTest, TranslatedSphereAndRay) {
	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto s = Sphere();
	s.transform = translate(5, 0, 0);

	auto xs = s.shapeIntersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(NormalTest, NormalOnASphereXZYAxis) {
	auto s = Sphere();
	auto n = s.objectNormal( Tuple::point(1, 0, 0));

	ASSERT_EQ(n, Tuple::vector(1, 0, 0));

	n = s.objectNormal( Tuple::point(0, 1, 0));
	ASSERT_EQ(n, Tuple::vector(0, 1, 0));

	n = s.objectNormal( Tuple::point(0, 0, 1));
	ASSERT_EQ(n, Tuple::vector(0, 0, 1));

	n = s.objectNormal( Tuple::point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	ASSERT_EQ(n, Tuple::vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(NormalTest, TranslatedSphere) {
	auto s = Sphere();
	s.transform = (translate(0, 1, 0));

	auto n = s.normal(Tuple::point(0, 1.70711, -0.70711));

	ASSERT_EQ(n, Tuple::vector(0, 0.70711, -0.70711));
}

TEST(NormalTest, TransformedSphere) {
	auto s = Sphere();
	s.transform = (scale(1, 0.5, 1) * rotationZ(M_PI / 5));

	auto n = s.normal(Tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2));
	ASSERT_EQ(n, Tuple::vector(0, 0.97014, -0.24254));

}

TEST(ReflectionTest, VectorAt45) {
	auto v = Tuple::vector(1, -1, 0);
	auto n = Tuple::vector(0, 1, 0);

	auto r = v.reflect(n);

	ASSERT_EQ(r, Tuple::vector(1, 1, 0));
}

TEST(ReflectionTest, SlantedSurface) {
	auto v = Tuple::vector(0, -1, 0);
	auto n = Tuple::vector(sqrt(2) / 2, sqrt(2) / 2, 0);

	auto r = v.reflect(n);

	ASSERT_EQ(r, Tuple::vector(1, 0, 0));
}

TEST(LightTest, PointLightPositionIntensity) {
	auto intensity = Color(1, 1, 1);
	auto position = Tuple::point(0, 0, 0);
	PointLight light(intensity, position);

	ASSERT_EQ(light.position, position);
	ASSERT_EQ(light.intensity, intensity);
}

TEST(MaterialTest, SphereMaterial) {
	auto s = Sphere();
	Material material;

	ASSERT_EQ(s.material, material);
}

// NOTE: this lighting tests use intensity instead of bool in shadow value
TEST(LightingTest, EyeBetweenLight) {
	Material m;
	Tuple position = Tuple::point(0, 0, 0);
	auto eyev = Tuple::vector(0, 0, -1);
	auto normalv = Tuple::vector(0, 0, -1);
	PointLight light(Color(1, 1, 1), Tuple::point(0, 0, -10));

	auto sphere = Sphere();
	sphere.material = m;
	auto result = light.lighting(sphere.material,&sphere, position, eyev, normalv, 1);

	ASSERT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(LightingTest, EyeBetweenLightOffset45) {
	Material m;
	Tuple position = Tuple::point(0, 0, 0);
	auto eyev = Tuple::vector(0, sqrt(2) / 2, -sqrt(2) / 2);
	auto normalv = Tuple::vector(0, 0, -1);
	PointLight light(Color(1, 1, 1), Tuple::point(0, 0, -10));
	auto sphere = Sphere();
	sphere.material = m;
	auto result = light.lighting(sphere.material, &sphere, position, eyev, normalv, 1);

	ASSERT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(LightingTest, EyeOppositeLightOffset45) {
	Material m;
	Tuple position = Tuple::point(0, 0, 0);
	auto eyev = Tuple::vector(0, 0, -1);
	auto normalv = Tuple::vector(0, 0, -1);
	PointLight light(Color(1, 1, 1), Tuple::point(0, 10, -10));
	auto sphere = Sphere();
	sphere.material = m;
	auto result = light.lighting(sphere.material, &sphere, position, eyev, normalv, 1);

	ASSERT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(LightingTest, EyeInPathLightOffset45) {
	Material m;
	Tuple position = Tuple::point(0, 0, 0);
	auto eyev = Tuple::vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
	auto normalv = Tuple::vector(0, 0, -1);
	PointLight light(Color(1, 1, 1), Tuple::point(0, 10, -10));
	auto sphere = Sphere();
	sphere.material = m;
	auto result = light.lighting(sphere.material, &sphere, position, eyev, normalv, 1);

	ASSERT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(LightingTest, LightBehindSurface) {
	Material m;
	Tuple position = Tuple::point(0, 0, 0);
	auto eyev = Tuple::vector(0, 0, -1);
	auto normalv = Tuple::vector(0, 0, -1);
	PointLight light(Color(1, 1, 1), Tuple::point(0, 0, 10));
	auto sphere = Sphere();
	sphere.material = m;
	auto result = light.lighting(sphere.material, &sphere, position, eyev, normalv, 0);;

	ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(WorldTest, DefaultWorld) {
	PointLight light(Color(1, 1, 1), Tuple::point(-10, 10, -10));
	Sphere s1, s2;
	s1.material.color = Color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;

	s2.transform = scale(0.5, 0.5, 0.5);

	World w = defaultWorld();

	ASSERT_EQ(*w.lights[0], light);

	w.objects.emplace_back(&s1);
	w.objects.emplace_back(&s2);

    ASSERT_EQ(*(Sphere *)w.objects[0], s1);
	ASSERT_EQ(*(Sphere *)w.objects[1], s2);
}

TEST(WorldTest, WorldRayIntersect) {

	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto test = w.worldIntersection(r);

	double cmpTo[] = { 4, 4.5, 5.5, 6 };

	int cnt = 0;

	for (auto x : test) {
		ASSERT_FLOAT_EQ(x->t, cmpTo[cnt++]);
	}
}

TEST(PreCompute, Initialization) {
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto s = Sphere();
	Intersection i(4.f, &s);
	Precomputations comps(i, r);
	
	 //TODO: make defaults for Precomputation class
	ASSERT_FLOAT_EQ(i.t, comps.t);
	ASSERT_EQ(comps.shape, &s);
	ASSERT_EQ(comps.point, Tuple::point(0, 0, -1));

	ASSERT_EQ(comps.eyev, Tuple::vector(0, 0, -1));
	ASSERT_EQ(comps.normalv, Tuple::vector(0, 0, -1));
	
}
	
TEST(PreCompute, IntersectionOutside) {
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto s = Sphere();
	Intersection i(4.f, &s);
	Precomputations comps(i, r);

	ASSERT_EQ(comps.inside, false);
}
	
TEST(PreCompute, IntersectionInside) {
	Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
	auto s = Sphere();
	Intersection i(1.f, &s);
	Precomputations comps(i, r);

	ASSERT_EQ(comps.point, Tuple::point(0, 0, 1));
	ASSERT_EQ(comps.eyev, Tuple::vector(0, 0, -1));
	ASSERT_EQ(comps.inside, true);
	ASSERT_EQ(comps.normalv, Tuple::vector(0, 0, -1));
}

TEST(PreCompute, ShadingAnIntersection) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	Intersection i(4.f, w.objects[0]);

	Precomputations comps(i, r);

	int tmp = 1;
	auto c = w.shadeHit(comps, tmp, tmp);

	ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(PreCompute, FromInside) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
	// replacing the default light for this test
	w.lights[0] = (new PointLight(Color(1, 1, 1), Tuple::point(0, 0.25, 0)));

	Intersection i(0.5f, w.objects[1]);

	Precomputations comps(i, r);

	int tmp = 1;
	auto c = w.shadeHit(comps ,tmp, tmp);
	ASSERT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST(PreCompute, RayMiss) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));

	auto c = w.colorAt(r);

	ASSERT_EQ(c, Color(0, 0, 0));
}

TEST(PreCompute, RayHit) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto c = w.colorAt(r);

	ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(PreCompute, IntersectionBehindRay) {
	World w = defaultWorld();
	w.objects[1]->material.ambient = 1;

	Ray r(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));
	auto c = w.colorAt(r);

	ASSERT_EQ(c, w.objects[1]->material.color);
}

TEST(ViewTransformation, defaultOrientation) {
	
	Tuple from = Tuple::point(0, 0, 0);
	Tuple to = Tuple::point(0, 0, -1);
	Tuple up = Tuple::vector(0, 1, 0);
	auto t = viewTransformation(from, to, up);

	ASSERT_EQ(t, identityMatrix(4));
}

TEST(ViewTransformation, lookingInPozitiveZ) {

	Tuple from = Tuple::point(0, 0, 0);
	Tuple to = Tuple::point(0, 0, 1);
	Tuple up = Tuple::vector(0, 1, 0);
	auto t = viewTransformation(from, to, up);

	ASSERT_EQ(t, scale(-1, 1, -1));
}


TEST(ViewTransformation, viewTransfomationMovesTheWorld) {

	Tuple from = Tuple::point(0, 0, 8);
	Tuple to = Tuple::point(0, 0, 0);
	Tuple up = Tuple::vector(0, 1, 0);
	auto t = viewTransformation(from, to, up);

	ASSERT_EQ(t, translate(0, 0, -8));
}

TEST(ViewTransformation, ArbitraryViewTransform) {

	Tuple from = Tuple::point(1, 3, 2);
	Tuple to = Tuple::point(4, -2, 8);
	Tuple up = Tuple::vector(1, 1, 0);
	auto t = viewTransformation(from, to, up);

	Matrix testM(4, 4);
	testM.matrix[0] = -0.50709;
	testM.matrix[1] = 0.50709;
	testM.matrix[2] = 0.67612;
	testM.matrix[3] = -2.36643;
	testM.matrix[4] = 0.76772;
	testM.matrix[5] = 0.60609;
	testM.matrix[6] = 0.12122;
	testM.matrix[7] = -2.82843;
	testM.matrix[8] = -0.35857;
	testM.matrix[9] = 0.59761;
	testM.matrix[10] = -0.71714;
	testM.matrix[11] = 0;
	testM.matrix[12] = 0;
	testM.matrix[13] = 0;
	testM.matrix[14] = 0;
	testM.matrix[15] = 1;

	ASSERT_EQ(t, testM);
}

TEST(CameraTest, ConstructingACamera) {
	Camera c(160, 120, M_PI / 2);
	ASSERT_EQ(c.hSize, 160);
	ASSERT_EQ(c.vSize, 120);
	ASSERT_FLOAT_EQ(c.fieldOfView, M_PI / 2);
	ASSERT_EQ(c.transform, identityMatrix(4));
}

TEST(CameraTest, HorizontalCanvas) {
	Camera c(200, 125, M_PI / 2);
	ASSERT_FLOAT_EQ(c.pixelSize, 0.01);

	Camera c1(125, 200, M_PI / 2);
	ASSERT_FLOAT_EQ(c1.pixelSize, 0.01);
}

TEST(CameraTest, RayThroughCenter) {
	Camera c(201, 101, M_PI / 2);
		
	auto r = c.rayForPixel(100, 50);
	ASSERT_EQ(r.origin, Tuple::point(0,0, 0));
	ASSERT_EQ(r.direction, Tuple::vector(0, 0, -1));
}

TEST(CameraTest, RayThroughCorner) {
	Camera c(201, 101, M_PI / 2);

	auto r = c.rayForPixel(0, 0);
	ASSERT_EQ(r.origin, Tuple::point(0, 0, 0));
	ASSERT_EQ(r.direction, Tuple::vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayCameraTransformed) {
	Camera c(201, 101, M_PI / 2);
	c.transform = rotationY(M_PI / 4) * translate(0, -2, 5);
	auto r = c.rayForPixel(100, 50);
	ASSERT_EQ(r.origin, Tuple::point(0, 2, -5));
	ASSERT_EQ(r.direction, Tuple::vector(sqrt(2) / 2, 0, -sqrt(2)/2));
}

TEST(CameraTest, RenderingWithCamera) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	Camera c(11, 11, M_PI / 2);
	c.transform = viewTransformation(Tuple::point(0, 0, -5), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));

	auto image = c.render(w);

	ASSERT_EQ(image.canvas[5*11+5], Color(0.38066, 0.47583, 0.2855));
}

TEST(ShadowTest, SurfaceInShadow) {
	auto eyev = Tuple::vector(0, 0, -1);
	auto normalv= Tuple::vector(0, 0, -1);
	auto light = PointLight(Color(1, 1, 1), Tuple::point(0, 0.25, 0));
	
	auto m = Material();
	auto position = Tuple::point(0, 0, 0);

	auto sphere = Sphere();
	sphere.material = m;
	auto result = light.lighting(sphere.material,&sphere, position, eyev, normalv, 1);

	ASSERT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(ShadowTest, TestingNotInShadow) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	Tuple p = Tuple::point(0, 10, 0);

	ASSERT_FALSE(w.isShadowed(p, w.lights[0]->position));
}

TEST(ShadowTest, TestingInShadow) {
	World w = defaultWorld();
	Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	Tuple p = Tuple::point(0, 10, 0);

	ASSERT_FALSE(w.isShadowed(p, w.lights[0]->position));

	auto p1 = Tuple::point(10, -10, 10);
	ASSERT_TRUE(w.isShadowed(p1, w.lights[0]->position));
	
	auto p2 = Tuple::point(-20, 20, -20);
	ASSERT_FALSE(w.isShadowed(p2, w.lights[0]->position));

	auto p3 = Tuple::point(-2, 2, -2);
	ASSERT_FALSE(w.isShadowed(p3, w.lights[0]->position));
}

TEST(ShadowTest, ShadeHitAcne) {
	World w;
	auto s1 = Sphere();
	auto s2 = Sphere();
	s2.transform = translate(0, 0, 10);

	w.objects.emplace_back(&s1);
	w.objects.emplace_back(&s2);
	w.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(0, 0, -10)));

	auto r = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
	auto i = Intersection(4.f, w.objects[1]);

	auto comps = Precomputations(i, r);

	int tmp = 1;
	auto c = w.shadeHit(comps, tmp, tmp);

	ASSERT_EQ(c, Color(0.1, 0.1, 0.1));
}

TEST(ShadowTest, OffsetThePoint) {

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto s = Sphere();
	s.transform = translate(0, 0, 1);

	auto i = Intersection(5.f, &s);
	auto comps = Precomputations(i, r);

	ASSERT_TRUE(comps.overPoint.z < -EPSILON/2);
	ASSERT_TRUE(comps.point.z > comps.overPoint.z);
}
// TODO: tests for intersect? page 119 or all of them?

TEST(ShapesRefactor, DefaultTransformation) {
	auto s = Sphere();
	
	ASSERT_EQ(s.transform, identityMatrix(4));

	s.transform = translate(2, 3, 4);
	ASSERT_EQ(s.transform, translate(2, 3, 4));
}

TEST(ShapesRefactor, DefaultMaterial) {
	auto s = Sphere();
	Material m;

	ASSERT_EQ(s.material, m);

	m.ambient = 1;
	s.material = m;

	ASSERT_EQ(s.material, m);
}

TEST(PlaneRefactor, NormalIsConstant) {
	auto p = Plane();
	
	auto n1 = p.normal(Tuple::point(0, 0, 0));
	ASSERT_EQ(Tuple::vector(0, 1, 0), n1);

	auto n2 = p.normal(Tuple::point(10, 0, -10));
	ASSERT_EQ(Tuple::vector(0, 1, 0), n2);

	auto n3 = p.normal(Tuple::point(-5, 0, 150));
	ASSERT_EQ(Tuple::vector(0, 1, 0), n3);
}

TEST(PlaneRefactor, IntersectingParallel) {
	auto p = Plane();
	auto r = Ray(Tuple::point(0, 10, 0), Tuple::vector(0, 0, 0));

	auto xs = p.shapeIntersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(PlaneRefactor, IntersectingCoplanar) {
	auto p = Plane();
	auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));

	auto xs = p.shapeIntersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}


TEST(PlaneRefactor, IntersectingAbove) {
	auto p = Plane();
	auto r = Ray(Tuple::point(0, 1, 0), Tuple::vector(0, -1, 0));

	auto xs = p.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 1);

	for (auto inter : xs.intersections) {
		ASSERT_FLOAT_EQ(inter->t, 1);
		ASSERT_EQ(inter->s, &p);
	}
}

TEST(PlaneRefactor, IntersectingBelow) {
	auto p = Plane();
	auto r = Ray(Tuple::point(0, -1, 0), Tuple::vector(0, 1, 0));

	auto xs = p.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 1);

	for (auto inter : xs.intersections) {
		ASSERT_FLOAT_EQ(inter->t, 1);
		ASSERT_EQ(inter->s, &p);
	}
}

//TODO: generalizing paterns tests missing

TEST(PatternTest, DefaultPattern) {
	auto pattern = StripePattern();

	ASSERT_EQ(pattern.a, Color(1, 1, 1));
	ASSERT_EQ(pattern.b, Color(0, 0, 0));
}

TEST(PatternTest, PatternAt) {
	auto pattern = StripePattern();
	
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 1, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 2, 0)), Color(1, 1, 1));

	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 1)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 2)), Color(1, 1, 1));
	
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0.9, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(1, 0, 0)), Color(0, 0, 0));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(-0.1, 0, 0)), Color(0, 0, 0));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(-1, 0, 0)), Color(0, 0, 0));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(-1.1, 0, 0)), Color(1, 1, 1));
}

TEST(PatternTest, LightingWithPattern) {
	
	auto material = Material();
	material.pattern = new StripePattern();
	material.ambient = 1;
	material.diffuse = 0;
	material.specular = 0;

	auto eyev = Tuple::vector(0, 0, -1);
	auto normalv = Tuple::vector(0, 0, -1);
	auto light = PointLight(Color(1, 1, 1), Tuple::point(0, 0, -10));

	auto sphere = Sphere();
	sphere.material = material;
	auto c1 = light.lighting(sphere.material, &sphere, Tuple::point(0.9, 0, 0), eyev, normalv, false);

	auto c2 = light.lighting(sphere.material, &sphere, Tuple::point(1.1, 0, 0), eyev, normalv, false);

	ASSERT_EQ(c1, Color(1, 1, 1));
	ASSERT_EQ(c2, Color(0, 0, 0));
}

TEST(PatternTest, ObjectTransformation) {
	auto object = Sphere();
	object.transform = scale(2, 2, 2);
	object.material.pattern = new StripePattern();

	auto c = object.stripeAtObject(Tuple::point(1.5, 0, 0));
	
	ASSERT_EQ(c, Color(1, 1, 1));
}

TEST(PatternTest, StripesWithPatternTransform) {
	auto object = Sphere();
	object.material.pattern = new StripePattern();
	object.material.pattern->transform = scale(2, 2, 2);

	auto c = object.stripeAtObject(Tuple::point(1.5, 0, 0));

	ASSERT_EQ(c, Color(1, 1, 1));
}

TEST(PatternTest, StripesWithPatternAndObjectTransform) {
	auto object = Sphere();
	object.transform = scale(2, 2, 2);
	object.material.pattern = new StripePattern();
	object.material.pattern->transform = translate(0.5, 0, 0);

	auto c = object.material.pattern->patternColorAt(Tuple::point(2.5, 0, 0));

	ASSERT_EQ(c, Color(1, 1, 1));
}

TEST(PatternTest, GeneralizingPatterns) {
	auto pattern = StripePattern();
	ASSERT_EQ(pattern.transform, identityMatrix(4));
}

TEST(PatternTest, GeneralizingPatternsTransform) {
	auto pattern = StripePattern();
	pattern.transform = translate(1, 2, 3);
	ASSERT_EQ(pattern.transform, translate(1, 2, 3));
}

TEST(PatternTest, PatternWithObjectTransform) {
	
	// TODO: should i have a non member patterncolorat funciton (pattern_at_shape in the book)
	// implement a test pattern?
	auto shape = Sphere();
	shape.transform = scale(2, 2, 2);
	auto pattern = StripePattern();
	shape.material.pattern = &pattern;
	auto c = pattern.patternColorAt(Tuple::point(2, 3, 4));
	//ASSERT_EQ(c, Color(1, 1.5, 2));
}

TEST(PatternTest, PatternWihtObjectAndPatternTransform) {

	// TODO: test pattern
	auto shape = Sphere();
	shape.transform = scale(2, 2, 2);
	auto pattern = StripePattern();
	pattern.transform = translate(0.5, 1, 1.5);
	shape.material.pattern = &pattern;
	auto c = shape.stripeAtObject(Tuple::point(2.5, 3, 3.5));
	//ASSERT_EQ(c, Color(0.75, 0.75, 0.75));
}

TEST(PatternTest, GradientPatternTest) {

	auto object = Sphere();
	object.material.pattern = new GradientPattern(Color(1, 1, 1), Color(0, 0, 0));

	ASSERT_EQ(object.stripeAtObject(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(object.stripeAtObject(Tuple::point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
	ASSERT_EQ(object.stripeAtObject(Tuple::point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
	ASSERT_EQ(object.stripeAtObject(Tuple::point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}

TEST(PatternTest, RingPatternTest) {

	auto pattern = RingPattern();
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(1, 0, 0)), Color(0, 0, 0));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 1)), Color(0, 0, 0));

	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0.708, 0, 0.708)), Color(0, 0, 0));
}

TEST(PatternTest, CheckerTest) {

	auto pattern = CheckerPattern();
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0.99, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(1.01, 0, 0)), Color(0, 0, 0));

	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0.99, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 1.01, 0)), Color(0, 0, 0));

	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 0.99)), Color(1, 1, 1));
	ASSERT_EQ(pattern.patternColorAt(Tuple::point(0, 0, 1.01)), Color(0, 0, 0));
}

// TODO: nested patterns, perlin noise

TEST(ReflectivityTest, DefaultMaterial) {

	Material m;
	ASSERT_EQ(m.reflective, 0.0);
}

TEST(ReflectivityTest, ReflectionVector) {

	auto shape = Plane();
	auto r = Ray(Tuple::point(0, 1, -1), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	auto i = Intersection(sqrt(2), &shape);
	auto comps = Precomputations(i, r);

	ASSERT_EQ(comps.reflectv, Tuple::vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

TEST(ReflectivityTest, NonReflectiveMaterial) {

	World w = defaultWorld();

	auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));

	auto i = Intersection(1, w.objects[1]);
	auto comps = Precomputations(i, r);

	int tmp = 1;
	auto color = w.reflectedColor(comps, tmp, tmp);

	ASSERT_EQ(color, Color(0, 0, 0));
}

TEST(ReflectivityTest, ReflectiveMaterial) {

	World w = defaultWorld();
	
	auto shape = Plane();
	shape.material.reflective = 0.5;
	shape.transform = translate(0, -1, 0);

	w.objects.emplace_back(&shape);

	auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));

	auto i = Intersection(sqrt(2), w.objects[2]);
	auto comps = Precomputations(i, r);

	int tmp = 1;

	auto color = w.reflectedColor(comps, tmp, tmp);

	// TODO: test seems fine a bigger epsilon for tests?
	//ASSERT_EQ(color, Color(0.19032, 0.2379, 0.14274));
	ASSERT_EQ(color, Color(0.190332, 0.237915, 0.142749));
}

TEST(ReflectivityTest, ShadeHitReflectiveMaterial) {

	World w = defaultWorld();

	auto shape = Plane();
	shape.material.reflective = 0.5;
	shape.transform = translate(0, -1, 0);

	w.objects.emplace_back(&shape);

	auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));

	auto i = Intersection(sqrt(2), w.objects[2]);
	auto comps = Precomputations(i, r);

	int tmp = 1;
	auto color = w.shadeHit(comps, tmp, tmp);

	// TODO: test seems fine a bigger epsilon for tests?
	ASSERT_EQ(color, Color(0.876757, 0.92434, 0.829174));
}

TEST(ReflectivityTest, TerminateInfiniteRecursion) {

	World w = defaultWorld();

	w.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(0, 0, 0)));

	auto lower = Plane();
	lower.material.reflective = 1;
	lower.transform = translate(0, -1, 0);

	auto upper = Plane();
	upper.material.reflective = 1;
	upper.transform = translate(0, 1, 0);

	w.objects.emplace_back(&lower);
	w.objects.emplace_back(&upper);

	auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));

	Color out(0, 0, 0);
	out = w.colorAt(r);
	// TODO: test in another way test n6
	GTEST_ASSERT_NE(out, Color(0, 0, 0));

}

TEST(ReflectivityTest, ShadeHitReflectiveMaterialMaxDepth) {

	World w = defaultWorld();

	auto shape = Plane();
	shape.material.reflective = 0.5;
	shape.transform = translate(0, -1, 0);

	w.objects.emplace_back(&shape);

	auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));

	auto i = Intersection(sqrt(2), w.objects[2]);
	auto comps = Precomputations(i, r);

	int tmp = 0;
	auto color = w.reflectedColor(comps, tmp, tmp);

	// TODO: test seems fine a bigger epsilon for tests?
	//std::cout << color.r << " " << color.g << " " << color.b << "\n";
	ASSERT_EQ(color, Color(0, 0, 0));
}

TEST(RefractionTest, DefaultMaterial) {

	auto m = Material();
	ASSERT_FLOAT_EQ(m.transparency, 0.0f);
	ASSERT_FLOAT_EQ(m.refractiveIndex, 1.0f);
}

TEST(RefractionTest, GlassySphere) {

	auto s = glassSphere();
	ASSERT_EQ(s.transform, identityMatrix(4));
	ASSERT_FLOAT_EQ(s.material.transparency, 1.0);
	ASSERT_FLOAT_EQ(s.material.refractiveIndex, 1.5);

}

TEST(RefractionTest, n1n2VariousIntersections) {

	auto a = glassSphere();
	a.transform = scale(2, 2, 2);
	a.material.refractiveIndex = 1.5;

	auto b = glassSphere();
	b.transform = scale(0, 0, -0.25);
	b.material.refractiveIndex = 2.0;

	auto c = glassSphere();
	c.transform = scale(0, 0, 0.25);
	c.material.refractiveIndex = 2.5;
	
	auto tmp = Intersection(2, &a);
	auto tmp1= Intersection(2.75, &b);
	auto tmp2 = Intersection(3.25, &c);
	auto tmp3 = Intersection(4.75, &b);
	auto tmp4 = Intersection(5.25, &c);
	auto tmp5 = Intersection(6, &a);
	
	Intersections i;
	i.intersections.insert(&tmp);
	i.intersections.insert(&tmp1);
	i.intersections.insert(&tmp2);
	i.intersections.insert(&tmp3);
	i.intersections.insert(&tmp4);
	i.intersections.insert(&tmp5);

	auto r = Ray(Tuple::point(0, 0, -4), Tuple::vector(0, 0, 1));
	
	Precomputations comps;

	double testValuesn1[] = { 1.0, 1.5, 2.0, 2.5, 2.5, 1.5 };
	double testValuesn2[] = { 1.5, 2., 2.5, 2.5, 1.5, 1. };
	int cnt = 0;

	for (auto x : i.intersections) {
		comps = Precomputations(*x, r, i);
		ASSERT_FLOAT_EQ(comps.n1, testValuesn1[cnt]);
		ASSERT_FLOAT_EQ(comps.n2, testValuesn2[cnt]);
		cnt++;
	}
}

TEST(RefractionTest, UnderPoint) {

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto s = glassSphere();
	s.transform = translate(0, 0, 1);
	auto i = Intersection(5, &s);
	auto xs = Intersections();
	xs.intersections.insert(&i);

	auto comps = Precomputations(i, r, xs);

	EXPECT_TRUE(comps.underPoint.z > EPSILON / 2);
	EXPECT_TRUE(comps.point.z < comps.underPoint.z);
}

TEST(RefractionTest, opaqueSurface) {

	auto w = defaultWorld();
	auto s = w.objects[0];

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto tmp = Intersection(4, s);
	auto tmp1 = Intersection(6, s);
	
	auto xs = Intersections();
	xs.intersections.insert(&tmp);
	xs.intersections.insert(&tmp1);

	auto comps = Precomputations(tmp, r, xs);

	int cnt = 5;
	auto c = w.refractedColor(comps, cnt, cnt);
	
	ASSERT_EQ(c, Color(0, 0, 0));
}

TEST(RefractionTest, maxRecursiveDepth) {

	auto w = defaultWorld();
	auto s = w.objects[0];
	s->material.transparency = 1.0;
	s->material.refractiveIndex = 1.5;

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto tmp = Intersection(4, s);
	auto tmp1 = Intersection(6, s);

	auto xs = Intersections();
	xs.intersections.insert(&tmp);
	xs.intersections.insert(&tmp1);

	auto comps = Precomputations(tmp, r, xs);

	int cnt = 0;
	auto c = w.refractedColor(comps, cnt, cnt);

	ASSERT_EQ(c, Color(0, 0, 0));
}

TEST(RefractionTest, totalInternalReflection) {

	auto w = defaultWorld();
	auto s = w.objects[0];
	s->material.ambient = 1.0;
	s->material.pattern = new TestPatern();

	auto b = w.objects[1];
	b->material.transparency = 1.0;
	b->material.refractiveIndex = 1.5;

	auto r = Ray(Tuple::point(0, 0, 0.1), Tuple::vector(0, 1, 0));
	
	auto tmp = Intersection(-0.9899, s);
	auto tmp1 = Intersection(-0.4899, b);
	auto tmp2 = Intersection(0.4899, b);
	auto tmp3 = Intersection(0.9899, s);

	auto xs = Intersections();
	xs.intersections.insert(&tmp);
	xs.intersections.insert(&tmp1);
	xs.intersections.insert(&tmp2);
	xs.intersections.insert(&tmp3);

	auto comps = Precomputations(tmp2, r, xs);

	int cnt = 5;
	auto c = w.refractedColor(comps, cnt, cnt);

	//TODO: not the same color as in the book (but really really close) smaller epsilon?
	ASSERT_EQ(c, Color(0, 0.998875, 0.047219));
}

TEST(RefractionTest, shadeHitTransparentMaterial) {

	auto w = defaultWorld();
	auto floor = Plane();
	floor.transform = translate(0, -1, 0);
	floor.material.transparency = 0.5;
	floor.material.refractiveIndex = 1.5;

	w.objects.emplace_back(&floor);
	auto ball = Sphere();
	ball.material.color = Color(1, 0, 0);
	ball.material.ambient = 0.5;
	ball.transform = translate(0, -3.5, -0.5);

	w.objects.emplace_back(&ball);

	auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));

	auto tmp = Intersection(sqrt(2), &floor);

	auto xs = Intersections();
	xs.intersections.insert(&tmp);

	auto comps = Precomputations(tmp, r, xs);

	auto cnt = 5;
	auto color = w.shadeHit(comps, cnt, cnt);
	ASSERT_EQ(color, Color(0.93642, 0.68642, 0.68642));
}

TEST(FresnelEffect, InternalReflection) {
	auto shape = glassSphere();
	auto r = Ray(Tuple::point(0, 0, sqrt(2) / 2), Tuple::vector(0, 1, 0));
	auto tmp1 = Intersection(-sqrt(2) / 2, &shape);
	auto tmp2 = Intersection(sqrt(2) / 2, &shape);

	auto xs = Intersections();
	xs.intersections.insert(&tmp1);
	xs.intersections.insert(&tmp2);

	auto comps = Precomputations(tmp2, r, xs);
	auto reflectance = comps.schlick();

	ASSERT_FLOAT_EQ(reflectance, 1.0);
}

TEST(FresnelEffect, SchlickAproxPerpendicular) {
	auto shape = glassSphere();
	auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
	auto tmp1 = Intersection(-1, &shape);
	auto tmp2 = Intersection(1, &shape);

	auto xs = Intersections();
	xs.intersections.insert(&tmp1);
	xs.intersections.insert(&tmp2);

	auto comps = Precomputations(tmp2, r, xs);
	auto reflectance = comps.schlick();

	ASSERT_FLOAT_EQ(reflectance, 0.04);
}

TEST(FresnelEffect, N2GreaterThanN1) {
	auto shape = glassSphere();
	auto r = Ray(Tuple::point(0, 0.99, -2), Tuple::vector(0, 0, 1));
	auto tmp1 = Intersection(1.8589, &shape);

	auto xs = Intersections();
	xs.intersections.insert(&tmp1);

	auto comps = Precomputations(tmp1, r, xs);
	auto reflectance = comps.schlick();

	// TODO: book is 0.48873 smaller epsilon?
	ASSERT_FLOAT_EQ(reflectance, 0.48873082);
}

TEST(FresnelEffect, ReflectiveTransparentMaterial) {
	auto w = defaultWorld();
	auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	auto floor = Plane();
	floor.transform = translate(0, -1, 0);
	floor.material.reflective = 0.5;
	floor.material.transparency = 0.5;
	floor.material.refractiveIndex = 1.5;

	w.objects.emplace_back(&floor);

	auto ball = Sphere();
	ball.material.color = Color(1, 0, 0);
	ball.material.ambient = 0.5;
	ball.transform = translate(0, -3.5, -0.5);

	w.objects.emplace_back(&ball);

	auto tmp = Intersection(sqrt(2), &floor);
	auto xs = Intersections();
	xs.intersections.insert(&tmp);

	auto comps = Precomputations(tmp, r, xs);
	int cnt = 5;

	auto color = w.shadeHit(comps, cnt, cnt);

	ASSERT_EQ(color, Color(0.93391, 0.69643, 0.69243));

}

TEST(CubeTest, RayIntersectsCube) {

	auto c = Cube();

	std::vector<Ray> testRay{
		Ray(Tuple::point(5, 0.5, 0), Tuple::vector(-1, 0, 0)),
		Ray(Tuple::point(-5, 0.5, 0), Tuple::vector(1, 0, 0)),
		Ray(Tuple::point(0.5, 5, 0), Tuple::vector(0, -1, 0)),
		Ray(Tuple::point(0.5, -5, 0), Tuple::vector(0, 1, 0)),
		Ray(Tuple::point(0.5, 0, 5), Tuple::vector(0, 0, -1)),
		Ray(Tuple::point(0.5, 0, -5), Tuple::vector(0, 0, 1)),
		Ray(Tuple::point(0, 0.5, 0), Tuple::vector(0, 0, 1))
	};

	double ans[] = {4, 6, 4, 6, 4, 6, 4, 6, 4, 6, 4, 6, -1, 1};
	double t2[] = {6, 6, 6, 6, 6, 6, 1};

	auto cnt = 0;

	for (auto x : testRay) {
		auto xs = c.intersect(x);
		
		for (auto inter : xs.intersections) {

			ASSERT_EQ(xs.intersections.size(), 2);
			ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
			cnt++;
		}
	}
}

TEST(CubeTest, RayMissCube) {

	auto c = Cube();

	std::vector<Ray> testRay{
		Ray(Tuple::point(-2, 0, 0), Tuple::vector(0.2673, 0.5345, 0.8018)),
		Ray(Tuple::point(0, -2, 0), Tuple::vector(0.8018, 0.2673, 0.5345)),
		Ray(Tuple::point(0, 0, -2), Tuple::vector(0.5345, 0.8018, 0.2673)),
		Ray(Tuple::point(2, 0, 2), Tuple::vector(0, 0, -1)),
		Ray(Tuple::point(0, 2, 2), Tuple::vector(0, -1, 0)),
		Ray(Tuple::point(2, 2, 0), Tuple::vector(-1, 0, 0))
	};

	for (auto x : testRay) {
		auto xs = c.intersect(x);
		ASSERT_EQ(xs.intersections.size(), 0);
	}
}

TEST(CubeTest, NormalCube) {

	auto c = Cube();

	std::vector<Tuple> point{
		Tuple::point(1, 0.5, -0.8),
		Tuple::point(-1, -0.2, 0.9),
		Tuple::point(-0.4, 1, -0.1),
		Tuple::point(0.3, -1, -0.7),
		Tuple::point(-0.6, 0.3, 1),
		Tuple::point(0.4, 0.4, -1),
		Tuple::point(1, 1, 1),
		Tuple::point(-1, -1, -1)
	};

	std::vector<Tuple> normal{
		Tuple::vector(1, 0, 0),
		Tuple::vector(-1, 0, 0),
		Tuple::vector(0, 1, 0),
		Tuple::vector(0, -1, 0),
		Tuple::vector(0, 0, 1),
		Tuple::vector(0, 0, -1),
		Tuple::vector(1, 0, 0),
		Tuple::vector(-1, 0, 0)
	};

	auto cnt = 0;

	for (auto x : point) {
		auto n = c.objectNormal(x);

		ASSERT_EQ(n, normal[cnt]);
		cnt++;
	}
}

TEST(CylinderTest, RayMisses) {

	auto cyl = Cylinder();
	std::vector<Tuple> origin = { Tuple::point(1, 0, 0), Tuple::point(0, 0, 0), Tuple::point(0, 0, -5) };
	std::vector<Tuple> direction = { Tuple::vector(0, 1, 0), Tuple::vector(0, 1, 0), Tuple::vector(1, 1, 1) };

	for (int i = 0; i < 3; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(origin[i], dir);
		auto xs = cyl.intersect(r);

		ASSERT_EQ(xs.intersections.size(), 0);
	}
}

TEST(CylinderTest, RayHits) {

	auto cyl = Cylinder();
	std::vector<Tuple> origin = { Tuple::point(1, 0, -5), Tuple::point(0, 0, -5), Tuple::point(0.5, 0, -5) };
	std::vector<Tuple> direction = { Tuple::vector(0, 0, 1), Tuple::vector(0, 0, 1), Tuple::vector(0.1, 1, 1) };

	double ans[] = {5, 5, 4, 6, 6.80798, 7.0887237};
	// TODO: small difference compared to the book smaller epsilon?
	double t1[] = { 5, 6, 7.0887237 };

	auto cnt = 0;

	for (int i = 0; i < 3; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(origin[i], dir);
		auto xs = cyl.intersect(r);

		for (auto inter : xs.intersections) {
			ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
			cnt++;
		}
	}
}

TEST(CylinderTest, NormalVector) {

	auto cyl = Cylinder();
	std::vector<Tuple> point = { Tuple::point(1, 0, 0), Tuple::point(0, 5, -1), Tuple::point(0, -2, 1), Tuple::point(-1, -1, 0) };
	std::vector<Tuple> normal = { Tuple::vector(1, 0, 0), Tuple::vector(0, 0, -1), Tuple::vector(0, 0, 1), Tuple::vector(-1, 0, 0)};

	for (int i = 0; i < 4; ++i) {
		auto n = cyl.objectNormal(point[i]);
		ASSERT_EQ(n, normal[i]);
	}
}

TEST(CylinderTest, DefaultMinMax) {

	auto cyl = Cylinder();
	ASSERT_FLOAT_EQ(cyl.minimum, -INFINITY);
	ASSERT_FLOAT_EQ(cyl.maximum, INFINITY);
}

TEST(CylinderTest, IntersectingConstrained) {

	auto cyl = Cylinder();
	std::vector<Tuple> point = { Tuple::point(0, 1.5, 0), Tuple::point(0, 3, -5), Tuple::point(0, 0, -5), Tuple::point(0, 2, -5), Tuple::point(0, 1, -5), Tuple::point(0, 1.5, -2) };
	std::vector<Tuple> direction = { Tuple::vector(0.1, 1, 0), Tuple::vector(0, 0, 1), Tuple::vector(0, 0, 1) , Tuple::vector(0, 0, 1) , Tuple::vector(0, 0, 1) , Tuple::vector(0, 0, 1) };

	cyl.maximum = 2;
	cyl.minimum = 1;

	double count[] = { 0, 0, 0, 0, 0, 2 };

	for (int i = 0; i < 5; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(point[i], dir);
		auto xs = cyl.intersect(r);

		ASSERT_EQ(xs.intersections.size(), count[i]);
	}
}

TEST(CylinderTest, DefaultClosed) {

	auto cyl = Cylinder();
	ASSERT_EQ(cyl.closed, false);
}

TEST(CylinderTest, IntersectingClosedCaps) {

	auto cyl = Cylinder();
	cyl.minimum = 1;
	cyl.maximum = 2;
	cyl.closed = true;

	std::vector<Tuple> point = { Tuple::point(0, 3, 0), Tuple::point(0, 3, -2), Tuple::point(0, 4, -2), Tuple::point(0, 0, -2), Tuple::point(0, -1, -2) };
	std::vector<Tuple> direction = { Tuple::vector(0, -1, 0), Tuple::vector(0, -1, 2), Tuple::vector(0, -1, 1) , Tuple::vector(0, 1, 2) , Tuple::vector(0, 1, 1) };

	for (int i = 0; i < 5; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(point[i], dir);
		auto xs = cyl.intersect(r);

		ASSERT_EQ(xs.intersections.size(), 2);
	}
}

TEST(CylinderTest, NormalVectorEndCaps) {

	auto cyl = Cylinder();
	cyl.minimum = 1;
	cyl.maximum = 2;
	cyl.closed = true;

	std::vector<Tuple> point = { Tuple::point(0, 1, 0), Tuple::point(0.5, 1, 0), Tuple::point(0, 1, 0.5), Tuple::point(0, 2, 0), Tuple::point(0.5, 2, 0), Tuple::point(0, 2, 0.5) };
	std::vector<Tuple> normal = { Tuple::vector(0, -1, 0), Tuple::vector(0, -1, 0), Tuple::vector(0, -1, 0) , Tuple::vector(0, 1, 0), Tuple::vector(0, 1, 0), Tuple::vector(0, 1, 0) };

	for (int i = 0; i < 6; ++i) {
		
		auto n = cyl.objectNormal(point[i]);


		ASSERT_EQ(n, normal[i]);
	}
}

TEST(ConeTest, ConeIntersection) {

	auto cyl = Cone();

	std::vector<Tuple> origin = { Tuple::point(0, 0, -5), Tuple::point(0, 0, -5), Tuple::point(1, 1, -5) };
	std::vector<Tuple> direction = { Tuple::vector(0, 0, 1), Tuple::vector(1, 1, 1), Tuple::vector(-0.5, -1, 1) };

	//TODO: small difference in number compared to the book, use a smaller epsilon?
	double ans[] = { 5, 5, 8.6602545, 8.6602545, 4.5500555, 49.44994 };
	double t1[] = { 5, 8.6602545, 49.44994 };
	auto cnt = 0;

	for (int i = 0; i < 3; ++i) {

		auto dir = direction[i].normalize();
		auto r = Ray(origin[i], dir);
		auto xs = cyl.intersect(r);

		for (auto inter : xs.intersections) {

			ASSERT_EQ(xs.intersections.size(), 2);
			ASSERT_FLOAT_EQ(inter->t, ans[cnt]);
			cnt++;
		}
	}
}

TEST(ConeTest, ConeRayParralelToHalve) {

	auto cyl = Cone();
	auto direction = Tuple::vector(0, 1, 1).normalize();
	auto r = Ray(Tuple::point(0, 0, -1), direction);

	auto xs = cyl.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 1);
	//TODO: small difference in number compared to the book, use a smaller epsilon?
	for (auto inter : xs.intersections) {
		ASSERT_FLOAT_EQ(inter->t, 0.35355338);
	}
}

TEST(ConeTest, ConesEndCaps) {

	auto cyl = Cone();
	cyl.minimum = -0.5;
	cyl.maximum = 0.5;
	cyl.closed = true;

	std::vector<Tuple> origin = { Tuple::point(0, 0, -5), Tuple::point(0, 0, -0.25), Tuple::point(0, 0, -0.25) };
	std::vector<Tuple> direction = { Tuple::vector(0, 1, 0), Tuple::vector(0, 1, 1), Tuple::vector(0, 1, 0) };

	int cnt[] = { 0, 2, 4 };

	for (int i = 0; i < 3; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(origin[i], dir);

		auto xs = cyl.intersect(r);

		ASSERT_EQ(xs.intersections.size(), cnt[i]);
	}
}

TEST(ConeTest, ConeNormal) {

	auto cyl = Cone();
	cyl.minimum = -0.5;
	cyl.maximum = 0.5;
	cyl.closed = true;

	std::vector<Tuple> point = { Tuple::point(0, 0, 0), Tuple::point(1, 1, 1), Tuple::point(-1, -1, 0) };
	std::vector<Tuple> normal = { Tuple::vector(0, 0, 0), Tuple::vector(1, -sqrt(2), 1), Tuple::vector(-1, 1, 0)};

	for (int i = 0; i < 3; ++i) {
		auto n = cyl.objectNormal(point[i]);

		ASSERT_EQ(n, normal[i]);
	}
}

TEST(GroupTest, DefaultGroup) {
	auto g = Group();
	ASSERT_EQ(g.transform, identityMatrix(4));
	ASSERT_EQ(g.children.size(), 0);
}

TEST(GroupTest, ShapeParent) {
	//TODO: test shape
	auto s = Sphere();
	ASSERT_EQ(s.parent, nullptr);
}

TEST(GroupTest, AddingAChild) {
	auto g = Group();
	auto s = Sphere();
	g.addChild(&s);

	ASSERT_EQ(g.children.size(), 1);
	ASSERT_EQ(g.children[0], &s);
	ASSERT_EQ(s.parent, &g); 
}

TEST(GroupTest, IntersectingWihtEmptyGroup) {
	auto g = Group();
	auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));

	auto xs = g.intersect(r);
	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(GroupTest, IntersectingWihtNonEmptyGroup) {
	auto g = Group();
	auto s1 = Sphere();
	auto s2 = Sphere();

	s2.transform = translate(0, 0, -3);
	auto s3 = Sphere();
	s3.transform = translate(5, 0, 0);

	g.addChild(&s1);
	g.addChild(&s2);
	g.addChild(&s3);

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto xs = g.intersect(r);
	
	ASSERT_EQ(xs.intersections.size(), 4);

	Sphere* ans[] = { &s2, &s2, &s1, &s1 };
	auto cnt = 0;

	for (auto inter : xs.intersections) {
		ASSERT_EQ(inter->s, ans[cnt]);
		cnt++;
	}

}

TEST(GroupTest, IntersectingWihtTransformedGroup) {
	auto g = Group();
	g.transform = scale(2, 2, 2);
	auto s = Sphere();
	s.transform = translate(5, 0, 0);

	g.addChild(&s);
	auto r = Ray(Tuple::point(10, 0, -10), Tuple::vector(0, 0, 1));

	auto xs = g.shapeIntersect(r);

	ASSERT_EQ(xs.intersections.size(), 2);
}

TEST(GroupTest, WorldToObjectSpace) {
	auto g1 = new Group();

	g1->transform = rotationY(M_PI / 2);

	auto g2 = new Group();
	g2->transform = scale(2, 2, 2);

	g1->addChild(g2);

	auto s = Sphere();

	s.transform = translate(5, 0, 0);

	g2->addChild(&s);

	auto p = s.worldToObject(Tuple::point(-2, 0, -10));

	ASSERT_EQ(p, Tuple::point(0, 0, -1));
}


TEST(GroupTest, normalToWorldSpace) {
	auto g1 = Group();

	g1.transform = rotationY(M_PI / 2);

	auto g2 = new Group();
	g2->transform = scale(1, 2, 3);

	g1.addChild(g2);

	auto s = Sphere();

	s.transform = translate(5, 0, 0);

	g2->addChild(&s);

	auto p = s.normalToWorld(Tuple::vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

	//TODO: not the same as in the book smaller epsilon?
	ASSERT_EQ(p, Tuple::vector(0.285714, 0.428571, - 0.857143));
}

TEST(BoundingBox, BoundingBoxDefault) {
	auto box = BoundingBox();

	// TODO: why doesn't this work
	// check all infinity comparisons
	//ASSERT_EQ(box.boxMin, Tuple::point(INFINITY, INFINITY, INFINITY));

	ASSERT_FLOAT_EQ(box.boxMin.x, INFINITY);
	ASSERT_FLOAT_EQ(box.boxMin.y, INFINITY);
	ASSERT_FLOAT_EQ(box.boxMin.z, INFINITY);

	ASSERT_FLOAT_EQ(box.boxMax.x, -INFINITY);
	ASSERT_FLOAT_EQ(box.boxMax.y, -INFINITY);
	ASSERT_FLOAT_EQ(box.boxMax.z, -INFINITY);
}

TEST(BoundingBox, BoundingBoxWithVolume) {
	auto box = BoundingBox(Tuple::point(-1, -2, -3) , Tuple::point(3, 2, 1));
	
	ASSERT_EQ(box.boxMin, Tuple::point(-1, -2, -3));
	ASSERT_EQ(box.boxMax, Tuple::point(3, 2, 1));
}

TEST(BoundingBox, AddingPointsToBoundingBox) {
	auto box = BoundingBox();

	Tuple p1 = Tuple::point(-5, 2, 0);
	Tuple p2 = Tuple::point(7, 0, -3);

	box.addPoint(p1);
	box.addPoint(p2);

	ASSERT_EQ(box.boxMin, Tuple::point(-5.f, 0.f, -3.f));
	ASSERT_EQ(box.boxMax, Tuple::point(7.f, 2.f, 0.f));

}

TEST(BoundingBox, SphereBoundingBox) {
	auto shape = Sphere();
	auto box = shape.boundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(-1, -1, -1));
	ASSERT_EQ(box.boxMax, Tuple::point(1, 1, 1));

}

TEST(BoundingBox, PlaneBoundingBox) {
	auto shape = Plane();
	auto box = shape.boundsOf();

	//TODO: Why can't i compare points
	ASSERT_FLOAT_EQ(box.boxMin.x, -INFINITY);
	ASSERT_FLOAT_EQ(box.boxMin.y, 0);
	ASSERT_FLOAT_EQ(box.boxMin.z, -INFINITY);

	ASSERT_FLOAT_EQ(box.boxMax.x, INFINITY);
	ASSERT_FLOAT_EQ(box.boxMax.y, 0);
	ASSERT_FLOAT_EQ(box.boxMax.z, INFINITY);
}

TEST(BoundingBox, CubeBoundingBox) {
	auto shape = Cube();
	auto box = shape.boundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(-1, -1, -1));
	ASSERT_EQ(box.boxMax, Tuple::point(1, 1, 1));
}

TEST(BoundingBox, UnboundCylinderBoundingBox) {
	auto shape = Cylinder();
	auto box = shape.boundsOf();

	//TODO: Why can't i compare points
	ASSERT_FLOAT_EQ(box.boxMin.x, -1);
	ASSERT_FLOAT_EQ(box.boxMin.y, -INFINITY);
	ASSERT_FLOAT_EQ(box.boxMin.z, -1);

	ASSERT_FLOAT_EQ(box.boxMax.x, 1);
	ASSERT_FLOAT_EQ(box.boxMax.y, INFINITY);
	ASSERT_FLOAT_EQ(box.boxMax.z, 1);
}

TEST(BoundingBox, BoundCylinderBoundingBox) {
	auto shape = Cylinder();
	shape.minimum = -5;
	shape.maximum = 3;
	auto box = shape.boundsOf();
	
	ASSERT_EQ(box.boxMin, Tuple::point(-1, -5, -1));
	ASSERT_EQ(box.boxMax, Tuple::point(1, 3, 1));
}

TEST(BoundingBox, UnboundConeBoundingBox) {
	auto shape = Cone();
	auto box = shape.boundsOf();

	//TODO: Why can't i compare points
	ASSERT_FLOAT_EQ(box.boxMin.x, -INFINITY);
	ASSERT_FLOAT_EQ(box.boxMin.y, -INFINITY);
	ASSERT_FLOAT_EQ(box.boxMin.z, -INFINITY);

	ASSERT_FLOAT_EQ(box.boxMax.x, INFINITY);
	ASSERT_FLOAT_EQ(box.boxMax.y, INFINITY);
	ASSERT_FLOAT_EQ(box.boxMax.z, INFINITY);

}

TEST(BoundingBox,BoundConeBoundingBox) {
	auto shape = Cone();
	shape.minimum = -5;
	shape.maximum = 3;
	auto box = shape.boundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(-5, -5, -5));
	ASSERT_EQ(box.boxMax, Tuple::point(5, 3, 5));
}

//TODO: test shape

TEST(BoundingBox, AddingBoxes) {
	auto box1 = BoundingBox(Tuple::point(-5, -2, 0), Tuple::point(7, 4, 4));
	auto box2 = BoundingBox(Tuple::point(8, -7, -2), Tuple::point(14, 2, 8));

	box1.mergeBox(box2);

	ASSERT_EQ(box1.boxMin, Tuple::point(-5, -7, -2));
	ASSERT_EQ(box1.boxMax, Tuple::point(14, 4, 8));
}

TEST(BoundingBox, BoxContainsPoint) {
	auto box = BoundingBox(Tuple::point(5, -2, 0), Tuple::point(11, 4, 7));

	Tuple points[] = {
						Tuple::point(5, -2, 0),
						Tuple::point(11, 4, 7),
						Tuple::point(8, 1, 3),
						Tuple::point(3, 0, 3),
						Tuple::point(8, -4, 3),
						Tuple::point(8, 1, -1),
						Tuple::point(13, 1, 3),
						Tuple::point(8, 5, 3),
						Tuple::point(8, 1, 8)
	};

	bool ans[] = { true, true, true, false, false, false, false, false, false };
	for (int i = 0; i < 9; ++i) {
		auto tmp = box.contains(points[i]);
		ASSERT_EQ(tmp, ans[i]);
	}
}

TEST(BoundingBox, BoxContainsBox) {
	auto box = BoundingBox(Tuple::point(5, -2, 0), Tuple::point(11, 4, 7));
	auto box1 = BoundingBox(Tuple::point(5, -2, 0), Tuple::point(11, 4, 7));
	auto box2 = BoundingBox(Tuple::point(6, -1, 1), Tuple::point(10, 3, 6));
	auto box3 = BoundingBox(Tuple::point(4, -3, -1), Tuple::point(10, 3, 6));
	auto box4 = BoundingBox(Tuple::point(6, -1, 1), Tuple::point(12, 5, 8));

	EXPECT_TRUE(box.contains(box1));
	EXPECT_TRUE(box.contains(box2));
	EXPECT_FALSE(box.contains(box3));
	EXPECT_FALSE(box.contains(box4));
}

TEST(BoundingBox, TransformingBoundingBox) {
	auto box = BoundingBox(Tuple::point(-1, -1, -1), Tuple::point(1, 1, 1));
	auto matrix = rotationX(M_PI / 4) * rotationY(M_PI / 4);
	auto box2 = box.transform(matrix);

	// TODO: not the same as in the book, smaller epsilon for tests?
	ASSERT_EQ(box2.boxMin, Tuple::point(-1.41421, -1.70711, -1.70711));
	ASSERT_EQ(box2.boxMax, Tuple::point(1.41421, 1.70711, 1.70711));
}

TEST(BoundingBox, BoundingBoxInParentSpace) {
	auto shape = Sphere();
	shape.transform = translate(1, -3, 5) * scale(0.5, 2, 4);
	auto box = shape.parentSpaceBoundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(0.5, -5, 1));
	ASSERT_EQ(box.boxMax, Tuple::point(1.5, -1, 9));
}

TEST(BoundingBox, GroupBoundingBoxWithChildren) {
	auto s = Sphere();
	s.transform = translate(2, 5, -3) * scale(2, 2, 2);
	auto c = Cylinder();
	c.minimum = -2;
	c.maximum = 2;
	c.transform = translate(-4, -1, 4) * scale(0.5, 1, 0.5);

	auto shape = Group();

	shape.addChild(&s);
	shape.addChild(&c);

	auto box = shape.boundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(-4.5, -3, -5));
	ASSERT_EQ(box.boxMax, Tuple::point(4, 7, 4.5));
}
//TODO tests for CSG



TEST(BoundingBox, IntersectingRayWithBoundingBoxAtOrigin) {
	auto box = BoundingBox(Tuple::point(-1, -1, -1), Tuple::point(1, 1, 1));

	Tuple origin[] = {
		  Tuple::point(5, 0.5, 0),
		  Tuple::point(-5, 0.5, 0),
		  Tuple::point(0.5, 5, 0),
		  Tuple::point(0.5, -5, 0),
		  Tuple::point(0.5, 0, 5),
		  Tuple::point(0.5, 0, -5),
		  Tuple::point(0, 0.5, 0),
		  Tuple::point(-2, 0, 0),
		  Tuple::point(0, -2, 0),
		  Tuple::point(0, 0, -2),
		  Tuple::point(2, 0, 2),
		  Tuple::point(0, 2, 2),
		  Tuple::point(2, 2, 0)
	};


	Tuple direction[] = {
		 Tuple::vector(-1, 0, 0),
		 Tuple::vector(1, 0, 0),
		 Tuple::vector(0, -1, 0),
		 Tuple::vector(0, 1, 0),
		 Tuple::vector(0, 0, -1),
		 Tuple::vector(0, 0, 1),
		 Tuple::vector(0, 0, 1),
		 Tuple::vector(2, 4, 6),
		 Tuple::vector(6, 2, 4),
		 Tuple::vector(4, 6, 2),
		 Tuple::vector(0, 0, -1),
		 Tuple::vector(0, -1, 0),
		 Tuple::vector(-1, 0, 0)
	};


	bool result[] = {
		true,
		true,
		true,
		true,
		true,
		true,
		true,
		false,
		false,
		false,
		false,
		false,
		false
	};

	for (int i = 0; i < 13; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(origin[i], dir);
		ASSERT_EQ(box.intersect(r), result[i]);
	}
}

TEST(BoundingBox, IntersectingRayWithNonCubicBoundingBox) {
	auto box = BoundingBox(Tuple::point(5, -2, 0), Tuple::point(11, 4, 7));

	Tuple origin[] = {
		  Tuple::point(15, 1, 2) ,
		  Tuple::point(-5, -1, 4),
		  Tuple::point(7, 6, 5),
		  Tuple::point(9, -5, 6),
		  Tuple::point(8, 2, 12),
		  Tuple::point(6, 0, -5),
		  Tuple::point(8, 1, 3.5),
		  Tuple::point(9, -1, -8),
		  Tuple::point(8, 3, -4),
		  Tuple::point(9, -1, -2),
		  Tuple::point(4, 0, 9),
		  Tuple::point(8, 6, -1),
		  Tuple::point(12, 5, 4)
	};


	Tuple direction[] = {
		 Tuple::vector(-1, 0, 0),
		 Tuple::vector(1, 0, 0),
		 Tuple::vector(0, -1, 0),
		 Tuple::vector(0, 1, 0),
		 Tuple::vector(0, 0, -1),
		 Tuple::vector(0, 0, 1),
		 Tuple::vector(0, 0, 1),
		 Tuple::vector(2, 4, 6),
		 Tuple::vector(6, 2, 4),
		 Tuple::vector(4, 6, 2),
		 Tuple::vector(0, 0, -1),
		 Tuple::vector(0, -1, 0),
		 Tuple::vector(-1, 0, 0)
	};


	bool result[] = {
		true,
		true,
		true,
		true,
		true,
		true,
		true,
		false,
		false,
		false,
		false,
		false,
		false
	};

	for (int i = 0; i < 13; ++i) {
		auto dir = direction[i].normalize();
		auto r = Ray(origin[i], dir);
		ASSERT_EQ(box.intersect(r), result[i]);
	}
}
// TODO: tests for Using the bounding box as an optimization


TEST(BoundingBox, SplittingAPerfectCube) {
	auto box = BoundingBox(Tuple::point(-1, -4, -5), Tuple::point(9, 6, 5));
	BoundingBox left;
	BoundingBox right;

	box.splitBounds(&left, &right);

	ASSERT_EQ(left.boxMin, Tuple::point(-1, -4, -5));
	ASSERT_EQ(left.boxMax, Tuple::point(4, 6, 5));
	ASSERT_EQ(right.boxMin, Tuple::point(4, -4, -5));
	ASSERT_EQ(right.boxMax, Tuple::point(9, 6, 5));
}

TEST(BoundingBox, SplittingAnXWideBox) {
	auto box = BoundingBox(Tuple::point(-1, -2, -3), Tuple::point(9, 5.5, 3));
	BoundingBox left;
	BoundingBox right;

	box.splitBounds(&left, &right);

	ASSERT_EQ(left.boxMin, Tuple::point(-1, -2, -3));
	ASSERT_EQ(left.boxMax, Tuple::point(4, 5.5, 3));
	ASSERT_EQ(right.boxMin, Tuple::point(4, -2, -3));
	ASSERT_EQ(right.boxMax, Tuple::point(9, 5.5, 3));
}

TEST(BoundingBox, SplittingAnYWideBox) {
	auto box = BoundingBox(Tuple::point(-1, -2, -3), Tuple::point(5, 8, 3));
	BoundingBox left;
	BoundingBox right;

	box.splitBounds(&left, &right);

	ASSERT_EQ(left.boxMin, Tuple::point(-1, -2, -3));
	ASSERT_EQ(left.boxMax, Tuple::point(5, 3, 3));
	ASSERT_EQ(right.boxMin, Tuple::point(- 1, 3, -3));
	ASSERT_EQ(right.boxMax, Tuple::point(5, 8, 3));
}

TEST(BoundingBox, SplittingAnZWideBox) {
	auto box = BoundingBox(Tuple::point(-1, -2, -3), Tuple::point(5, 3, 7));
	BoundingBox left;
	BoundingBox right;

	box.splitBounds(&left, &right);

	ASSERT_EQ(left.boxMin, Tuple::point(- 1, -2, -3));
	ASSERT_EQ(left.boxMax, Tuple::point(5, 3, 2));
	ASSERT_EQ(right.boxMin, Tuple::point(-1, -2, 2));
	ASSERT_EQ(right.boxMax, Tuple::point(5, 3, 7));
}

TEST(BoundingBox, PartitioningGroupsChildren) {
	auto s1 = Sphere();
	s1.transform = translate(-2, 0, 0);

	auto s2 = Sphere();
	s2.transform = translate(2, 0, 0);

	auto s3 = Sphere();

	auto g = Group();
	g.addChild(&s1);
	g.addChild(&s2);
	g.addChild(&s3);

	auto left = Group();
	auto right = Group();

	g.partitionChildren(left, right);

	ASSERT_EQ(1, g.children.size());
	ASSERT_EQ(&s3, g.children[0]);

	ASSERT_EQ(1, left.children.size());
	ASSERT_EQ(&s1, left.children[0]);

	ASSERT_EQ(1, right.children.size());
	ASSERT_EQ(&s2, right.children[0]);
}

TEST(BoundingBox, SubGroupFromList) {
	auto s1 = Sphere();
	auto s2 = Sphere();
	
	auto g = Group();
	
	auto newG = Group();
	newG.addChild(&s1);
	newG.addChild(&s2);
	
	g.makeSubgroup(newG);

	ASSERT_EQ(g.children.size(), 1);
	
	//TODO: do this without casting
	Group* t = (Group *)g.children[0];
	ASSERT_EQ(t->children.size(), 2);
	ASSERT_EQ(t->children[0], &s1);
	ASSERT_EQ(t->children[1], &s2);
	
}

//TODO Subdividing a primitive does nothing

TEST(BoundingBox, SubdividingAgroupPartitionsItsChildren) {
	auto s1 = Sphere();
	s1.transform = translate(-2, -2, 0);
	auto s2 = Sphere();
	s2.transform = translate(-2, 2, 0);
	auto s3 = Sphere();
	s3.transform = scale(4, 4, 4);

	auto g = Group();
	g.addChild(&s1);
	g.addChild(&s2);
	g.addChild(&s3);


	g.divide(1);

	ASSERT_EQ(g.children.size(), 2);
	ASSERT_EQ(g.children[0], &s3);

	auto subgroup = (Group *)g.children[1];
	ASSERT_EQ(subgroup->children.size(), 2);

	auto sub0 = (Group*)subgroup->children[0];
	ASSERT_EQ(sub0->children.size(), 1);
	ASSERT_EQ(sub0->children[0], &s1);

	auto sub1 = (Group*)subgroup->children[1];
	ASSERT_EQ(sub1->children.size(), 1);
	ASSERT_EQ(sub1->children[0], &s2);
}

TEST(BoundingBox, SubdividingAGroupWithTooFewChildren) {
	auto s1 = Sphere();
	s1.transform = translate(-2, 0, 0);
	auto s2 = Sphere();
	s2.transform = translate(2, 1, 0);
	auto s3 = Sphere();
	s3.transform = translate(2, -1, 0);

	auto subGroup = new Group();
	subGroup->addChild(&s1);
	subGroup->addChild(&s2);
	subGroup->addChild(&s3);

	auto s4 = Sphere();

	auto g = Group();
	g.addChild(subGroup);
	g.addChild(&s4);

	g.divide(3);

	// TODO: write this in a less confusing way

	ASSERT_EQ(g.children.size(), 2);
	ASSERT_EQ(g.children[0], subGroup);
	ASSERT_EQ(g.children[1], &s4);

	ASSERT_EQ(subGroup->children.size(), 2);


	auto sub0 = (Group*)g.children[0];

	auto sub0sub0 = (Group*)sub0->children[0];
	auto sub0sub1 = (Group*)sub0->children[1];

	ASSERT_EQ(sub0sub0->children.size(), 1);
	ASSERT_EQ(sub0sub1->children.size(), 2);

	ASSERT_EQ(sub0sub0->children[0], &s1);

	ASSERT_EQ(sub0sub1->children[0], &s2);
	ASSERT_EQ(sub0sub1->children[1], &s3);

}

TEST(Triangle, ConstructingATriangle) {

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	ASSERT_EQ(t.p1, p1);
	ASSERT_EQ(t.p2, p2);
	ASSERT_EQ(t.p3, p3);

	ASSERT_EQ(t.e1, Tuple::vector(-1, -1, 0));
	ASSERT_EQ(t.e2, Tuple::vector(1, -1, 0));
	ASSERT_EQ(t.normal, Tuple::vector(0, 0, -1));
}

TEST(Triangle, NormalOnATriangle) {

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	auto n1 = t.objectNormal(Tuple::point(0, 0.5, 0));
	auto n2 = t.objectNormal(Tuple::point(-0.5, 0.75, 0));
	auto n3 = t.objectNormal(Tuple::point(0.5, 0.25, 0));


	ASSERT_EQ(n1, t.normal);
	ASSERT_EQ(n2, t.normal);
	ASSERT_EQ(n3, t.normal);
}

TEST(Triangle, IntersectingARayParallelToTriangle) {

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	auto r = Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 1, 0));

	auto xs = t.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(Triangle, RayMisssesP1P3Edge){

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	auto r = Ray(Tuple::point(1, 1, -2), Tuple::vector(0, 0, 1));

	auto xs = t.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(Triangle, RayMisssesP1P2Edge) {

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	auto r = Ray(Tuple::point(-1, 1, -2), Tuple::vector(0, 0, 1));

	auto xs = t.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(Triangle, RayMisssesP2P3Edge) {

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	auto r = Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 0, 1));

	auto xs = t.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(Triangle, RayStrikesTriangle) {

	Tuple p1 = Tuple::point(0, 1, 0);
	Tuple p2 = Tuple::point(-1, 0, 0);
	Tuple p3 = Tuple::point(1, 0, 0);

	Triangle t(p1, p2, p3);

	auto r = Ray(Tuple::point(0, 0.5, -2), Tuple::vector(0, 0, 1));

	auto xs = t.intersect(r);

	ASSERT_EQ(xs.intersections.size(), 1);

	for (auto inter : xs.intersections) {
		ASSERT_FLOAT_EQ(inter->t, 2);
	}
}


TEST(OBJPARSER, TMPTEST) {
	OBJParser o("Randomstring.obj");

	ASSERT_EQ(o.skippedLines, 5);
}

TEST(OBJPARSER, VertexRecords) {
	OBJParser o("VertexRecords1.obj");

	// book values, not the same because mine are normalized from (-1, -1, -1), (1, 1, 1)
	//Tuple ans[] = {Tuple::point(-1, 1, 0), Tuple::point(-1, 0.5, 0), Tuple::point(1, 0, 0), Tuple::point(1, 1, 0)};
	//TODO: check if the new values are normalized correctly
	Tuple ans[] = { Tuple::point(-1, 0.5, 0), Tuple::point(-1, 0, 0), Tuple::point(1, - 0.5, 0), Tuple::point(1, 0.5, 0) };
	int i = 0;

	for (auto x : o.vertices) {
		ASSERT_EQ(x, ans[i++]);
	}
}

TEST(OBJPARSER, TriangleFaces) {
	OBJParser o("TriangleFaces1.obj");

	//TODO: Test for group and children

	ASSERT_EQ(o.triangles[0]->p1, o.vertices[0]);
	ASSERT_EQ(o.triangles[0]->p2, o.vertices[1]);
	ASSERT_EQ(o.triangles[0]->p3, o.vertices[2]);

	ASSERT_EQ(o.triangles[1]->p1, o.vertices[0]);
	ASSERT_EQ(o.triangles[1]->p2, o.vertices[2]);
	ASSERT_EQ(o.triangles[1]->p3, o.vertices[3]);

	ASSERT_EQ(o.g.children.size(), 2);
}



TEST(OBJPARSER, TrianglePolygons) {
	OBJParser o("TriangulatingPoligons.obj");

	//TODO: Test for group and children

	ASSERT_EQ(((Triangle *)(o.g.children[0]))->p1, o.vertices[0]);
	ASSERT_EQ(((Triangle *)(o.g.children[0]))->p2, o.vertices[1]);
	ASSERT_EQ(((Triangle *)(o.g.children[0]))->p3, o.vertices[2]);

	ASSERT_EQ(((Triangle *)(o.g.children[1]))->p1, o.vertices[0]);
	ASSERT_EQ(((Triangle *)(o.g.children[1]))->p2, o.vertices[2]);
	ASSERT_EQ(((Triangle *)(o.g.children[1]))->p3, o.vertices[3]);

	ASSERT_EQ(((Triangle *)(o.g.children[2]))->p1, o.vertices[0]);
	ASSERT_EQ(((Triangle *)(o.g.children[2]))->p2, o.vertices[3]);
	ASSERT_EQ(((Triangle *)(o.g.children[2]))->p3, o.vertices[4]);
}

TEST(OBJPARSER, TrianglesInGroups) {

	OBJParser o("trianglesingroups.obj");

	//TODO: Test for group and children
	ASSERT_EQ(o.namedGroup["FirstGroup"]->children[0], o.triangles[0]);
	ASSERT_EQ(o.namedGroup["SecondGroup"]->children[0], o.triangles[1]);

	ASSERT_EQ(((Triangle *) o.namedGroup["FirstGroup"]->children[0])->p1, o.vertices[0]);
	ASSERT_EQ(((Triangle *) o.namedGroup["FirstGroup"]->children[0])->p2, o.vertices[1]);
	ASSERT_EQ(((Triangle *) o.namedGroup["FirstGroup"]->children[0])->p3, o.vertices[2]);

	ASSERT_EQ(((Triangle *) o.namedGroup["SecondGroup"]->children[0])->p1, o.vertices[0]);
	ASSERT_EQ(((Triangle *) o.namedGroup["SecondGroup"]->children[0])->p2, o.vertices[2]);
	ASSERT_EQ(((Triangle *) o.namedGroup["SecondGroup"]->children[0])->p3, o.vertices[3]);
}

TEST(OBJPARSER, ConstructingSmoothTriangle) {

	auto p1 = Tuple::point(0, 1, 0);
	auto p2 = Tuple::point(-1, 0, 0);
	auto p3 = Tuple::point(1, 0, 0);
	auto n1 = Tuple::point(0, 1, 0);
	auto n2 = Tuple::point(-1, 0, 0);
	auto n3 = Tuple::point(1, 0, 0);

	auto smooth = SmoothTriangle(p1, p2, p3, n1, n2, n3);

	ASSERT_EQ(smooth.p1, p1);
	ASSERT_EQ(smooth.p2, p2);
	ASSERT_EQ(smooth.p3, p3);
	ASSERT_EQ(smooth.n1, n1);
	ASSERT_EQ(smooth.n2, n2);
	ASSERT_EQ(smooth.n3, n3);
}

TEST(OBJPARSER, IntersectionEncapsulateUandV) {

	auto s = Triangle(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
	auto i = Intersection(3.5, &s, 0.2, 0.4);

	ASSERT_FLOAT_EQ(i.u, 0.2);
	ASSERT_FLOAT_EQ(i.v, 0.4);
}

TEST(OBJPARSER, IntersectioNWithSmoothTriangle) {

	auto p1 = Tuple::point(0, 1, 0);
	auto p2 = Tuple::point(-1, 0, 0);
	auto p3 = Tuple::point(1, 0, 0);
	auto n1 = Tuple::point(0, 1, 0);
	auto n2 = Tuple::point(-1, 0, 0);
	auto n3 = Tuple::point(1, 0, 0);

	auto smooth = SmoothTriangle(p1, p2, p3, n1, n2, n3);

	auto r = Ray(Tuple::point(-0.2, 0.3, -2), Tuple::vector(0, 0, 1));

	auto xs = smooth.intersect(r);


	for (auto x : xs.intersections) {
		ASSERT_FLOAT_EQ(x->u, 0.45);
		ASSERT_FLOAT_EQ(x->v, 0.25);
	}
}

// TODO: fix for floats
TEST(OBJPARSER, SmoothTriangleInterpolateTheNormal) {

	auto p1 = Tuple::point(0, 1, 0);
	auto p2 = Tuple::point(-1, 0, 0);
	auto p3 = Tuple::point(1, 0, 0);
	auto n1 = Tuple::point(0, 1, 0);
	auto n2 = Tuple::point(-1, 0, 0);
	auto n3 = Tuple::point(1, 0, 0);

	auto smooth = SmoothTriangle(p1, p2, p3, n1, n2, n3);

	auto r = Ray(Tuple::point(-0.2, 0.3, -2), Tuple::vector(0, 0, 1));

	auto xs = smooth.intersect(r);
	

	for (auto x : xs.intersections) {
		auto comps = Precomputations(*x, r, xs);
		ASSERT_EQ(comps.normalv, Tuple::vector(-0.5547, 0.83205, 0));
	}
}

TEST(OBJPARSER, VertexNormalRecords) {

	OBJParser o("vertexNormalRecords.obj");

	ASSERT_EQ(o.normals[0], Tuple::vector(0, 0, 1));
	ASSERT_EQ(o.normals[1], Tuple::vector(0.707, 0, -0.707));
	ASSERT_EQ(o.normals[2], Tuple::vector(1, 2, 3));
}

TEST(OBJPARSER, a) {

	OBJParser o("faceswithnormals.obj");

	ASSERT_EQ(o.smoothTriangles[0]->p1, o.vertices[0]);
	ASSERT_EQ(o.smoothTriangles[0]->p2, o.vertices[1]);
	ASSERT_EQ(o.smoothTriangles[0]->p3, o.vertices[2]);

	ASSERT_EQ(o.smoothTriangles[0]->n1, o.normals[2]);
	ASSERT_EQ(o.smoothTriangles[0]->n2, o.normals[0]);
	ASSERT_EQ(o.smoothTriangles[0]->n3, o.normals[1]);

	ASSERT_EQ(o.smoothTriangles[1]->p1, o.vertices[0]);
	ASSERT_EQ(o.smoothTriangles[1]->p2, o.vertices[1]);
	ASSERT_EQ(o.smoothTriangles[1]->p3, o.vertices[2]);

	ASSERT_EQ(o.smoothTriangles[1]->n1, o.normals[2]);
	ASSERT_EQ(o.smoothTriangles[1]->n2, o.normals[0]);
	ASSERT_EQ(o.smoothTriangles[1]->n3, o.normals[1]);

	ASSERT_EQ(o.g.children.size(), 2);
}

TEST(BoundingBox, TriangleBox) {

	auto shape = Triangle(Tuple::point(-3, 7, 2), Tuple::point(6, 2, -4), Tuple::point(2, -1, -1));

	auto box = shape.boundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(-3, -1, -4));
	ASSERT_EQ(box.boxMax, Tuple::point(6, 7, 2));
}

TEST(CSG, CSGConstruct) {

	auto s1 = Sphere();
	auto s2 = Cube();

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	ASSERT_EQ(CSGOperation::OPERATION::UNION, c.operation);
	ASSERT_EQ(c.left, &s1);
	ASSERT_EQ(c.right, &s2);

	ASSERT_EQ(s1.parent, &c);
	ASSERT_EQ(s2.parent, &c);
}

TEST(CSG, RuleForACSGOperationUnion) {

	auto s1 = Sphere();
	auto s2 = Cube();

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	bool lhit[] = { true, true, true, true, false, false, false, false };
	bool inl[] = { true, true, false, false, true, true, false, false };
	bool inr[] = { true, false, true, false, true, false, true, false };

	bool ans[] = {false, true, false, true, false, false, true, true};

	for (int i = 0; i < 8; ++i) {
		ASSERT_EQ(ans[i], c.intersectionAllowed(CSGOperation::OPERATION::UNION, lhit[i], inl[i], inr[i]));
	}
}

TEST(CSG, RuleForACSGOperationIntersection) {

	auto s1 = Sphere();
	auto s2 = Cube();

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	bool lhit[] = { true, true, true, true, false, false, false, false };
	bool inl[] = { true, true, false, false, true, true, false, false };
	bool inr[] = { true, false, true, false, true, false, true, false };

	bool ans[] = { true, false, true, false, true, true, false, false };

	for (int i = 0; i < 8; ++i) {
		ASSERT_EQ(ans[i], c.intersectionAllowed(CSGOperation::OPERATION::INTERSECTION, lhit[i], inl[i], inr[i]));

	}
}

TEST(CSG, RuleForACSGOperationDifference) {

	auto s1 = Sphere();
	auto s2 = Cube();

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	bool lhit[] = { true, true, true, true, false, false, false, false };
	bool inl[] = { true, true, false, false, true, true, false, false };
	bool inr[] = { true, false, true, false, true, false, true, false };

	bool ans[] = { false, true, false, true, true, true, false, false};

	for (int i = 0; i < 8; ++i) {
		ASSERT_EQ(ans[i], c.intersectionAllowed(CSGOperation::OPERATION::DIFFERENCE, lhit[i], inl[i], inr[i]));
	}
}

TEST(CSG, FilteringAListOfIntersections) {

	auto s1 = Sphere();
	auto s2 = Cube();

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	auto i1 = Intersection(1, &s1);
	auto i2 = Intersection(2, &s2);
	auto i3 = Intersection(3, &s1);
	auto i4 = Intersection(4, &s2);

	auto xs = Intersections();
	xs.intersections.insert(&i1);
	xs.intersections.insert(&i2);
	xs.intersections.insert(&i3);
	xs.intersections.insert(&i4);

	auto result = c.filterIntersections(xs);

	ASSERT_EQ(result.intersections.size(), 2);
	//TODO: check why the results are not the same as in the book
	int ans[] = { 1, 4 };

	int i = 0;

	for (auto res : result.intersections) {
		ASSERT_EQ(res->t, ans[i]);
		++i;
	}

	c.operation = CSGOperation::OPERATION::INTERSECTION;
		
	auto result1 = c.filterIntersections(xs);
	int ans1[] = {2, 3};
	
	i = 0;

	for (auto res : result1.intersections) {
		ASSERT_EQ(res->t, ans1[i]);
		++i;
	}
	

	c.operation = CSGOperation::OPERATION::DIFFERENCE;

	auto result2 = c.filterIntersections(xs);
	int ans2[] = { 1, 2 };

	i = 0;

	for (auto res : result2.intersections) {
		ASSERT_EQ(res->t, ans2[i]);
		++i;
	}

}

TEST(CSG, RayMissesCSGObject) {

	auto s1 = Sphere();
	auto s2 = Cube();

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	auto r = Ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));

	auto xs = c.intersect(r);
	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(CSG, RayHitsCSGObject) {

	auto s1 = Sphere();
	auto s2 = Sphere();
	s2.transform = translate(0, 0, 0.5);

	auto c = CSGShape(CSGOperation::OPERATION::UNION, &s1, &s2);

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto xs = c.intersect(r);
	ASSERT_EQ(xs.intersections.size(), 2);

	double points[] = { 4, 6.5 };
	Shape* shapes[] = { &s1, &s2 };

	int i = 0;

	for (auto intersection : xs.intersections) {
		ASSERT_EQ(intersection->t, points[i]);
		ASSERT_EQ(intersection->s, shapes[i]);
		i++;
	}
}

TEST(CSG, BoundsOfCSG) {

	auto left = Sphere();
	auto right = Sphere();
	
	right.transform = translate(2, 3, 4);

	auto shape = CSGShape(CSGOperation::OPERATION::DIFFERENCE, &left, &right);

	auto box = shape.boundsOf();

	ASSERT_EQ(box.boxMin, Tuple::point(-1, -1, -1));
	ASSERT_EQ(box.boxMax, Tuple::point(3, 4, 5));
}

//TODO: set ray as in the book, testshape
// hits too
TEST(CSG, RayMissesCSG) {

	auto left = Sphere();
	auto right = Sphere();

	auto shape = CSGShape(CSGOperation::OPERATION::DIFFERENCE, &left, &right);

	auto ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));
	auto xs = shape.intersect(ray);

	ASSERT_EQ(xs.intersections.size(), 0);
}

TEST(CSG, RayHitsCSG) {

	auto left = Sphere();
	auto right = Sphere();

	auto shape = CSGShape(CSGOperation::OPERATION::DIFFERENCE, &left, &right);

	auto ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto xs = shape.intersect(ray);

	ASSERT_EQ(xs.intersections.size(), 2);
}

TEST(CSG, SubdividingCSGSubdividesChildren) {

	auto s1 = Sphere();
	s1.transform = translate(-1.5, 0, 0);

	auto s2 = Sphere();
	s2.transform = translate(1.5, 0, 0);

	auto left = Group();
	left.addChild(&s1);
	left.addChild(&s2);

	auto s3 = Sphere();
	s3.transform = translate(0, 0, -1.5);

	auto s4 = Sphere();
	s4.transform = translate(0, 0, 1.5);

	auto right = Group();
	right.addChild(&s3);
	right.addChild(&s4);

	auto shape = CSGShape(CSGOperation::OPERATION::DIFFERENCE, &left, &right);

	shape.divide(1);

	ASSERT_EQ(((Group *)shape.left)->children.size(), 2);

	auto subGroup = (Group *)((Group*)shape.left)->children[0];
	ASSERT_EQ(subGroup->children[0], &s1);

	subGroup = (Group*)((Group*)shape.left)->children[1];
	ASSERT_EQ(subGroup->children[0], &s2);


	subGroup = (Group*)((Group*)shape.right)->children[0];
	ASSERT_EQ(subGroup->children[0], &s3);

	subGroup = (Group*)((Group*)shape.right)->children[1];
	ASSERT_EQ(subGroup->children[0], &s4);

}

TEST(AreaLight, isShadowForOcclusion) {
	auto w = defaultWorld();
	auto lightPosition = Tuple::point(-10, -10, -10);

	bool ans[] = { false, true, false, false };
	std::vector<Tuple> points{ Tuple::point(-10, -10, 10), Tuple::point(10, 10, 10) ,Tuple::point(-20, -20, -20),Tuple::point(-5, -5, -5) };

	int cnt = 0;

	for (auto point : points) {
		ASSERT_EQ(w.isShadowed(point, lightPosition), ans[cnt]);
		cnt++;
	}
}

TEST(AreaLight, PointLightIntensity) {
	auto w = defaultWorld();
	
	auto light = w.lights[0];

	std::vector<Tuple> points{

		Tuple::point(0, 1.0001, 0) ,
		Tuple::point(-1.0001, 0, 0),
		Tuple::point(0, 0, -1.0001),
		Tuple::point(0, 0, 1.0001) ,
		Tuple::point(1.0001, 0, 0) ,
		Tuple::point(0, -1.0001, 0),
		Tuple::point(0, 0, 0)
	};

	double arr[] = { 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };

	int cnt = 0;

	for (auto point : points) {
		ASSERT_FLOAT_EQ(light->intensityAt(point, w), arr[cnt++]);
	}
}

TEST(AreaLight, IntensityToAttenuateColor) {
	auto w = defaultWorld();
	w.lights.clear();

	w.lights.emplace_back(new PointLight(Color(1, 1, 1), Tuple::point(0, 0, -10)));

	auto shape = w.objects[0];
	shape->material.ambient = 0.1;
	shape->material.diffuse = 0.9;
	shape->material.specular = 0.;
	shape->material.color = Color(1, 1, 1);

	auto pt = Tuple::point(0, 0, -1);
	auto eyev = Tuple::vector(0, 0, -1);
	auto normalv = Tuple::vector(0, 0, -1);

	std::vector<double> intensity = { 1.0, 0.5, 0.0 };
	std::vector<Color> ans = { Color(1, 1, 1), Color(0.55, 0.55, 0.55), Color(0.1, 0.1, 0.1) };

	int i = 0;

	for (auto in : intensity) {
		ASSERT_EQ(w.lights[0]->lighting(shape->material, shape, pt, eyev, normalv, in), ans[i++]);
	}
}

TEST(AreaLight, CreatingAreaLight) {
	auto corner = Tuple::point(0, 0, 0);
	auto v1 = Tuple::vector(2, 0, 0);
	auto v2 = Tuple::vector(0, 0, 1);

	auto light = TestLight(corner, v1, 4, v2, 2, Color(1, 1, 1));

	ASSERT_EQ(light.corner, corner);
	ASSERT_EQ(light.uVec, Tuple::vector(0.5, 0, 0));
	ASSERT_EQ(light.uSteps, 4);
	ASSERT_EQ(light.vVec, Tuple::vector(0, 0, 0.5));
	ASSERT_EQ(light.vSteps, 2);
	ASSERT_EQ(light.samples, 8);
	ASSERT_EQ(light.position, Tuple::point(1, 0, 0.5));
}

TEST(AreaLight, SinglePointOnAreaLight) {
	auto corner = Tuple::point(0, 0, 0);
	auto v1 = Tuple::vector(2, 0, 0);
	auto v2 = Tuple::vector(0, 0, 1);

	auto light = TestLight(corner, v1, 4, v2, 2, Color(1, 1, 1));

	int u[] = { 0, 1, 0, 2, 3 };
	int v[] = { 0, 0, 1, 0, 1 };

	std::vector<Tuple> result{
		Tuple::point(0.25, 0, 0.25),
		Tuple::point(0.75, 0, 0.25),
		Tuple::point(0.25, 0, 0.75),
		Tuple::point(1.25, 0, 0.25),
		Tuple::point(1.75, 0, 0.75)
	};

	int i = 0;

	for (auto res : result) {
		ASSERT_EQ(light.pointOnLight(u[i], v[i]), res);

		++i;
	}
}

TEST(AreaLight, AreaLightIntensity) {
	auto w = defaultWorld();
	w.lights.clear();
	
	auto corner = Tuple::point(-0.5, -0.5, -5);
	auto v1 = Tuple::vector(1, 0, 0);
	auto v2 = Tuple::vector(0, 1, 0);

	auto light = TestLight(corner, v1, 2, v2, 2, Color(1, 1, 1));

	light.jitter = false;

	std::vector<Tuple> points{
	Tuple::point(0, 0, 2),
	Tuple::point(1, -1, 2),
	Tuple::point(1.5, 0, 2),
	Tuple::point(1.25, 1.25, 3),
	Tuple::point(0, 0, -2)
	};

	double result[] = { 0.0, 0.25, 0.5, 0.75, 1 };

	int i = 0;

	for (auto point : points) {
		ASSERT_EQ(light.intensityAt(point, w), result[i++]);
	}

}

TEST(AreaLight, NumberGEneratorCyclicSequence) {
	auto corner = Tuple::point(-0.5, -0.5, -5);
	auto v1 = Tuple::vector(1, 0, 0);
	auto v2 = Tuple::vector(0, 1, 0);

	auto light = TestLight(corner, v1, 2, v2, 2, Color(1, 1, 1));
	// TODO: why do i need to do this here but not in the test below
	light.cur = 0;

	light.seq = new std::vector<double>{ 0.1, 0.5, 1.0 };

	ASSERT_FLOAT_EQ(0.1, light.next());
	ASSERT_FLOAT_EQ(0.5, light.next());
	ASSERT_FLOAT_EQ(1.0, light.next());
	ASSERT_FLOAT_EQ(0.1, light.next());
}


TEST(AreaLight, SinglePointONaJitteredLight) {
	auto corner = Tuple::point(0, 0, 0);
	auto v1 = Tuple::vector(2, 0, 0);
	auto v2 = Tuple::vector(0, 0, 1);

	auto light = TestLight(corner, v1, 4, v2, 2, Color(1, 1, 1));
	light.seq = new std::vector<double>{ 0.3, 0.7 };
	light.jitter = true;
	
	int u[] = { 0, 1, 0, 2, 3 };
	int v[] = { 0, 0, 1, 0, 1 };

	std::vector<Tuple> ans{
		Tuple::point(0.15, 0, 0.35),
		Tuple::point(0.65, 0, 0.35),
		Tuple::point(0.15, 0, 0.85),
		Tuple::point(1.15, 0, 0.35),
		Tuple::point(1.65, 0, 0.85)
	};

	int i = 0;

	for (auto a : ans) {
		auto tmp = light.pointOnLight(u[i], v[i]);
		ASSERT_EQ(a, tmp);
		++i;
	}
}


TEST(AreaLight, LightingSamplesAreaLight) {
	
	auto corner = Tuple::point(-0.5, -0.5, -5);
	auto v1 = Tuple::vector(1, 0, 0);
	auto v2 = Tuple::vector(0, 1, 0);

	auto light = TestLight(corner, v1, 2, v2, 2, Color(1, 1, 1));

	auto shape = Sphere();
	shape.material.ambient = 0.1;
	shape.material.diffuse = 0.9;
	shape.material.specular = 0.;
	shape.material.color = Color(1, 1, 1);

	auto eye = Tuple::point(0, 0, -5);
	
	std::vector<Tuple> pt{ Tuple::point(0, 0, -1), Tuple::point(0, 0.7071, -0.7071) };

	//TODO: small difference to the book because of random?
	Color ans[] = { Color(0.996505, 0.996505, 0.996505), Color(0.623183, 0.623183, 0.623183) };

	int i = 0;

	for (auto p : pt) {
		auto eyev = (eye - p).normalize();
		auto normalv = Tuple::vector(p.x, p.y, p.z);

		auto result = light.lighting(shape.material, &shape, p, eyev, normalv, 1.0);

		ASSERT_EQ(result, ans[i++]);
	}
}

TEST(UVPatterns, CheckerPatternIn2D) {
	auto checkers = UVCheckers(2, 2, Color(0, 0, 0), Color(1, 1, 1));
	std::vector<std::pair<double, double>> points = { 
														{ 0.0, 0.0 }, { 0.5, 0.0 }, { 0.0, 0.5 },
														{ 0.5, 0.5 }, { 1.0, 1.0 }
													};

	std::vector<Color> ans = { Color(0, 0, 0), Color(1, 1, 1) , Color(1, 1, 1) , Color(0, 0, 0) , Color(0, 0, 0) };

	int i = 0;

	for (auto point : points) {
		ASSERT_EQ(checkers.uvPatternAt(point.first, point.second), ans[i]);
		++i;
	}
}

TEST(UVPatterns, SphericalMap) {
	std::vector<std::pair<double, double>> uv = {
													{ 0.0, 0.5 }, { 0.25, 0.5 }, { 0.5, 0.5 },
													{ 0.75, 0.5 }, { 0.5, 1.0 }, { 0.5, 0.0 }, { 0.25, 0.75 } 
												};

	std::vector<Tuple> points = {
									Tuple::point(0, 0, -1), Tuple::point(1, 0, 0), Tuple::point(0, 0, 1),
									Tuple::point(-1, 0, 0), Tuple::point(0, 1, 0), Tuple::point(0, -1, 0),
									Tuple::point(sqrt(2) / 2, sqrt(2) / 2, 0)
								};

	int i = 0;

	auto sphere = Sphere();

	for (auto point : points) {
		double u, v;
		sphere.UVmap(point, &u, &v);

		ASSERT_FLOAT_EQ(uv[i].first, u);
		ASSERT_FLOAT_EQ(uv[i].second, v);
		++i;
	}

}

TEST(UVPatterns, TextureMapAndSpherical) {
	auto checkers = UVCheckers(16, 8, Color(0, 0, 0), Color(1, 1, 1));



	std::vector<Tuple> points = {
									Tuple::point(0.4315, 0.4670, 0.7719) ,
									Tuple::point(-0.9654, 0.2552, -0.0534),
									Tuple::point(0.1039, 0.7090, 0.6975),
									Tuple::point(-0.4986, -0.7856, -0.3663),
									Tuple::point(-0.0317, -0.9395, 0.3411),
									Tuple::point(0.4809, -0.7721, 0.4154),
									Tuple::point(0.0285, -0.9612, -0.2745),
									Tuple::point(-0.5734, -0.2162, -0.7903),
									Tuple::point(0.7688, -0.1470, 0.6223),
									Tuple::point(-0.7652, 0.2175, 0.6060)
	};

	Color ans[] = {
						Color(1, 1, 1), Color(0, 0, 0),  Color(1, 1, 1),
						Color(0, 0, 0), Color(0, 0, 0), Color(0, 0, 0),
						Color(0, 0, 0),Color(1, 1, 1), Color(0, 0, 0),
						Color(0, 0, 0)
				  };

	int i = 0;
	auto sphere = Sphere();

	for (auto point : points) {
		ASSERT_EQ(checkers.patternColorAt(point, &sphere), ans[i]);
		++i;
	}
}

TEST(UVPatterns, PlanarMapping) {
	std::vector<std::pair<double, double>> ans = {
														{ 0.25, 0.5 }, { 0.25, 0.75 }, { 0.25, 0.75 },
														{ 0.25, 0.5 }, { 0.25, 0.25 }, { 0., 0. }, { 0., 0. }
													};

	std::vector<Tuple> points = {
									 Tuple::point(0.25, 0, 0.5),	
									 Tuple::point(0.25, 0, -0.25),	
									 Tuple::point(0.25, 0.5, -0.25),	
									 Tuple::point(1.25, 0, 0.5),	
									 Tuple::point(0.25, 0, -1.75),	
									 Tuple::point(1, 0, -1),	
									 Tuple::point(0, 0, 0)
								};

	auto plane = Plane();
	int i = 0;

	for (auto point : points) {
		double u, v;
		plane.UVmap(point, &u, &v);

		ASSERT_EQ(u, ans[i].first);
		ASSERT_EQ(v, ans[i].second);

		++i;
	}
}

TEST(UVPatterns, CylindricalMapping) {
	std::vector<std::pair<double, double>> ans = {
													{ 0., 0. }, { 0., 0.5 }, { 0., 0. },
													{ 0.125, 0.5  }, { 0.25, 0.5 }, { 0.375, 0.5 }, 
													{ 0.5, 0.75 }, { 0.625, 0.5 }, { 0.75, 0.25 },
													{ 0.875, 0.5 },
												 };

	std::vector<Tuple> points = {
									Tuple::point(0, 0, -1),
									Tuple::point(0, 0.5, -1),
									Tuple::point(0, 1, -1),
									Tuple::point(0.70711, 0.5, -0.70711),
									Tuple::point(1, 0.5, 0),
									Tuple::point(0.70711, 0.5, 0.70711),
									Tuple::point(0, -0.25, 1),
									Tuple::point(-0.70711, 0.5, 0.70711),
									Tuple::point(-1, 1.25, 0),
									Tuple::point(-0.70711, 0.5, -0.70711)
								};

	auto cylinder = Cylinder();
	int i = 0;

	for (auto point : points) {
		double u, v;
		cylinder.UVmap(point, &u, &v);

		ASSERT_EQ(u, ans[i].first);
		ASSERT_EQ(v, ans[i].second);

		++i;
	}
}

TEST(UVPatterns, FaceFromPoint) {
	auto cube = Cube();

	std::vector<Tuple> points = {
		Tuple::point(-1, 0.5, -0.25),
		Tuple::point(1.1, -0.75, 0.8),
		Tuple::point(0.1, 0.6, 0.9),
		Tuple::point(-0.7, 0, -2),
		Tuple::point(0.5, 1, 0.9),
		Tuple::point(-0.2, -1.3, 1.1)
	};

	cubeFace::FACE ans[] = { cubeFace::LEFT, cubeFace::RIGHT, cubeFace::FRONT, cubeFace::BACK, cubeFace::UP, cubeFace::DOWN };

	int i = 0;

	for (auto point : points) {
		ASSERT_EQ(cube.faceFromPoint(point), ans[i++]);
	}
}

TEST(UVPatterns, UVMapFacesFront) {
	auto cube = Cube();

	std::vector<Tuple> points = {
		Tuple::point(-0.5, 0.5, 1),
		Tuple::point(0.5, -0.5, 1),
	};


	std::vector<std::pair<double, double>> ans = {{ 0.25, 0.75 }, { 0.75, 0.25 }};

	int i = 0;

	for (auto point : points) {
		double u, v;

		cube.cubeUVFront(point, &u, &v);
		ASSERT_FLOAT_EQ(ans[i].first, u);
		ASSERT_FLOAT_EQ(ans[i].second, v);
		i++;
	}
}

TEST(UVPatterns, UVMapFacesBack) {
	auto cube = Cube();

	std::vector<Tuple> points = {
		
		Tuple::point(0.5, 0.5, -1),
		Tuple::point(-0.5, -0.5, -1)
	};

	std::vector<std::pair<double, double>> ans = { {0.25, 0.75}, {0.75, 0.25} };

	int i = 0;

	for (auto point : points) {
		double u, v;

		cube.cubeUVBack(point, &u, &v);
		ASSERT_FLOAT_EQ(ans[i].first, u);
		ASSERT_FLOAT_EQ(ans[i].second, v);
		i++;
	}
}

TEST(UVPatterns, UVMapFacesLeft) {
	auto cube = Cube();

	std::vector<Tuple> points = {

		Tuple::point(-1, 0.5, -0.5),
		Tuple::point(-1, -0.5, 0.5),
	};


	std::vector<std::pair<double, double>> ans = { {0.25, 0.75}, {0.75, 0.25} };

	int i = 0;

	for (auto point : points) {
		double u, v;

		cube.cubeUVLeft(point, &u, &v);
		ASSERT_FLOAT_EQ(ans[i].first, u);
		ASSERT_FLOAT_EQ(ans[i].second, v);
		i++;
	}
}


TEST(UVPatterns, UVMapFacesRight) {
	auto cube = Cube();

	std::vector<Tuple> points = {

		Tuple::point(1, 0.5, 0.5),
		Tuple::point(1, -0.5, -0.5),
	};


	std::vector<std::pair<double, double>> ans = { {0.25, 0.75}, {0.75, 0.25} };

	int i = 0;

	for (auto point : points) {
		double u, v;

		cube.cubeUVRight(point, &u, &v);
		ASSERT_FLOAT_EQ(ans[i].first, u);
		ASSERT_FLOAT_EQ(ans[i].second, v);
		i++;
	}
}

TEST(UVPatterns, UVMapFacesUP) {
	auto cube = Cube();

	std::vector<Tuple> points = {
		Tuple::point(-0.5, 1, -0.5),
		Tuple::point(0.5, 1, 0.5)
	};


	std::vector<std::pair<double, double>> ans = { {0.25, 0.75}, {0.75, 0.25} };

	int i = 0;

	for (auto point : points) {
		double u, v;

		cube.cubeUVUp(point, &u, &v);
		ASSERT_FLOAT_EQ(ans[i].first, u);
		ASSERT_FLOAT_EQ(ans[i].second, v);
		i++;
	}
}

TEST(UVPatterns, UVMapFacesDown) {
	auto cube = Cube();

	std::vector<Tuple> points = {
		Tuple::point(-0.5, -1, 0.5),
		Tuple::point(0.5, -1, -0.5)
		
	};


	std::vector<std::pair<double, double>> ans = { {0.25, 0.75}, {0.75, 0.25} };

	int i = 0;

	for (auto point : points) {
		double u, v;

		cube.cubeUVDown(point, &u, &v);
		ASSERT_FLOAT_EQ(ans[i].first, u);
		ASSERT_FLOAT_EQ(ans[i].second, v);
		i++;
	}
}

TEST(UVPatterns, FindingColorsOnMappedCube) {
	Color red    = Color(1, 0, 0);
	Color yellow = Color(1, 1, 0);
	Color brown  = Color(1, 0.5, 0);
	Color green  = Color(0, 1, 0);
	Color cyan   = Color(0, 1, 1);
	Color blue   = Color(0, 0, 1);
	Color purple = Color(1, 0, 1);
	Color white  = Color(1, 1, 1);

	auto left    = AlignCheck(yellow, cyan, red, blue, brown);
	auto front   = AlignCheck(cyan, red, yellow, brown, green);
	auto right   = AlignCheck(red, yellow, purple, green, white);
	auto back    = AlignCheck(green, purple, cyan, white, blue);
	auto up      = AlignCheck(brown, cyan, purple, red, yellow);
	auto down    = AlignCheck(purple, brown, green, blue, white);

	auto pattern = CubeMap(&front, &back, &left, &right, &up, &down);
	auto cube = Cube();
	cube.material.pattern = &pattern;



	std::vector<Tuple> LPoints = {
									Tuple::point(-1, 0, 0), Tuple::point(-1, 0.9, -0.9), Tuple::point(-1, 0.9, 0.9),
									Tuple::point(-1, -0.9, -0.9), Tuple::point(-1, -0.9, 0.9)
								 };


	std::vector<Color> LAns = { yellow, cyan, red, blue, brown };
	int i = 0;

	for (auto point : LPoints) {
		// we can simply call cube.stripeAtObject(point), but i will leave it to follow the example
		ASSERT_EQ(pattern.patternColorAt(point, &cube), LAns[i++]);
	}

	std::vector<Tuple> FPoints = {
								Tuple::point(0, 0, 1), Tuple::point(-0.9, 0.9, 1), Tuple::point(0.9, 0.9, 1),
								Tuple::point(-0.9, -0.9, 1), Tuple::point(0.9, -0.9, 1)
	};

	std::vector<Color> FAns = { cyan, red, yellow, brown, green };
	i = 0;

	for (auto point : FPoints) {
		// we can simply call cube.stripeAtObject(point), but i will leave it to follow the example
		ASSERT_EQ(pattern.patternColorAt(point, &cube), FAns[i++]);
	}

	std::vector<Tuple> RPoints = {
							Tuple::point(1, 0, 0), Tuple::point(1, 0.9, 0.9), Tuple::point(1, 0.9, -0.9),
							Tuple::point(1, -0.9, 0.9), Tuple::point(1, -0.9, -0.9)
	};

	std::vector<Color> RAns = { red, yellow, purple, green, white };
	i = 0;

	for (auto point : RPoints) {
		// we can simply call cube.stripeAtObject(point), but i will leave it to follow the example
		ASSERT_EQ(pattern.patternColorAt(point, &cube), RAns[i++]);
	}

	std::vector<Tuple> BPoints = {
						Tuple::point(0, 0, -1), Tuple::point(0.9, 0.9, -1), Tuple::point(-0.9, 0.9, -1),
						Tuple::point(0.9, -0.9, -1), Tuple::point(-0.9, -0.9, -1)
	};

	std::vector<Color> BAns = { green, purple, cyan, white, blue };
	i = 0;

	for (auto point : BPoints) {
		// we can simply call cube.stripeAtObject(point), but i will leave it to follow the example
		ASSERT_EQ(pattern.patternColorAt(point, &cube), BAns[i++]);
	}


	std::vector<Tuple> UPoints = {
						Tuple::point(0, 1, 0), Tuple::point(-0.9, 1, -0.9), Tuple::point(0.9, 1, -0.9),
						Tuple::point(-0.9, 1, 0.9), Tuple::point(0.9, 1, 0.9)
	};

	std::vector<Color> UAns = { brown, cyan, purple, red, yellow };
	i = 0;

	for (auto point : UPoints) {
		// we can simply call cube.stripeAtObject(point), but i will leave it to follow the example
		ASSERT_EQ(pattern.patternColorAt(point, &cube), UAns[i++]);
	}

	std::vector<Tuple> DPoints = {
					Tuple::point(0, -1, 0), Tuple::point(-0.9, -1, 0.9), Tuple::point(0.9, -1, 0.9),
					Tuple::point(-0.9, -1, -0.9), Tuple::point(0.9, -1, -0.9)
	};

	std::vector<Color> DAns = { purple, brown, green, blue, white };
	i = 0;

	for (auto point : DPoints) {
		// we can simply call cube.stripeAtObject(point), but i will leave it to follow the example
		ASSERT_EQ(pattern.patternColorAt(point, &cube), DAns[i++]);
	}

}

TEST(PPMParsing, WrongMagicNumber) {
	auto canvas = canvasFromPPM("WrongMagicNumber.ppm");
}

TEST(PPMParsing, PPMDimensions) {
	auto canvas = canvasFromPPM("PPMDimensions.ppm");

	ASSERT_EQ(canvas.w, 10);
	ASSERT_EQ(canvas.h, 2);
}

TEST(PPMParsing, PPMPixelData) {
	auto canvas = canvasFromPPM("PixelData.ppm");
	std::vector<Color> ans = {
		Color(1, 0.498039, 0),
		Color(0, 0.498039, 1),
		Color(0.498039, 1, 0),
		Color(1, 1, 1),
		Color(0, 0, 0),
		Color(1, 0, 0),
		Color(0, 1, 0),
		Color(0, 0, 1),
		Color(1, 1, 0),
		Color(0, 1, 1),
		Color(1, 0, 1),
		Color(0.498039, 0.498039, 0.498039)
	};

	for (int x = 0; x < canvas.h * canvas.w; ++x) {
			ASSERT_EQ(canvas.canvas[x], ans[x]);
	}
}

TEST(PPMParsing, IgnoringCommentsInPPM) {
	auto canvas = canvasFromPPM("IgnoringComments.ppm");
	std::vector<Color> ans = {
		Color(1, 1, 1),
		Color(1, 0, 1)
	};

	ASSERT_EQ(canvas.canvas[0], ans[0]);
	ASSERT_EQ(canvas.canvas[1], ans[1]);
}

TEST(PPMParsing, PPMRGBSpanningLines) {
	auto canvas = canvasFromPPM("PPMRGBSpansLines.ppm");
	std::vector<Color> ans = {
		Color(0.2, 0.6, 0.8),
	};

	ASSERT_EQ(canvas.canvas[0], ans[0]);
}

TEST(PPMParsing, PPMRespectScale) {
	auto canvas = canvasFromPPM("RespectScale.ppm");
	std::vector<Color> ans = {
		Color(0.75, 0.5, 0.25),
	};
	// The test is wrong i think should be (1, 0)
	ASSERT_EQ(canvas.canvas[2], ans[0]);
}

TEST(PPMParsing, CheckerPatternIn2d) {
	auto canvas = canvasFromPPM("CheckerPatternIn2d.ppm");
	std::vector<Color> ans = {
		 Color(0.9, 0.9, 0.9),
		 Color(0.2, 0.2, 0.2),
		 Color(0.1, 0.1, 0.1),
		 Color(0.9, 0.9, 0.9)
	};

	auto pattern = UVImagePattern(&canvas);

	auto sphere = Sphere();

	auto c = pattern.uvPatternAt(0, 0);
	ASSERT_EQ(c, ans[0]);

	c = pattern.uvPatternAt(0.3, 0);
	ASSERT_EQ(c, ans[1]);

	c = pattern.uvPatternAt(0.6, 0.3);
	ASSERT_EQ(c, ans[2]);

	c = pattern.uvPatternAt(1, 1);
	ASSERT_EQ(c, ans[3]);
}
