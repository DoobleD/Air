#include "E_Minimize.hpp"

using namespace air;

E_Minimize::E_Minimize() : XnVSwipeDetector(true, "Minimize")
{
  RegisterSwipeDown(NULL, &E_Minimize::onSwipe);
  SetMotionSpeedThreshold(MIN_SPEED);
}

E_Minimize::~E_Minimize()
{
}

void XN_CALLBACK_TYPE		E_Minimize::onSwipe(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt)
{
  printf("MINIMIZE!\n");
}
