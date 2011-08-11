#include <math.h>

#include "XnMath.hpp"


using namespace xn;


Point2Df	math::PointsCenter(Point2Df a, Point2Df b)
{
  Point2Df	center;

  center.X = (a.X + b.X) / 2;
  center.Y = (a.Y + b.Y) / 2;

  return center;
}

Point3Df	math::PointsCenter(Point3Df a, Point3Df b)
{
  Point3Df	center;

  center.X = (a.X + b.X) / 2;
  center.Y = (a.Y + b.Y) / 2;
  center.Z = (a.Z + b.Z) / 2;

  return center;
}

bool		math::Equal(Point2Df a, Point2Df b)
{
  return a.X == b.X && a.Y == b.Y;
}

bool		math::Equal(Point3Df a, Point3Df b)
{
  return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}

Vector2Df	math::PointsVector(Point2Df a, Point2Df b)
{
  Vector3Df	v;

  v.X = b.X - a.X;
  v.Y = b.Y - a.Y;

  return v;
}

Vector3Df	math::PointsVector(Point3Df a, Point3Df b)
{
  Vector3Df	v;

  v.X = b.X - a.X;
  v.Y = b.Y - a.Y;
  v.Z = b.Z - a.Z;

  return v;
}


float		math::PointsDistance(Point2Df a, Point2Df b)
{
  float		x = a.X - b.X;
  float		y = a.Y - b.Y;

  return sqrtf(x * x + y * y);
}

float		math::PointsDistance(Point3Df a, Point3Df b)
{
  float		x = a.X - b.X;
  float		y = a.Y - b.Y;
  float		z = a.Z - b.Z;

  return sqrtf(x * x + y * y + z * z);	  
}

float		math::VectorsDotProduct(Vector2Df a, Vector2Df b)
{
  return a.X * b.X +  a.Y * b.Y;
}

float		math::VectorsDotProduct(Vector3Df a, Vector3Df b)
{
  return a.X * b.X +  a.Y * b.Y + a.Z * b.Z;  
}

Vector3Df	math::VectorsCrossProduct(Vector3Df a, Vector3Df b)
{
  Vector3Df	crossProduct;

  crossProduct.X = a.Y * b.Z - a.Z * b.Y;
  crossProduct.Y = a.Z * b.X - a.X * b.Z;
  crossProduct.Z = a.X * b.Y - a.Y * b.X;

  return crossProduct;
}

float		math::VectorMagnitude(Vector2Df v)
{
  return sqrtf(v.X * v.X + v.Y * v.Y);
}

float		math::VectorMagnitude(Vector3Df v)
{
  return sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

float		math::VectorsAngle(Vector2Df a, Vector2Df b)
{
  // Formula is: a.b = |a||b| * cos(angle)
  
  float		dotProduct = VectorsDotProduct(a, b);
  float		aMagnitude = VectorMagnitude(a);
  float		bMagnitude = VectorMagnitude(b);
  float		angle = (dotProduct / (aMagnitude * bMagnitude));

  // cos -1 gives the angle in radians, we convert it into degrees
  return acosf(angle) * (180 / (float) M_PI);
}

float		math::VectorsAngle(Vector3Df a, Vector3Df b)
{
  // Formula is: a.b = |a||b| * cos(angle)
  
  float		dotProduct = VectorsDotProduct(a, b);
  float		aMagnitude = VectorMagnitude(a);
  float		bMagnitude = VectorMagnitude(b);
  float		angle = (dotProduct / (aMagnitude * bMagnitude));

  // cos -1 gives the angle in radians, we convert it into degrees
  return acosf(angle) * (180 / (float) M_PI);
}
