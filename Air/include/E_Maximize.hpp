#ifndef _E_MAXIMIZE_HPP_
#define _E_MAXIMIZE_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#define MIN_SPEED			0.75 // m/s

namespace air
{

  class					E_Maximize : public XnVSwipeDetector
  {
  public:
    E_Maximize();
    ~E_Maximize();
    
    static void XN_CALLBACK_TYPE	onSwipe(XnFloat velocity, 
						XnFloat angle, 
						void *userCxt);
  };

}

#endif //_E_MAXIMIZE_HPP_
