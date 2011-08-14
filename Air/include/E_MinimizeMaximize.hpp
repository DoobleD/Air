#ifndef _E_MINIMIZE_MAXIMIZE_HPP_
#define _E_MINIMIZE_MAXIMIZE_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#include "OS/Keyboard.hpp"


#define MINMAX_SPEED			0.75 // m/s


namespace air
{

  class					E_MinimizeMaximize : public XnVSwipeDetector
  {
  private:
    static os::Keyboard			m_kb;

  public:
    E_MinimizeMaximize();
    ~E_MinimizeMaximize();
    
    static void XN_CALLBACK_TYPE	onSwipeUp(XnFloat velocity, 
						  XnFloat angle, 
						  void *userCxt);
    static void XN_CALLBACK_TYPE	onSwipeDown(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt);
  };

}

#endif //_E_MINIMIZE_MAXIMIZE_HPP_
