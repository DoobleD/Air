#include "Screen.hpp"

// No use of 'using namespace air::os' to avoid conflict with a struct Screen form Xlib

air::os::Screen::Screen(void)
{
  m_display = XOpenDisplay(0);
  m_rootWindow = XRootWindow(m_display, 0);
}

air::os::Screen::~Screen(void)
{
}

int			air::os::Screen::getResX(void)
{
  XWindowAttributes 	attributes;

  XGetWindowAttributes(m_display, m_rootWindow, &attributes);

  return attributes.width;
}

int			air::os::Screen::getResY(void)
{
  XWindowAttributes 	attributes;

  XGetWindowAttributes(m_display, m_rootWindow, &attributes);

  return attributes.height;
}
