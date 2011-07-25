#include "Mouse.hpp"

using namespace air::os;

Mouse::Mouse(void)
{
  m_display = XOpenDisplay(0);
  m_rootWindow = XRootWindow(m_display, 0);

  XSelectInput(m_display, m_rootWindow, KeyReleaseMask);
}

Mouse::~Mouse(void)
{

}

void		Mouse::setPosition(double x, double y)
{
  XWarpPointer(m_display, None, m_rootWindow, 0, 0, 0, 0, x, y);
  
  // Flushes the output buffer, therefore updates the cursor's position. 
  // Thanks to Achernar.
  XFlush(m_display); 
}
