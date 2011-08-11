#include "MouseControl.hpp"


using namespace air;


void		MouseControl::update(xn::FingersData & fingersData)
{
  if (fingersData.Size == 1)
    {
      m_mouse.setPosition(fingersData.Fingers[0].X, fingersData.Fingers[0].Y);
      m_mouse.buttonPress(os::Mouse::ButtonLeft);
      m_mouse.buttonRelease(os::Mouse::ButtonLeft);
    }
}
