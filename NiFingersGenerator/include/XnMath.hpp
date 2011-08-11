#ifndef _XN_MATH_HPP_
#define _XN_MATH_HPP_

#include <XnTypes.h>

#include <list>

#include "XnFingerTypes.hpp"

#ifndef M_PI
#define M_PI 3.1415926
#endif

using namespace std;


namespace xn
{
  namespace math
  {
    Point2Df		PointsCenter(Point2Df a, Point2Df b);
    Point3Df		PointsCenter(Point3Df a, Point3Df b);

    bool		Equal(Point2Df a, Point2Df b);
    bool		Equal(Point3Df a, Point3Df b);

    Vector2Df		PointsVector(Point2Df a, Point2Df b);
    Vector3Df		PointsVector(Point3Df a, Point3Df b);

    float		PointsDistance(Point2Df a, Point2Df b);
    float		PointsDistance(Point3Df a, Point3Df b);

    float		VectorsDotProduct(Vector2Df a, Vector2Df b);
    float		VectorsDotProduct(Vector3Df a, Vector3Df b);

    Vector3Df		VectorsCrossProduct(Vector3Df a, Vector3Df b);

    float		VectorMagnitude(Vector2Df v);
    float		VectorMagnitude(Vector3Df v);

    float		VectorsAngle(Vector2Df a, Vector2Df b);
    float		VectorsAngle(Vector3Df a, Vector3Df b);
  }
}

// Here are the math functions which are templated, and therefore, need
// To be in a header file, since the project compiles a shared library.
#include "XnMathTemplates.hpp"

#endif //_XN_MATH_HPP_
