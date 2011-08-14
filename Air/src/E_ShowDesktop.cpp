#include "E_ShowDesktop.hpp"


using namespace air;


os::Keyboard	E_ShowDesktop::m_kb;


E_ShowDesktop::E_ShowDesktop(void) : XnVPushDetector("ShowDesktop")
{
  RegisterPush(NULL, &E_ShowDesktop::onPush);

  SetPushMaximumAngleBetweenImmediateAndZ(15.f);
  SetPushImmediateMinimumVelocity(SD_MIN_SPEED);
}

E_ShowDesktop::~E_ShowDesktop(void)
{
}

void XN_CALLBACK_TYPE		E_ShowDesktop::onPush(XnFloat velocity, 
						      XnFloat angle, 
						      void *userCxt)
{
  printf("SHOW DESKTOP!\n");
  
  m_kb.keyPress(os::Keyboard::SuperLeft);
  m_kb.keyPress(os::Keyboard::d);
  m_kb.keyRelease(os::Keyboard::d);
  m_kb.keyRelease(os::Keyboard::SuperLeft);
}
