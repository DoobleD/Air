#ifndef _E_MINIMIZE_HPP_
#define _E_MINIMIZE_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#define MIN_SPEED			0.75 // m/s

namespace air
{

  class					E_Minimize : public XnVSwipeDetector
  {
  public:
    E_Minimize();
    ~E_Minimize();
    
    static void XN_CALLBACK_TYPE	onSwipe(XnFloat velocity, 
						XnFloat angle, 
						void *userCxt);
  };

}

#endif //_E_MINIMIZE_HPP_
