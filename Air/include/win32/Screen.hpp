#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "IScreen.hpp"

#include <SFML/System.hpp>

#include <Windows.h>
#include <list>


#define _FPS		60.f // 60 fps


namespace air
{
  namespace os
  {
    
    class			Screen : public IScreen, public sf::Thread
    {
      struct			Rectangle
      {
	RECT			coord;
	COLORREF		color;
	bool			erased;

	Rectangle(void) {erased = false;}
      };

    private:
      HDC			m_screenDC;
      HDC			m_memDC;
      HBITMAP			m_bmap;
      HANDLE			m_bmapHandle;

      volatile bool		m_threadRunning;
      sf::Mutex			m_mutex;

      std::list<Rectangle>	m_discs;

      void			restore(void);
      void			drawAll(void);
      void			shutdownThread(void);
      void			initThread(void);

      void			Run(void);

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
