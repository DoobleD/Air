#include "E_SwitchTab.hpp"

 
using namespace air;


os::Keyboard	E_SwitchTab::m_kb;


E_SwitchTab::E_SwitchTab(void) : XnVSwipeDetector(true, "SwitchTab")
{
  RegisterSwipeLeft(NULL, &E_SwitchTab::onSwipeLeft);
  RegisterSwipeRight(NULL, &E_SwitchTab::onSwipeLeft);

  SetMotionSpeedThreshold(ST_MIN_SPEED);
  SetSteadyMaxStdDev(10.f);
}

E_SwitchTab::~E_SwitchTab(void)
{
}

void XN_CALLBACK_TYPE		E_SwitchTab::onSwipeRight(XnFloat velocity, 
							  XnFloat angle, 
							  void *userCxt)
{
  printf("SWITCH TAB RIGHT!\n");

#ifdef __unix__
  m_kb.keyPress(os::Keyboard::AltLeft);
  m_kb.keyPress(os::Keyboard::Tab);
  m_kb.keyRelease(os::Keyboard::Tab);
  m_kb.keyRelease(os::Keyboard::AltLeft);
#elif defined _WIN32  

#endif
}

void XN_CALLBACK_TYPE		E_SwitchTab::onSwipeLeft(XnFloat velocity, 
							 XnFloat angle, 
							 void *userCxt)
{
  printf("SWITCH TAB LEFT!\n");

#ifdef __unix__
  m_kb.keyPress(os::Keyboard::ShiftLeft);
  m_kb.keyPress(os::Keyboard::AltLeft);

  m_kb.keyPress(os::Keyboard::Tab);
  m_kb.keyRelease(os::Keyboard::Tab);

  m_kb.keyRelease(os::Keyboard::AltLeft);
  m_kb.keyRelease(os::Keyboard::ShiftLeft);
#elif defined _WIN32
  
#endif  
}
