#ifndef _E_SWITCH_TAB_HPP_
#define _E_SWITCH_TAB_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#include "OS/Keyboard.hpp"


#define ST_MIN_SPEED			1.35 // m/s


namespace air
{

  class					E_SwitchTab : public XnVSwipeDetector
  {
  private:
    static os::Keyboard			m_kb;

  public:
    E_SwitchTab(void);
    ~E_SwitchTab(void);
    
    static void XN_CALLBACK_TYPE	onSwipe(XnFloat velocity, 
						XnFloat angle, 
						void *userCxt);
  };

}

#endif //_E_SWITCH_TAB_HPP_
