#ifndef _ISCREEN_H_
#define _ISCREEN_H_

namespace air
{
  namespace os
  {
    class		IScreen
    {
    public:
      virtual int	getResX(void) = 0;
      virtual int	getResY(void) = 0;
    };
  }
}

#endif //_ISCREEN_H_
