#ifndef _COORD_CONVERTER_HPP_
#define _COORD_CONVERTER_HPP_

#include <XnTypes.h>

namespace air
{

  class			CoordConverter
  {
  public:
    
    static XnPoint3D	realWorldToScreenSize(XnPoint3D point);
    static XnPoint3D	realWorldToNIScreen(XnPoint3D point);
  };

}

#endif //_COORD_CONVERTER_HPP_
