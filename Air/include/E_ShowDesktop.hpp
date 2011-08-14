#ifndef _E_SHOW_DESKTOP_HPP_
#define _E_SHOW_DESKTOP_HPP_

// NITE headers
#include <XnVPushDetector.h>

namespace air
{

  class					E_ShowDesktop : public XnVPushDetector
  {
  public:
    E_ShowDesktop();
    ~E_ShowDesktop();
    
    static void XN_CALLBACK_TYPE	onPush(XnFloat velocity, 
					       XnFloat angle, 
					       void *userCxt);
  };
  
}

#endif //_E_SHOW_DESKTOP_HPP_
