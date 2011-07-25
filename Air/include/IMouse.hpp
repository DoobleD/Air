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
    };

  }
}

#endif //_IMOUSE_HPP_
