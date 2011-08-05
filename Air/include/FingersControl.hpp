#ifndef _FINGERS_CONTROL_HPP_
#define _FINGERS_CONTROL_HPP_


#include "XnTypes.h"
#include "XnFingersGenerator.hpp"

namespace air
{
  
  class					FingersControl
  {
  public:

    static void XN_CALLBACK_TYPE	FingersCreate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      const xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData);
    static void XN_CALLBACK_TYPE	FingersUpdate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      const xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData);
    static void XN_CALLBACK_TYPE	FingersDestroy(xn::FingersGenerator & gen,
						       XnUserID id, 
						       XnFloat time,
						       void * userData);
  };

}

#endif //_FINGERS_CONTROL_HPP_
