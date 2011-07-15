#include "E_LeftClick.hpp"

using namespace air;

E_LeftClick::E_LeftClick() : XnVPushDetector("LeftClick")
{
  RegisterPush(NULL, &E_LeftClick::onPush);
}

E_LeftClick::~E_LeftClick()
{
}

void XN_CALLBACK_TYPE		E_LeftClick::onPush(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt)
{
  printf("LEFT CLICK!\n");
}
