#ifndef _ISCREEN_H_
#define _ISCREEN_H_


#include "Color.hpp"


namespace air
{
  namespace os
  {
    class		IScreen
    {
    public:
      virtual int	getResX(void) = 0;
      virtual int	getResY(void) = 0;
      virtual void	drawRectangle(int x, int y, 
				      int sizeX, int sizeY,
				      const air::Color & color) = 0;
      virtual void	clear(void) = 0;
      virtual void	display(void) = 0;

    };
  }
}

#endif //_ISCREEN_H_
