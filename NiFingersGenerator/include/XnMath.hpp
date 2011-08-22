#ifndef _XN_MATH_HPP_
#define _XN_MATH_HPP_


#include "XnFingerTypes.hpp"


// M_PI is not always defined under Windows. M_PI represent the pi value (~ 3.14).
#ifndef M_PI
#define M_PI 3.1415926
#endif

// Degrees <-> Radians conversion macros.
#define RADIAN_TO_DEGREES(x) (x * (180 / (float) M_PI))
#define DEGREES_TO_RADIAN(x) (x * ((float) M_PI / 180))


using namespace std;

//
// xn::math:: is a namespace containing a set of function related to generic math
// operations. The functions are declared here. 
//
// See XnFingersTypes.hpp for the specific structues used here.
//

namespace xn
{
  namespace math
  {
    /**
     * Find the center of two 2D points.
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return A point at the center of a and b.
     */
    Point2Df		PointsCenter(Point2Df a, Point2Df b);

    /**
     * Find the center of two 3D points.
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return A point at the center of a and b.
     */
    Point3Df		PointsCenter(Point3Df a, Point3Df b);

    /**
     * Check wheter or not two 2D points are equals (means have identical coordinates).
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return true if a and b are equals, false otherwise.
     */
    bool		Equal(Point2Df a, Point2Df b);

    /**
     * Check wheter or not two 3D points are equals (means have identical coordinates).
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return true if a and b are equals, false otherwise.
     */
    bool		Equal(Point3Df a, Point3Df b);

    /**
     * Creates a 2D vector from point a to point b.
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return A 2D vector from a to b.
     */
    Vector2Df		PointsVector(Point2Df a, Point2Df b);

    /**
     * Creates a 3D vector from point a to point b.
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return A 3D vector from a to b.
     */
    Vector3Df		PointsVector(Point3Df a, Point3Df b);

    /**
     * Computes the distance of two 2D points.
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return The distance between a and b.
     */
    float		PointsDistance(Point2Df a, Point2Df b);

    /**
     * Computes the distance of two 3D points.
     *
     * @param a		A point.
     * @param b		Another point.
     *
     * @return The distance between a and b.
     */
    float		PointsDistance(Point3Df a, Point3Df b);

    /**
     * Computes the dot product of two 2D vectors.
     *
     * @param a		A vector.
     * @param b		Another vector.
     *
     * @return The dot product of a and b.
     */
    float		VectorsDotProduct(Vector2Df a, Vector2Df b);

    /**
     * Computes the dot product of two 3D vectors.
     *
     * @param a		A vector.
     * @param b		Another vector.
     *
     * @return The dot product of a and b.
     */
    float		VectorsDotProduct(Vector3Df a, Vector3Df b);

    /**
     * Computes the cross product of two 3D vectors.
     *
     * @param a		A vector.
     * @param b		Another vector.
     *
     * @return The cross product of a and b.
     */
    Vector3Df		VectorsCrossProduct(Vector3Df a, Vector3Df b);

    /**
     * Computes the magnitude of a 2D vector.
     *
     * @param v		A vector.
     *
     * @return The magnitude of v.
     */
    float		VectorMagnitude(Vector2Df v);

    /**
     * Computes the magnitude of a 3D vector.
     *
     * @param v		A vector.
     *
     * @return The magnitude of v.
     */
    float		VectorMagnitude(Vector3Df v);

    /**
     * Find the angle between two 2D vectors.
     *
     * @param a		A vector.
     * @param b		Another vector.
     * 
     * @return The angle between a and b.
     */
    float		VectorsAngle(Vector2Df a, Vector2Df b);

    /**
     * Find the angle between two 3D vectors.
     *
     * @param a		A vector.
     * @param b		Another vector.
     * 
     * @return The angle between a and b.
     */
    float		VectorsAngle(Vector3Df a, Vector3Df b);

    /**
     * Rotates a 2D point around another point.
     *
     * @param p			The point to rotate.
     * @param angle		The angle of rotation, in degrees.
     * @param centerOfRot	The point around which to rotate p.
     *
     * @return 'p' rotated of 'angle' degrees around point 'centerOfRot'.
     */
    Point2Df		PointRotate(Point2Df p, float angle, Point2Df centerOfRot);

    /**
     * Computes the center of mass of a 3D points.
     *
     * @param points	A list of points.
     *
     * @return The center of mass of the given points.
     */
    Point3Df		PointsCenterOfMass(const list<Point3Df> & points);
  }
}

// Here are the math functions which are templated, and therefore, need
// to be implemented in a header file, since the project compiles a library.

#include "XnMathTemplates.hpp"


#endif //_XN_MATH_HPP_
