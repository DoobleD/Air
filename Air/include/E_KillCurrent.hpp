#ifndef _E_KILL_CURRENT_HPP_
#define _E_KILL_CURRENT_HPP_

// NITE headers
#include <XnVPushDetector.h>

#include "OS/Keyboard.hpp"


#define KC_MIN_SPEED			0.65f


namespace air
{

  class					E_KillCurrent : public XnVPushDetector
  {
  private:
    static os::Keyboard			m_kb;
    
  public:
    E_KillCurrent(void);
    ~E_KillCurrent(void);
    
    static void XN_CALLBACK_TYPE	onPush(XnFloat velocity, 
					       XnFloat angle, 
					       void *userCxt);
  };
  
}

#endif //_E_KILL_CURRENT_HPP_
