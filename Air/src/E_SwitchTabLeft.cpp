#include "E_SwitchTabLeft.hpp"
#include "OS/Keyboard.hpp"

using namespace air;


E_SwitchTabLeft::E_SwitchTabLeft() : XnVSwipeDetector(true, "SwitchTabLeft")
{
  RegisterSwipeLeft(NULL, &E_SwitchTabLeft::onSwipe);
  SetMotionSpeedThreshold(ST_MIN_SPEED);
}

E_SwitchTabLeft::~E_SwitchTabLeft()
{
}

void XN_CALLBACK_TYPE		E_SwitchTabLeft::onSwipe(XnFloat velocity, 
							 XnFloat angle, 
							 void *userCxt)
{
  static os::Keyboard		kb;

  printf("SWITCH TAB LEFT!\n");

#ifdef __unix__
  kb.keyPress(os::Keyboard::ShiftLeft);
  kb.keyPress(os::Keyboard::AltLeft);

  kb.keyPress(os::Keyboard::Tab);
  kb.keyRelease(os::Keyboard::Tab);

  kb.keyRelease(os::Keyboard::AltLeft);
  kb.keyRelease(os::Keyboard::ShiftLeft);
#elif defined _WIN32
  
#endif  
}
