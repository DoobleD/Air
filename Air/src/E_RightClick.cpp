#include "E_RightClick.hpp"

using namespace air;

E_RightClick::E_RightClick() : XnVPushDetector("RightClick")
{
  RegisterPush(NULL, &E_RightClick::onPush);
}

E_RightClick::~E_RightClick()
{
}

void XN_CALLBACK_TYPE		E_RightClick::onPush(XnFloat velocity, 
						     XnFloat angle, 
						     void *userCxt)
{
  printf("RIGHT CLICK!\n");
}
