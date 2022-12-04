#include "pch.h"
#include "../RayTracerChallenge/Tuple.h"
#include "../RayTracerChallenge/Tuple.cpp"

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


# define TEST_PI           3.14159265358979323846  /* pi */


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
	float a = 3.5;

	ASSERT_TRUE(t1 * a == Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, TupleDividedWihtScalar) {
	Tuple t1 = Tuple(1, -2, 3, -4);
	float a = 3.5;

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

TEST(ColorTest, Addition){
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

	ASSERT_FLOAT_EQ(mino.minor(1 ,0), 25);
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
	ASSERT_TRUE(invertible1.invertible() ==  1);
	

	Matrix invertible2(4, 4);
	invertible2.matrix[0 * invertible2.w + 0] =  -4;
	invertible2.matrix[0 * invertible2.w + 1] = 2;
	invertible2.matrix[0 * invertible2.w + 2] =  -2;
	invertible2.matrix[0 * invertible2.w + 3] =  -3;
	invertible2.matrix[1 * invertible2.w + 0] =  9;
	invertible2.matrix[1 * invertible2.w + 1] =  6;
	invertible2.matrix[1 * invertible2.w + 2] =  2;
	invertible2.matrix[1 * invertible2.w + 3] =  6;
	invertible2.matrix[2 * invertible2.w + 0] =  0;
	invertible2.matrix[2 * invertible2.w + 1] =  -5;
	invertible2.matrix[2 * invertible2.w + 2] =  1;
	invertible2.matrix[2 * invertible2.w + 3] =  -5;
	invertible2.matrix[3 * invertible2.w + 0] =  0;
	invertible2.matrix[3 * invertible2.w + 1] =  0;
	invertible2.matrix[3 * invertible2.w + 2] =  0;
	invertible2.matrix[3 * invertible2.w + 3] =  0;

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

	ASSERT_EQ(inverse1.inverse(), cmp1);


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

	ASSERT_EQ(inverse2.inverse(), cmp2);

	
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

	ASSERT_EQ(inverse3.inverse(), cmp3);
	
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
	mat3 = mat3 * mat2.inverse();

	ASSERT_EQ(mat3, mat1);
}


TEST(TransformationTest, Translation) {
	Tuple p = Tuple::point(-3, 4, 5);
	Matrix t = translate(5, -3, 2);

	ASSERT_EQ(t * p, Tuple::point(2, 1, 7));
}

TEST(TransformationTest, MulInverseOfTranslation) {
	
	Matrix t = translate(5, -3, 2);
	Matrix inv = t.inverse();
	Tuple p = Tuple::point(-3,4, 5);

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
	Matrix inv = t.inverse();

	ASSERT_EQ(inv * v, Tuple::vector(-2, 2, 2));
}

TEST(TransformationTest, Reflection) {

	Matrix t = scale(-1, 1, 1);
	Tuple p = Tuple::point(2, 3, 4);
	ASSERT_EQ(t * p, Tuple::point(-2, 3, 4));
}

TEST(TransformationTest, RotatonX) {

	Tuple p = Tuple::point(0, 1, 0);
	Matrix halfQuarter = rotationX(TEST_PI / 4);
	Matrix fullQuarter = rotationX(TEST_PI / 2);

	ASSERT_EQ(halfQuarter * p,  Tuple::point(0, sqrt(2)/2, sqrt(2) / 2));
	ASSERT_EQ(fullQuarter * p, Tuple::point(0, 0, 1));
}

TEST(TransformationTest, RotatonY) {

	Tuple p = Tuple::point(0, 0, 1);
	Matrix halfQuarter = rotationY(TEST_PI / 4);
	Matrix fullQuarter = rotationY(TEST_PI / 2);

	ASSERT_EQ(halfQuarter * p, Tuple::point(sqrt(2) / 2, 0 , sqrt(2) / 2));
	ASSERT_EQ(fullQuarter * p, Tuple::point(1, 0, 0));
}

TEST(TransformationTest, RotatonZ) {

	Tuple p = Tuple::point(0, 1, 0);
	Matrix halfQuarter = rotationZ(TEST_PI / 4);
	Matrix fullQuarter = rotationZ(TEST_PI / 2);

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
	Matrix A = rotationX(TEST_PI / 2);
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
	Matrix A = rotationX(TEST_PI / 2);
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

	auto intersect = intersection(r, &s);

	ASSERT_EQ(intersect.size(), 2);

	ASSERT_FLOAT_EQ(intersect[0].t, 4.f);
	ASSERT_FLOAT_EQ(intersect[1].t, 6.f);

}
TEST(INTERSECTION, Tangent) {

	Ray r(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
	Sphere s;


	auto intersect = intersection(r, &s);

	ASSERT_EQ(intersect.size(), 2);

	ASSERT_FLOAT_EQ(intersect[0].t, 5.f);
	ASSERT_FLOAT_EQ(intersect[1].t, 5.f);

}

TEST(INTERSECTION, Miss) {

	Ray r(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
	Sphere s;

	auto intersect = intersection(r, &s);

	ASSERT_EQ(intersect.size(), 0);
}

TEST(INTERSECTION, RayInsideSphere) {

	Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
	Sphere s;

	auto intersect = intersection(r, &s);

	ASSERT_EQ(intersect.size(), 2);

	ASSERT_FLOAT_EQ(intersect[0].t, -1.f);
	ASSERT_FLOAT_EQ(intersect[1].t, 1.f);

}

TEST(INTERSECTION, SphereBehindRay) {

	Ray r(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
	Sphere s;

	auto intersect = intersection(r, &s);

	ASSERT_EQ(intersect.size(), 2);
	ASSERT_FLOAT_EQ(intersect[0].t, -6.f);
	ASSERT_FLOAT_EQ(intersect[1].t, -4.f);

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

	intersections.insert(&x);
	intersections.insert(&x1);

	ASSERT_EQ(intersections.size(), 2);

	ASSERT_TRUE(intersections.count(&x), 1);
	ASSERT_TRUE(intersections.count(&x1), 1);

}

TEST(TrackingIntersections, ObjectOnTheIntersection) {

	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
	auto s = Sphere();

	auto intersect = intersection(r, &s);

	ASSERT_EQ(intersect.size(), 2);
	ASSERT_EQ(intersect[0].s, &s);
	ASSERT_EQ(intersect[1].s, &s);

}

TEST(HitTest, PositiveT) {

	auto s = Sphere();

	auto i1 = Intersection(1.f, &s);
	auto i2 = Intersection(2.f, &s);

	// TODO: needs to be cleared because of previous tests
	// not sure if this is intended behaviour
	intersections.clear();

	intersections.insert(&i1);
	intersections.insert(&i2);

	auto i = Intersection::hit();

	ASSERT_EQ(i, &i1);

}


TEST(HitTest, NegativeT) {

	auto s = Sphere();

	// TODO: make Intersections non static?
	intersections.clear();

	auto i1 = Intersection(-1.f, &s);
	auto i2 = Intersection(1.f, &s);

	intersections.insert(&i1);
	intersections.insert(&i2);

	auto i = Intersection::hit();

	ASSERT_EQ(i, &i2);

}

TEST(HitTest, LowestNonNegative) {

	auto s = Sphere();

	// TODO: make Intersections non static?
	intersections.clear();

	auto i1 = Intersection(5.f, &s);
	auto i2 = Intersection(7.f, &s);
	auto i3 = Intersection(-3.f, &s);
	auto i4 = Intersection(2.f, &s);

	intersections.insert(&i1);
	intersections.insert(&i2);
	intersections.insert(&i3);
	intersections.insert(&i4);

	auto i = Intersection::hit();

	ASSERT_EQ(i, &i4);
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

	auto xs = intersection(r, &s);

	ASSERT_EQ(xs.size(), 2);
	ASSERT_EQ(xs[0].t, 3);
	ASSERT_EQ(xs[1].t, 7);
}

TEST(RayTest, TranslatedSphereAndRay) {
	auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

	auto s = Sphere();
	s.transform = translate(5, 0, 0);

	auto xs = intersection(r, &s);

	ASSERT_EQ(xs.size(), 0);
}