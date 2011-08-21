#ifndef _E_SHOW_DESKTOP_HPP_
#define _E_SHOW_DESKTOP_HPP_

// NITE headers
#include <XnVCircleDetector.h>

#include "OS/Keyboard.hpp"


#define SD_MIN_RADIUS			60
#define SD_MIN_TIME			1


namespace air
{

  class					E_ShowDesktop : public XnVCircleDetector
  {
  private:
    static os::Keyboard			m_kb;
    
  public:
    E_ShowDesktop(void);
    ~E_ShowDesktop(void);
    
    static void XN_CALLBACK_TYPE	onCircle(XnFloat times, 
						 XnBool confident,
						 const XnVCircle * circle, 
						 void * userCxt);
  };
  
}

#endif //_E_SHOW_DESKTOP_HPP_
