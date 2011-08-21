#include "E_KillCurrent.hpp"


using namespace air;


os::Keyboard	E_KillCurrent::m_kb;


E_KillCurrent::E_KillCurrent(void) : XnVPushDetector("KillCurrent")
{
  RegisterPush(NULL, &E_KillCurrent::onPush);

  SetPushMaximumAngleBetweenImmediateAndZ(15.f);
  SetPushImmediateMinimumVelocity(KC_MIN_SPEED);
}

E_KillCurrent::~E_KillCurrent(void)
{
}

void XN_CALLBACK_TYPE		E_KillCurrent::onPush(XnFloat velocity, 
						      XnFloat angle, 
						      void *userCxt)
{
  m_kb.keyPress(os::Keyboard::AltLeft);
  m_kb.keyPress(os::Keyboard::F4);
  m_kb.keyRelease(os::Keyboard::F4);
  m_kb.keyRelease(os::Keyboard::AltLeft);
}
