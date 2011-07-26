#ifndef _XN_FINGER_TYPES_HPP_
#define _XN_FINGER_TYPES_HPP_

#include <memory>

namespace xn
{

  struct		HandPeak
  {
    XnPoint3D		Position;
    float		Angle;

    HandPeak(void)
    {}
    HandPeak(XnPoint3D position, float angle) 
    {Position = position; Angle = angle;}
  };
  
  struct		FingersData
  {
    XnVector3D *	Fingers;
    XnUInt32		Size;

    ~FingersData()
    {delete Fingers;}
  };
  
}

#endif //_XN_FINGER_TYPES_HPP_
