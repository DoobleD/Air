#include <Windows.h>

#include "Screen.hpp"

using namespace air::os;

int		Screen::getResX(void)
{
  return GetSystemMetrics(SM_CXFULLSCREEN);
}

int		Screen::getResY(void)
{
  return GetSystemMetrics(SM_CYFULLSCREEN);
}
