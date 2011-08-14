#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "OS/IMouse.hpp"


namespace air
{
  namespace os
  {

    class		Mouse : public IMouse
    {
    public:
      void		setPosition(double x, double y);
      void		leftButtonPress(void);
      void		leftButtonRelease(void);
      void		rightButtonPress(void);
      void		rightButtonRelease(void);
    };

  }
}

#endif //_MOUSE_HPP_
