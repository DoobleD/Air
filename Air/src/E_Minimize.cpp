#include "E_Minimize.hpp"
#include "OS/Keyboard.hpp"


using namespace air;


E_Minimize::E_Minimize() : XnVSwipeDetector(true, "Minimize")
{
  RegisterSwipeDown(NULL, &E_Minimize::onSwipe);
  SetMotionSpeedThreshold(MINI_MIN_SPEED);
}

E_Minimize::~E_Minimize()
{
}

void XN_CALLBACK_TYPE		E_Minimize::onSwipe(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt)
{
  static os::Keyboard		kb;

  printf("MINIMIZE!\n");
  
#ifdef __unix__
  kb.keyPress(os::Keyboard::AltLeft);
  kb.keyPress(os::Keyboard::F9);
  kb.keyRelease(os::Keyboard::F9);
  kb.keyRelease(os::Keyboard::AltLeft);
#elif defined _WIN32
  
#endif
}
