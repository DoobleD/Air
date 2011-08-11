#ifndef _COORD_CONVERTER_HPP_
#define _COORD_CONVERTER_HPP_

#include <XnTypes.h>

#include "OS/Screen.hpp"


namespace air
{

  class			CoordConverter
  {
  private:
    static os::Screen	m_screen;
    
  public:
    
    static XnPoint3D	realWorldToScreenSize(XnPoint3D point);
    static XnPoint3D	realWorldToNIScreen(XnPoint3D point);
  };

}

#endif //_COORD_CONVERTER_HPP_
