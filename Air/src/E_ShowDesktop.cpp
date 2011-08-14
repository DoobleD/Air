#include "E_ShowDesktop.hpp"

using namespace air;

E_ShowDesktop::E_ShowDesktop() : XnVPushDetector("ShowDesktop")
{
  RegisterPush(NULL, &E_ShowDesktop::onPush);
}

E_ShowDesktop::~E_ShowDesktop()
{
}

void XN_CALLBACK_TYPE		E_ShowDesktop::onPush(XnFloat velocity, 
						      XnFloat angle, 
						      void *userCxt)
{
  printf("SHOW DESKTOP!\n");
}
