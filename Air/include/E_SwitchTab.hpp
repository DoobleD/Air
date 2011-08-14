#ifndef _E_SWITCH_TAB_HPP_
#define _E_SWITCH_TAB_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#include "OS/Keyboard.hpp"


#define ST_MIN_SPEED			0.75 // m/s


namespace air
{

  class					E_SwitchTab : public XnVSwipeDetector
  {
  private:
  static os::Keyboard			m_kb;

  public:
    E_SwitchTab(void);
    ~E_SwitchTab(void);
    
    static void XN_CALLBACK_TYPE	onSwipeLeft(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt);
    static void XN_CALLBACK_TYPE	onSwipeRight(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt);
  };

}

#endif //_E_SWITCH_TAB_HPP_
