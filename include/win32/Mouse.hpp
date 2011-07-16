#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "IMouse.hpp"


namespace air
{
  namespace os
  {

    class		Mouse : public IMouse
    {
      void		setPosition(double x, double y);
    };

  }
}

#endif //_MOUSE_HPP_
