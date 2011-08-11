#ifndef _IMOUSE_HPP_
#define _IMOUSE_HPP_

namespace air
{
  namespace os
  {

    class		IMouse
    {
    public:
      static int	ButtonLeft;
      static int	ButtonRight;

      virtual void	setPosition(double x, double y) = 0;
      virtual void	buttonPress(int button) = 0;
      virtual void	buttonRelease(int button) = 0;
    };

  }
}

#endif //_IMOUSE_HPP_
