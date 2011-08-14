#include "E_Maximize.hpp"
#include "OS/Keyboard.hpp"


using namespace air;


E_Maximize::E_Maximize() : XnVSwipeDetector(true, "Maximize")
{
  RegisterSwipeUp(NULL, &E_Maximize::onSwipe);
  SetMotionSpeedThreshold(MIN_SPEED);
}

E_Maximize::~E_Maximize()
{
}

void XN_CALLBACK_TYPE		E_Maximize::onSwipe(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt)
{
  static os::Keyboard		kb;

  printf("MAXIMIZE!\n");

#ifdef __unix__
  kb.keyPress(os::Keyboard::AltLeft);
  kb.keyPress(os::Keyboard::Escape);
  kb.keyRelease(os::Keyboard::Escape);
  kb.keyRelease(os::Keyboard::AltLeft);
#elif defined _WIN32
  
#endif
}
