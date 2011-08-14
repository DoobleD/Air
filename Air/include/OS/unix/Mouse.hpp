#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "OS/IMouse.hpp"

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
      XEvent		m_buttonEvent;

      void		initializeButtonEvent(void);
      void		buttonPress(int button);
      void		buttonRelease(int button);

    public:
      Mouse(void);
      ~Mouse(void);

      void		setPosition(double x, double y);
      void		leftButtonPress(void);
      void		leftButtonRelease(void);
      void		rightButtonPress(void);
      void		rightButtonRelease(void);
    };

  }
}

#endif //_MOUSE_HPP_
