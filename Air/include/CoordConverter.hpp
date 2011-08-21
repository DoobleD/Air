#ifndef _COORD_CONVERTER_HPP_
#define _COORD_CONVERTER_HPP_

#include <XnTypes.h>

#include "OS/Screen.hpp"


#define DEFAULT_SPEED_FACTOR	2


namespace air
{

  class			CoordConverter
  {
  private:

    static os::Screen	m_screen;

  public:
    
    static XnPoint3D	realWorldToScreenSize(XnPoint3D point);
    static XnPoint3D	realWorldToNIScreen(XnPoint3D point);
    static XnPoint3D	screenSizeToSpeedFactor(XnPoint3D point, 
						int speedFactor = DEFAULT_SPEED_FACTOR);
  };

}

#endif //_COORD_CONVERTER_HPP_
