#include "E_SwitchTabRight.hpp"
#include "OS/Keyboard.hpp"

using namespace air;


E_SwitchTabRight::E_SwitchTabRight() : XnVSwipeDetector(true, "SwitchTabRight")
{
  RegisterSwipeRight(NULL, &E_SwitchTabRight::onSwipe);
  SetMotionSpeedThreshold(ST_MIN_SPEED);
}

E_SwitchTabRight::~E_SwitchTabRight()
{
}

void XN_CALLBACK_TYPE		E_SwitchTabRight::onSwipe(XnFloat velocity, 
							  XnFloat angle, 
							  void *userCxt)
{
  static os::Keyboard		kb;

  printf("SWITCH TAB RIGHT!\n");

#ifdef __unix__
  kb.keyPress(os::Keyboard::AltLeft);
  kb.keyPress(os::Keyboard::Tab);
  kb.keyRelease(os::Keyboard::Tab);
  kb.keyRelease(os::Keyboard::AltLeft);
#elif defined _WIN32
  
#endif  
}
