#include <Windows.h>

#include "OS/Mouse.hpp"

using namespace air::os;

void		Mouse::setPosition(double x, double y)
{
  SetCursorPos((int) x, (int) y);
}
