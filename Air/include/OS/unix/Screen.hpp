#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_


#include <list>

#include <X11/Xlib.h>

#include <SFML/System.hpp>

#include "OS/IScreen.hpp"


// 30 fps only. 60 causes screen to flickers because of the screen parts redraw
#define _FPS		30.f 


using namespace std;


namespace air
{
  namespace os
  {

    /**
     * Implementation of IScreen for unix systems.
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
	// Rectangle left/top corner coordinates.
	int		x;
	int		y;
	// Rectangle width and height.
	int		sizeX;
	int		sizeY;
	// Rectangle color.
	Color		color;
	// Indicates if the rectangle has to be removed from screen (when clear screen)
	bool		erased;
	
	/**
	 * Default constructor.
	 */
	Rectangle(void) {erased = false;}
      };

    private:

      // X11 display device.
      Display *		m_display;
      // Screen id.
      int		m_screen;
      // Root X11 window handle.
      Window		m_rootWindow;
      // X11 graphic context used to draw.
      GC		m_gc;
      // X11 color map of screen.
      Colormap		m_colorMap;
      // X11 pixmap, used for double buffering.
      Pixmap		m_pixmapBuffer;

      // No use of mutex and reading/writing on m_threadRunning member
      // Since it is a boolean, its operations are atomic, and cannot 
      // be interrupted by another thread.
      bool		m_threadRunning;
      // A mutex is used to control other members access.
      sf::Mutex		m_mutex;

      // A list of rectangles to draw.
      list<Rectangle>	m_rectangles;

      /**
       * Creates an invisible window of the given size. Used to generate a repaint
       * event on screen for all the active windows, at the given location.
       *
       * @param x	The x coordinate of the top left corner of the window.
       * @param y	The y coordinate of the top left corner of the window.
       * @param width	The width of the window.
       * @param height	The height of the window.
       *
       * @return A X11 handle of the created window.
       */
      Window		createInvisibleWin(int x, int y, int width, int height);

      /**
       * Build the X11 GC.
       */
      void		buildGraphicContext(void);

      /**
       * Initialize X11 components.
       */
      void		initializeXComponents(void);

      /**
       * Destroy the X11 components.
       */
      void		destroyXComponents(void);

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
