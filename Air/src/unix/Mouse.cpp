#include "Mouse.hpp"

#include <string.h>


using namespace air::os;


int IMouse::ButtonLeft = Button1;
int IMouse::ButtonRight = Button2;


Mouse::Mouse(void)
{
  m_display = XOpenDisplay(0);
  m_rootWindow = XRootWindow(m_display, DefaultScreen(m_display));

  XSelectInput(m_display, m_rootWindow, KeyReleaseMask);
  
  initializeButtonEvent();
}

Mouse::~Mouse(void)
{
}

void		Mouse::initializeButtonEvent(void)
{
  memset (&m_buttonEvent, 0, sizeof (m_buttonEvent));

  m_buttonEvent.xbutton.same_screen = True;
  m_buttonEvent.xbutton.subwindow = m_rootWindow;

  while (m_buttonEvent.xbutton.subwindow)
    {
      m_buttonEvent.xbutton.window = m_buttonEvent.xbutton.subwindow;
      XQueryPointer(m_display, m_buttonEvent.xbutton.window,
		    &m_buttonEvent.xbutton.root, &m_buttonEvent.xbutton.subwindow,
		    &m_buttonEvent.xbutton.x_root, &m_buttonEvent.xbutton.y_root,
		    &m_buttonEvent.xbutton.x, &m_buttonEvent.xbutton.y,
		    &m_buttonEvent.xbutton.state);
    }
}

void		Mouse::setPosition(double x, double y)
{
  XWarpPointer(m_display, None, m_rootWindow, 0, 0, 0, 0, x, y);
  
  XFlush(m_display); 
}

void		Mouse::buttonPress(int button)
{
  m_buttonEvent.xbutton.button = button;
  m_buttonEvent.type = ButtonPress;

  XSendEvent(m_display, PointerWindow, True, ButtonPressMask, &m_buttonEvent);

  XFlush(m_display);
}

void		Mouse::buttonRelease(int button)
{
  m_buttonEvent.xbutton.button = button;
  m_buttonEvent.type = ButtonRelease;

  XSendEvent(m_display, PointerWindow, True, ButtonReleaseMask, &m_buttonEvent);

  XFlush(m_display);
}
