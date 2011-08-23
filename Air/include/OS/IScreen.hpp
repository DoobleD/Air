#ifndef _ISCREEN_H_
#define _ISCREEN_H_


#include "Color.hpp"


namespace air
{
  namespace os
  {

    /**
     * Interface for an object offering methods related to the OS screen.
     * Since this is an interface, all methods a pure virtual, and
     * therefore needs to be implemented by child classes.
     *
     * @author Pierre Alletru
     */
    class		IScreen
    {
    public:

      /**
       * Get the x resolution of the screen.
       *
       * @return The x resolution of the screen.
       */
      virtual int	getResX(void) = 0;

      /**
       * Get the y resolution of the screen.
       *
       * @return The y resolution of the screen.
       */
      virtual int	getResY(void) = 0;

      /**
       * Draw a filled rectangle on screen.
       *
       * @param x	The x position of the top left corner of the rectangle.
       * @param x	The y position of the top left corner of the rectangle.
       * @param sizeX	The width of the rectangle.
       * @param sizeY	The height of the rectangle.
       * @param color	The color of the rectangle.
       */
      virtual void	drawRectangle(int x, int y, 
				      int sizeX, int sizeY,
				      const air::Color & color) = 0;
      
      /**
       * Clear the previsouly drawn shapes. So restore screen.
       */
      virtual void	clear(void) = 0;

      /**
       * Actually draw the shapes to the screen.
       */
      virtual void	display(void) = 0;

    };
  }
}

#endif //_ISCREEN_H_
