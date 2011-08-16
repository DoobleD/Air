#include "Color.hpp"

#include <stdio.h>


using namespace air;


const Color Color::Black = Color(0, 0, 0);
const Color Color::Red = Color(255, 0, 0);
const Color Color::Green = Color(0, 255, 0);
const Color Color::Blue = Color(0, 0, 255);
const Color Color::Yellow = Color(255, 255, 0);
const Color Color::White = Color(255, 255, 254);


Color::Color(int _r, int _g, 
	     int _b, int _a)
{
  r = _r;
  g = _g;
  b = _b;
  a = _a;
}

const std::string	Color::getRGBString(void) const
{
  char s[8];
  
  *s = '#';
  sprintf(s + 1, "%.2X%.2X%.2X", r, g, b);
  
  return std::string(s);
}

