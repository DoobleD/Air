#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "IScreen.hpp"

#include <X11/Xlib.h>


using namespace std;


namespace air
{
  namespace os
  {
    
    class		Screen : public IScreen
    {
    private:
      Display *		m_display;
      Window		m_rootWindow;

      Window		m_refreshWin;
      GC		m_gc;
      Colormap		m_colorMap;

      void		buildGraphicContext(void);
      void		buildRefreshWin(void);

    public:
      Screen(void);
      ~Screen(void);

      int		getResX(void);
      int		getResY(void);
      void		drawDisc(int x, int y, int diameter, 
				 const air::Color & color);
      void		clear(void);
      void		display(void);
    };

  }
}

#endif //_SCREEN_HPP_
