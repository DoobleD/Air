#include "OS/Keyboard.hpp"

#include <X11/extensions/XTest.h>


using namespace air::os;


int IKeyboard::AltLeft = XK_Alt_L;
int IKeyboard::ShiftLeft = XK_Shift_L;
int IKeyboard::SuperLeft = XK_Super_L;
int IKeyboard::Escape = XK_Escape;
int IKeyboard::Tab = XK_Tab;
int IKeyboard::F4 = XK_F4;
int IKeyboard::F9 = XK_F9;
int IKeyboard::F10 = XK_F10;
int IKeyboard::D = XK_d;
int IKeyboard::Up = XK_Up;
int IKeyboard::Down = XK_Down;


Keyboard::Keyboard(void)
{
  m_display = XOpenDisplay(0);
}

Keyboard::~Keyboard(void)
{
  XCloseDisplay(m_display);
}

void		Keyboard::keyPress(int key)
{
  int		keycode;

  keycode = XKeysymToKeycode(m_display, key);

  XTestFakeKeyEvent(m_display, keycode, True, 0);

  XFlush(m_display);
}

void		Keyboard::keyRelease(int key)
{
  int		keycode;

  keycode = XKeysymToKeycode(m_display, key);

  XTestFakeKeyEvent(m_display, keycode, False, 0);

  XFlush(m_display);
}
