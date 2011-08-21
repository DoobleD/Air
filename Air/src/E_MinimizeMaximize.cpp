#include "E_MinimizeMaximize.hpp"


using namespace air;


os::Keyboard	E_MinimizeMaximize::m_kb;


E_MinimizeMaximize::E_MinimizeMaximize() : XnVSwipeDetector(true, "MinimizeMaximize")
{
  RegisterSwipeUp(NULL, &E_MinimizeMaximize::onSwipeUp);
  RegisterSwipeDown(NULL, &E_MinimizeMaximize::onSwipeDown);
  
  SetMotionSpeedThreshold(MM_MIN_SPEED);
  SetSteadyMaxStdDev(10.f);
}

E_MinimizeMaximize::~E_MinimizeMaximize()
{
}

void XN_CALLBACK_TYPE		E_MinimizeMaximize::onSwipeUp(XnFloat velocity, 
							      XnFloat angle, 
							      void *userCxt)
{
#ifdef __unix__
  m_kb.keyPress(os::Keyboard::AltLeft);
  m_kb.keyPress(os::Keyboard::F10);
  m_kb.keyRelease(os::Keyboard::F10);
  m_kb.keyRelease(os::Keyboard::AltLeft);
#elif defined _WIN32
  m_kb.keyPress(os::Keyboard::SuperLeft);
  m_kb.keyPress(os::Keyboard::Up);
  m_kb.keyRelease(os::Keyboard::Up);
  m_kb.keyRelease(os::Keyboard::SuperLeft);
#endif
}

void XN_CALLBACK_TYPE		E_MinimizeMaximize::onSwipeDown(XnFloat velocity, 
								XnFloat angle, 
								void *userCxt)
{
#ifdef __unix__
  m_kb.keyPress(os::Keyboard::AltLeft);
  m_kb.keyPress(os::Keyboard::F9);
  m_kb.keyRelease(os::Keyboard::F9);
  m_kb.keyRelease(os::Keyboard::AltLeft);
#elif defined _WIN32
  m_kb.keyPress(os::Keyboard::SuperLeft);
  m_kb.keyPress(os::Keyboard::Down);
  m_kb.keyRelease(os::Keyboard::Down);
  m_kb.keyRelease(os::Keyboard::SuperLeft);
#endif
}
