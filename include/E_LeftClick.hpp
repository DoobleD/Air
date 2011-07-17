#ifndef _E_LEFT_CLICK_HPP_
#define _E_LEFT_CLICK_HPP_

// NITE headers
#include <XnVPushDetector.h>

namespace air
{

  class					E_LeftClick : public XnVPushDetector
  {
  public:
    E_LeftClick();
    ~E_LeftClick();
    
    static void XN_CALLBACK_TYPE	onPush(XnFloat velocity, 
					       XnFloat angle, 
					       void *userCxt);
  };
  
}

#endif //_E_LEFT_CLICK_HPP_
