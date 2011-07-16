#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include <X11/Xlib.h>

namespace air
{
  namespace os
  {

    class		Mouse
    {
    private:
      Display *		m_display;
      Window		m_rootWindow;

    public:
      Mouse(void);
      ~Mouse(void);

      void		setPosition(double x, double y);
    };

  }
}

#endif //_MOUSE_HPP_
