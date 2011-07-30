#ifndef _XN_MATH_HPP_
#define _XN_MATH_HPP_

#include <XnTypes.h>

#define PI		3.1415926535897932384626433832795


namespace xn
{

  class				Math
  {
  public:
    static XnPoint3D		PointsCenter(XnPoint3D a, XnPoint3D b);
    static XnPoint3D		PointCreate(int x, int y, int z);
    static bool			Equal(XnPoint3D a, XnPoint3D b);
    static XnVector3D		PointsVector(XnPoint3D a, XnPoint3D b);
    static float		PointsDistance(XnPoint3D a, XnPoint3D b);
    static float		VectorsDotProduct(XnVector3D a, XnVector3D b);
    static XnVector3D		VectorsCrossProduct(XnVector3D a, XnVector3D b);
    static float		VectorMagnitude(XnVector3D v);
    static float		VectorsAngle(XnVector3D a, XnVector3D b);
  };

}

#endif //_XN_MATH_HPP_
