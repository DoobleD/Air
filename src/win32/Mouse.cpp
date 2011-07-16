#include "Mouse.hpp"

using namespace air::os;

void		Mouse::setPosition(double x, double y)
{
  SetCursorPos(x, y);
}
