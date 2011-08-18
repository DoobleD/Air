#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "OS/IMouse.hpp"


namespace air
{
  namespace os
  {

    class		Mouse : public IMouse
    {
    private:
      int		m_resX;
      int		m_resY;

    public:
      Mouse(void);
      ~Mouse(void);

      void		setPosition(double x, double y);
      void		leftButtonPress(void);
      void		leftButtonRelease(void);
      void		rightButtonPress(void);
      void		rightButtonRelease(void);
      void		wheelUp(void);
      void		wheelDown(void);
    };

  }
}

#endif //_MOUSE_HPP_
