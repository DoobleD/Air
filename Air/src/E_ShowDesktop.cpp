#include <SFML/System.hpp>

#include "E_ShowDesktop.hpp"


using namespace air;


os::Keyboard	E_ShowDesktop::m_kb;


E_ShowDesktop::E_ShowDesktop(void) : XnVCircleDetector("ShowDesktop")
{
  RegisterCircle(NULL, &E_ShowDesktop::onCircle);

  SetMinRadius(SD_MIN_RADIUS);
}

E_ShowDesktop::~E_ShowDesktop(void)
{
}

void XN_CALLBACK_TYPE		E_ShowDesktop::onCircle(XnFloat times, 
							XnBool confident,
							const XnVCircle * circle, 
							void * userCxt)
{
  static bool			requested = false;
  static sf::Clock		timer;

  if (requested == true && timer.GetElapsedTime() > 5)
    requested = false;

  if (requested == false)
    {
      m_kb.keyPress(os::Keyboard::SuperLeft);
      m_kb.keyPress(os::Keyboard::D);
      m_kb.keyRelease(os::Keyboard::D);
      m_kb.keyRelease(os::Keyboard::SuperLeft);

      requested = true;
      timer.Reset();
    }
}
