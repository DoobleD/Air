#ifndef _E_SHOW_DESKTOP_HPP_
#define _E_SHOW_DESKTOP_HPP_

// NITE headers
#include <XnVPushDetector.h>

#include "OS/Keyboard.hpp"


#define SD_MIN_SPEED			1.0f


namespace air
{

  class					E_ShowDesktop : public XnVPushDetector
  {
  private:
    static os::Keyboard			m_kb;
    
  public:
    E_ShowDesktop(void);
    ~E_ShowDesktop(void);
    
    static void XN_CALLBACK_TYPE	onPush(XnFloat velocity, 
					       XnFloat angle, 
					       void *userCxt);
  };
  
}

#endif //_E_SHOW_DESKTOP_HPP_
