#include "E_Maximize.hpp"

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
  printf("MAXIMIZE!\n");
}
