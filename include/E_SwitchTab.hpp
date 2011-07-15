#ifndef _E_SWITCH_TAB_HPP_
#define _E_SWITCH_TAB_HPP_

// NITE headers
#include <XnVCircleDetector.h>

namespace air
{

  class					E_SwitchTab : public XnVCircleDetector
  {
  public:
    E_SwitchTab();
    ~E_SwitchTab();

    static void XN_CALLBACK_TYPE	onCircle(XnFloat times, 
						 XnBool confident, 
						 const XnVCircle *circle, 
						 void *userCxt);

  };

}

#endif //_E_SWITCH_TAB_HPP_
