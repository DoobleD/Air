#include "OS/Mouse.hpp"

#include <string.h>


using namespace air::os;


Mouse::Mouse(void)
{
  m_display = XOpenDisplay(0);
  m_rootWindow = XRootWindow(m_display, DefaultScreen(m_display));

  XSelectInput(m_display, m_rootWindow, KeyReleaseMask);
}

Mouse::~Mouse(void)
{
  XCloseDisplay(m_display);
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
  initializeButtonEvent();
  
  m_buttonEvent.xbutton.button = button;
  m_buttonEvent.type = ButtonPress;

  XSendEvent(m_display, PointerWindow, True, ButtonPressMask, &m_buttonEvent);

  XFlush(m_display);
}

void		Mouse::buttonRelease(int button)
{
  initializeButtonEvent();

  m_buttonEvent.xbutton.button = button;
  m_buttonEvent.type = ButtonRelease;

  XSendEvent(m_display, PointerWindow, True, ButtonReleaseMask, &m_buttonEvent);

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
  buttonPress(Button2);
}

void		Mouse::rightButtonRelease(void)
{
  buttonRelease(Button2);
}

void		Mouse::middleButtonPress(void)
{
  buttonPress(Button3);
}

void		Mouse::middleButtonRelease(void)
{
  buttonRelease(Button3);
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
