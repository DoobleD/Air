#ifndef _XN_FINGER_TYPES_HPP_
#define _XN_FINGER_TYPES_HPP_

#include <XnTypes.h>


namespace xn
{
  /**
   * Math types
   */
  struct			Point2Df
  {
    float			X;
    float			Y;

    Point2Df(void) {}
    Point2Df(float x, float y) {X = x; Y = y;}
  };

  struct			Point3Df : public Point2Df
  {
    float			Z;

    Point3Df(void) {}
    Point3Df(float x, float y, float z) : Point2Df(x, y) {X = x; Y = y; Z = z;}
  };


  typedef Point2Df		Vector2Df;
  typedef Point3Df		Vector3Df;


  /**
   * More general types
   */
  struct			HandPeak
  {
    Point3Df			Position;
    float			Angle;
    int				FramesVisible;

    HandPeak(void) {}
    HandPeak(Point3Df position, float angle) 
    {Position = position; Angle = angle; FramesVisible = 0;}
  };
  
  struct			FingersData
  {
    XnVector3D *		Fingers;
    XnVector3D			Hand;
    XnFloat			HandAngle;
    XnUInt32			Size;
    
    ~FingersData() {delete Fingers;}
  };
  
}

#endif //_XN_FINGER_TYPES_HPP_
