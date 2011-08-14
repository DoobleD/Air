#ifndef _FINGERS_LISTENER_HPP_
#define _FINGERS_LISTENER_HPP_

#include "OS/Screen.hpp"
#include "MouseControl.hpp"

#include "XnFingersGenerator.hpp"


namespace air
{
  
  class					FingersListener
  {
  private:
    
    static os::Screen			m_screen;
    static MouseControl			m_mouseControl;

    static void				showDebug(xn::FingersData * fingersData);
    static void				drawAllFingers(xn::FingersData * fingersData);
    static void				toScreenCoord(xn::FingersData * fingersData);

  public:

    static void XN_CALLBACK_TYPE	FingersCreate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData);
    
    static void XN_CALLBACK_TYPE	FingersUpdate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData);

    static void XN_CALLBACK_TYPE	FingersDestroy(xn::FingersGenerator & gen,
						       XnUserID id, 
						       XnFloat time,
						       void * userData);
  };

}

#endif //_FINGERS_LISTENER_HPP_
