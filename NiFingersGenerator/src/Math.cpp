#include <math.h>

#include "XnMath.hpp"


using namespace xn;


XnVector3D	Math::PointsVector(XnPoint3D a, XnPoint3D b)
{
  XnVector3D	v;

  v.X = b.X - a.X;
  v.Y = b.Y - a.Y;
  v.Z = b.Z - a.Z;

  return v;
}

float		Math::PointsDistance(XnVector3D a, XnVector3D b)
{
  float		x = a.X - b.X;
  float		y = a.Y - b.Y;

  return sqrtf(x * x + y * y);	  
}

float		Math::VectorsDotProduct(XnVector3D a, XnVector3D b)
{
  return a.X * b.X +  a.Y * b.Y + a.Z * b.Z;  
}

XnVector3D	Math::VectorsCrossProduct(XnVector3D a, XnVector3D b)
{
  XnVector3D	crossProduct;

  crossProduct.X = a.Y * b.Z - a.Z * b.Y;
  crossProduct.Y = a.Z * b.X - a.X * b.Z;
  crossProduct.Z = a.X * b.Y - a.Y * b.X;

  return crossProduct;
}

float		Math::VectorMagnitude(XnVector3D v)
{
  return sqrtf(v.X * v.X + v.Y * v.Y);
}

float		Math::VectorsAngle(XnVector3D a, XnVector3D b)
{
  // Formula is: a.b = |a||b| * cos(angle)
  
  float		dotProduct = VectorsDotProduct(a, b);
  float		aMagnitude = VectorMagnitude(a);
  float		bMagnitude = VectorMagnitude(b);
  float		angle = (dotProduct / (aMagnitude * bMagnitude));

  // cos -1 gives the angle in radians, we convert it into degrees
  return acos(angle) * (180 / PI);
}
