#include "E_ShowKeyboard.hpp"

using namespace air;

E_ShowKeyboard::E_ShowKeyboard() : XnVSwipeDetector(true, "ShowKeyboard")
{
  RegisterSwipeRight(NULL, &E_ShowKeyboard::onSwipe);
  SetMotionSpeedThreshold(MIN_SPEED);
}

E_ShowKeyboard::~E_ShowKeyboard()
{
}

void XN_CALLBACK_TYPE		E_ShowKeyboard::onSwipe(XnFloat velocity, 
							XnFloat angle, 
							void *userCxt)
{
  printf("SHOW KEYBOARD!\n");
}
