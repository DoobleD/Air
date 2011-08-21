#include "OS/Mouse.hpp"

#include <X11/extensions/XTest.h>


using namespace air::os;


Mouse::Mouse(void)
{
  m_display = XOpenDisplay(0);
}

Mouse::~Mouse(void)
{
  XCloseDisplay(m_display);
}

void		Mouse::setPosition(double x, double y)
{
  XTestFakeMotionEvent(m_display, -1, x, y, CurrentTime);
  
  XFlush(m_display); 
}

void		Mouse::buttonPress(int button)
{
  XTestFakeButtonEvent(m_display, button, True, CurrentTime);

  XFlush(m_display);
}

void		Mouse::buttonRelease(int button)
{
  XTestFakeButtonEvent(m_display, button, False, CurrentTime);

  XFlush(m_display);
}

void		Mouse::leftButtonPress(void)
{
  buttonPress(Button1);
}

void		Mouse::leftButtonRelease(void)
{
  buttonRelease(Button1);
}

void		Mouse::rightButtonPress(void)
{
  buttonPress(Button3);
}

void		Mouse::rightButtonRelease(void)
{
  buttonRelease(Button3);
}

void		Mouse::middleButtonPress(void)
{
  buttonPress(Button2);
}

void		Mouse::middleButtonRelease(void)
{
  buttonRelease(Button2);
}

void		Mouse::wheelUp(void)
{
  buttonPress(Button4);
  buttonRelease(Button4);
}

void		Mouse::wheelDown(void)
{
  buttonPress(Button5);
  buttonRelease(Button5);
}
