#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "IScreen.hpp"


namespace air
{
  namespace os
  {
    
    class		Screen : public IScreen
    {
    public:
      int		getResX(void);
      int		getResY(void);
    };

  }
}

#endif //_SCREEN_HPP_
