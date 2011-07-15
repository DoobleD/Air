#ifndef _E_RIGHT_CLICK_HPP_
#define _E_RIGHT_CLICK_HPP_

// NITE headers
#include <XnVPushDetector.h>

namespace air
{

  class					E_RightClick : public XnVPushDetector
  {
  public:
    E_RightClick();
    ~E_RightClick();
    
    static void XN_CALLBACK_TYPE	onPush(XnFloat velocity, 
					       XnFloat angle, 
					       void *userCxt);
  };
  
}

#endif //_E_RIGHT_CLICK_HPP_
