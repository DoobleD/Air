#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "OS/IScreen.hpp"

#include <SFML/System.hpp>

#include <X11/Xlib.h>

#include <list>

// 30 fps only. 60 causes screen to flickers because of the screen parts redraw
#define _FPS		30.f 


using namespace std;


namespace air
{
  namespace os
  {
    
    class		Screen : public IScreen, public sf::Thread
    {
      struct		Rectangle
      {
	int		x;
	int		y;
	int		sizeX;
	int		sizeY;
	Color		color;
	bool		erased;

	Rectangle(void) {erased = false;}
      };

    private:
      Display *		m_display;
      int		m_screen;
      Window		m_rootWindow;
      GC		m_gc;
      Colormap		m_colorMap;
      Pixmap		m_pixmapBuffer;

      list<Rectangle>	m_rectangles;

      // No use of mutex and reading/writing on m_threadRunning member
      // Since it is a boolean, its operations are atomic, and cannot 
      // be interrupted by another thread
      bool		m_threadRunning;

      // A mutex is used to control other members access
      sf::Mutex		m_mutex;


      Window		createInvisibleWin(int x, int y, int width, int height);
      void		buildGraphicContext(void);
      void		initializeXComponents(void);
      void		destroyXComponents(void);
      void		restoreOSScreen(void);
      void		paintRectangles(void);
      void		paintAll(void);

      void		Run(void);

    public:
      Screen(void);
      ~Screen(void);

      int		getResX(void);
      int		getResY(void);
      void		drawRectangle(int x, int y, 
				      int sizeX, int sizeY,
				      const air::Color & color);
      void		clear(void);
      void		display(void);
    };

  }
}

#endif //_SCREEN_HPP_
