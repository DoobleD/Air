#ifndef _COLOR_HPP_
#define _COLOR_HPP_


#include <string>


namespace air
{
  
  struct		Color
  {
    static const Color	Black;
    static const Color  Red;
    static const Color  Green;
    static const Color  Blue;
    static const Color  White;

    int			r;
    int			g;
    int			b;
    int			a;

    Color(int _r = 0, int _g = 0, 
	  int _b = 0, int _a = 255);

    const std::string	getRGBString(void) const;
  };

}

#endif //_COLOR_HPP_
