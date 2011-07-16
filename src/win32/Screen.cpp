#include "Screen.hpp"

using namespace air::os;

int		Screen::getResX(void)
{
  GetSystemMetrics(SM_CXFULLSCREEN);
}

int		Screen::getResY(void)
{
  GetSystemMetrics(SM_CYFULLSCREEN);
}
