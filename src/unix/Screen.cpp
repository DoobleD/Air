#include <X11/Xlib.h>

#include "Screen.hpp"

// No use of 'using namespace air::os' to avoid conflict with a struct Screen form Xlib

int			air::os::Screen::getResX(void)
{
  Display *		display;
  Window		root_window;
  XWindowAttributes 	attributes;

  display = XOpenDisplay(0);
  root_window = XRootWindow(display, 0);
  
  XGetWindowAttributes(display, root_window, &attributes);

  return attributes.width;
}

int			air::os::Screen::getResY(void)
{
  Display *		display;
  Window		root_window;
  XWindowAttributes 	attributes;

  display = XOpenDisplay(0);
  root_window = XRootWindow(display, 0);
  
  XGetWindowAttributes(display, root_window, &attributes);

  return attributes.width;
}
