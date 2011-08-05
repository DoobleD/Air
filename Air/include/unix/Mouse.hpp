#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "SFML/Graphics.hpp"
#include "IMouse.hpp"

#include <X11/Xlib.h>


namespace air
{
  namespace os
  {

    class		Mouse : public IMouse
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
