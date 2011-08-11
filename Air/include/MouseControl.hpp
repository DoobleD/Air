#ifndef _MOUSE_CONTROL_HPP_
#define _MOUSE_CONTROL_HPP_

#include "XnFingerTypes.hpp"

#include "Mouse.hpp"


namespace air
{
  class			MouseControl
  {
  private:
    
    os::Mouse		m_mouse;
    
  public:
    
    void		update(xn::FingersData & fingersData);
  };
}

#endif //_MOUSE_CONTROL_HPP_
