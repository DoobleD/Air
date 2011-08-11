#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "IScreen.hpp"

#include <SFML/System.hpp>

#include <Windows.h>
#include <list>


#define _FPS		60.f // 60 fps


using namespace std;


namespace air
{
  namespace os
  {
    
    class		Screen : public IScreen, public sf::Thread
    {
      struct		Rectangle
      {
	RECT		coord;
	COLORREF	color;
	bool		erased;

	Rectangle(void) {erased = false;}
      };

    private:
      HDC		m_screenDC;
      HDC		m_memDC;
      HBITMAP		m_bmap;
      HANDLE		m_bmapHandle;

      // No use of mutex and reading/writing on m_threadRunning member
      // Since it is a boolean, its operations are atomic, and cannot 
      // be interrupted by another thread
      bool		m_threadRunning;

      // A mutex is used to control other members access
      sf::Mutex		m_mutex;

      list<Rectangle>	m_rectangles;

      void		destroyGDIComponents(void);
      void		initializeGDIComponents(void);
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
