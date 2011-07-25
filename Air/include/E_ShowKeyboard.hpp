#ifndef _E_SHOW_KEYBOARD_HPP_
#define _E_SHOW_KEYBOARD_HPP_

// NITE headers
#include <XnVSwipeDetector.h>

#define MIN_SPEED			0.75 // m/s

namespace air
{

  class					E_ShowKeyboard : public XnVSwipeDetector
  {
  public:
    E_ShowKeyboard();
    ~E_ShowKeyboard();
    
    static void XN_CALLBACK_TYPE	onSwipe(XnFloat velocity, 
						XnFloat angle, 
						void *userCxt);
  };

}

#endif //_E_SHOW_KEYBOARD_HPP_
