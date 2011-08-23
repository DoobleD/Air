#ifndef _EVENT_LISTENER_HPP_
#define _EVENT_LISTENER_HPP_


// NITE header
#include <XnVMessageListener.h>


namespace air
{

  /**
   * Holds a pointer to a XnVMessageListener object.
   * Any class inheriting from XnVMessageListener is an event class.
   *
   * The structure is used (mainly in globals.cpp) to define a global array
   * of all the NITE event liseteners (e.g E_ShowDesktop, E_SwitchApp, ...).
   *
   * @author Pierre Alletru
   */
  struct			EventListener
  {
    // A pointer to an event lisetener, which must inherit from XnVMessageListener.
    // This is required since XnVMessageListener is the base class of all NITE's
    // gestures recognition classes.
    XnVMessageListener *	listener;
  };

}

#endif //_EVENT_LISTENER_HPP_
