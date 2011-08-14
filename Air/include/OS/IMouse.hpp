#ifndef _IMOUSE_HPP_
#define _IMOUSE_HPP_

namespace air
{
  namespace os
  {

    class		IMouse
    {
    public:
      virtual void	setPosition(double x, double y) = 0;
      virtual void	leftButtonPress(void) = 0;
      virtual void	leftButtonRelease(void) = 0;
      virtual void	rightButtonPress(void) = 0;
      virtual void	rightButtonRelease(void) = 0;
    };

  }
}

#endif //_IMOUSE_HPP_
