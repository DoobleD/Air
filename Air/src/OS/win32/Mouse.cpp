#include <Windows.h>

#include "OS/Mouse.hpp"
#include "OS/Screen.hpp"


using namespace air::os;


Mouse::Mouse(void)
{
  Screen	screen;

  m_resX = screen.getResX();
  m_resY = screen.getResY();
}

Mouse::~Mouse(void)
{
}

void		Mouse::setPosition(double x, double y)
{
  if (x >= 0 && x < m_resX &&
      y >= 0 && y < m_resY)
    {
      SetCursorPos((int) x, (int) y);
    }
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

void		Mouse::middleButtonPress(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_MIDDLEDOWN, pos.x, pos.y, 0, 0);
}

void		Mouse::middleButtonRelease(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_MIDDLEUP, pos.x, pos.y, 0, 0);
}

void		Mouse::wheelUp(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_WHEEL, pos.x, pos.y, 120, 0);
}

void		Mouse::wheelDown(void)
{
  POINT		pos;

  GetCursorPos(&pos);

  mouse_event(MOUSEEVENTF_WHEEL, pos.x, pos.y, -120, 0);
}
