#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <X11/Xlib.h>

#include "IScreen.hpp"


namespace air
{
  namespace os
  {
    
    class		Screen : public IScreen
    {
    private:
      Display *		m_display;
      Window		m_rootWindow;

    public:
      Screen(void);
      ~Screen(void);

      int		getResX(void);
      int		getResY(void);
    };

  }
}

#endif //_SCREEN_HPP_
