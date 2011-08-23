#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_


#include <list>

#include <Windows.h>

#include <SFML/System.hpp>

#include "OS/IScreen.hpp"


// 60 fps
#define _FPS		60.f


using namespace std;


namespace air
{
  namespace os
  {
    
    /**
     * Implementation of IScreen for Windows.
     * Offers methods related to the OS screen.
     *
     * The class is threaded to be able to draw above screen. SFML library
     * is used for thread managment (see http://www.sfml-dev.org/).
     *
     * @author Pierre Alletru
     */
    class		Screen : public IScreen, public sf::Thread
    {
      /**
       * Represent a rectangle to draw on screen.
       *
       * @author Pierre Alletru
       */
      struct		Rectangle
      {
	// Rectangle left/top corner coordinates and size.
	RECT		coord;
	// Rectangle color.
	COLORREF	color;
	// Indicates if the rectangle has to be removed from screen (when clear screen).
	bool		erased;

	/**
	 * Default constructor.
	 */
	Rectangle(void) {erased = false;}
      };

    private:

      // GDI screen device.
      HDC		m_screenDC;
      // GDI memory device, used for double buffering.
      HDC		m_memDC;
      // GDI bitmap and its handle, used for drawing.
      HBITMAP		m_bmap;
      HANDLE		m_bmapHandle;

      // No use of mutex and reading/writing on m_threadRunning member
      // Since it is a boolean, its operations are atomic, and cannot 
      // be interrupted by another thread.
      bool		m_threadRunning;
      // A mutex is used to control other members access.
      sf::Mutex		m_mutex;

      // A list of rectangles to draw.
      list<Rectangle>	m_rectangles;

      /**
       * Initialize GDI components.
       */
      void		destroyGDIComponents(void);

      /**
       * Destroy the GDI components.
       */
      void		initializeGDIComponents(void);

      /**
       * Repaint screen.
       */
      void		restoreOSScreen(void);

      /**
       * Paint rectangles to the screen.
       */
      void		paintRectangles(void);

      /**
       * Paint all shapes that have to be drawn on screen.
       */
      void		paintAll(void);

      /**
       * SFML thread entry. Starts a drawing loop (clear and draw at the defined fps).
       */
      void		Run(void);

    public:

      /**
       * Default constructor.
       */
      Screen(void);

      /**
       * Destructor.
       */
      ~Screen(void);

      /**
       * Get the x resolution of the screen.
       *
       * @return The x resolution of the screen.
       */
      int		getResX(void);

      /**
       * Get the y resolution of the screen.
       *
       * @return The y resolution of the screen.
       */
      int		getResY(void);

      /**
       * Draw a filled rectangle on screen.
       *
       * @param x	The x position of the top left corner of the rectangle.
       * @param x	The y position of the top left corner of the rectangle.
       * @param sizeX	The width of the rectangle.
       * @param sizeY	The height of the rectangle.
       * @param color	The color of the rectangle.
       */
      void		drawRectangle(int x, int y, 
				      int sizeX, int sizeY, 
				      const air::Color & color);

      /**
       * Clear the previsouly drawn shapes. So restore screen.
       */
      void		clear(void);

      /**
       * Actually draw the shapes to the screen.
       */
      void		display(void);
    };

  }
}

#endif //_SCREEN_HPP_
