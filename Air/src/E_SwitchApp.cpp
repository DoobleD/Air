#include "E_SwitchApp.hpp"

 
using namespace air;


os::Keyboard	E_SwitchApp::m_kb;


E_SwitchApp::E_SwitchApp(void) : XnVSwipeDetector(true, "SwitchApp")
{
  RegisterSwipeLeft(NULL, &E_SwitchApp::onSwipe);
  RegisterSwipeRight(NULL, &E_SwitchApp::onSwipe);

  SetMotionSpeedThreshold(SA_MIN_SPEED);
  SetSteadyMaxStdDev(10.f);
}

E_SwitchApp::~E_SwitchApp(void)
{
}

void XN_CALLBACK_TYPE		E_SwitchApp::onSwipe(XnFloat velocity, 
						     XnFloat angle, 
						     void *userCxt)
{
#ifdef __unix__
  m_kb.keyPress(os::Keyboard::ShiftLeft);
  m_kb.keyPress(os::Keyboard::AltLeft);

  m_kb.keyPress(os::Keyboard::Tab);
  m_kb.keyRelease(os::Keyboard::Tab);

  m_kb.keyRelease(os::Keyboard::AltLeft);
  m_kb.keyRelease(os::Keyboard::ShiftLeft);
#elif defined _WIN32
  m_kb.keyPress(os::Keyboard::ShiftLeft);
  m_kb.keyPress(os::Keyboard::AltLeft);

  Sleep(1);

  m_kb.keyPress(os::Keyboard::Tab);
  m_kb.keyRelease(os::Keyboard::Tab);

  Sleep(1);

  m_kb.keyRelease(os::Keyboard::AltLeft);
  m_kb.keyRelease(os::Keyboard::ShiftLeft);  
#endif
}
