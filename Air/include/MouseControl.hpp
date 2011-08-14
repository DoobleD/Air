#ifndef _MOUSE_CONTROL_HPP_
#define _MOUSE_CONTROL_HPP_

#include "XnFingerTypes.hpp"

#include "OS/Mouse.hpp"
#include "OS/Screen.hpp"

#define	REQUIRED_MAX_FINGERS	2

#define MODE_NONE		0
#define MODE_POINTER		1
#define MODE_PRESSED		2
#define MODE_SCROLL		3

namespace air
{
  class			MouseControl
  {
  private:
    char		m_mode;

    XnPoint3D		m_scrollPos;

    os::Mouse		m_mouse;
    os::Screen &	m_screen;

  public:
    MouseControl(os::Screen & screen);
    ~MouseControl(void);

    void		resetMode(void);    
    bool		isAMouseMode(xn::FingersData & fingersData);
    void		update(xn::FingersData & fingersData);
  };
}

#endif //_MOUSE_CONTROL_HPP_
