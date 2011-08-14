#include <Windows.h>

#include "OS/Mouse.hpp"


using namespace air::os;


void		Mouse::setPosition(double x, double y)
{
  SetCursorPos((int) x, (int) y);
}

void		Mouse::leftButtonPress(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_LEFTDOWN, pos.x, pos.y, 0, 0);
}

void		Mouse::leftButtonRelease(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_LEFTUP, pos.x, pos.y, 0, 0);
}

void		Mouse::rightButtonPress(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_RIGHTDOWN, pos.x, pos.y, 0, 0);
}

void		Mouse::rightButtonRelease(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_RIGHTUP, pos.x, pos.y, 0, 0);
}
