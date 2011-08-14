#ifndef _E_SWITCH_TAB_LEFT_HPP_
#define _E_SWITCH_TAB_LEFT_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#define ST_MIN_SPEED			0.75 // m/s


namespace air
{

  class					E_SwitchTabLeft : public XnVSwipeDetector
  {
  public:
    E_SwitchTabLeft();
    ~E_SwitchTabLeft();
    
    static void XN_CALLBACK_TYPE	onSwipe(XnFloat velocity, 
						XnFloat angle, 
						void *userCxt);
  };

}

#endif //_E_SWITCH_TAB_LEFT_HPP_
