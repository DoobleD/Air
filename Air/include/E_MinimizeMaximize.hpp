#ifndef _E_MINIMIZE_MAXIMIZE_HPP_
#define _E_MINIMIZE_MAXIMIZE_HPP_


// NITE header
#include <XnVSwipeDetector.h>

#include "OS/Keyboard.hpp"


// Required minimum movement speed
#define MM_MIN_SPEED			1.15 // m/s


namespace air
{

  /**
   * Event class. Associate up/down swipe gesture to the action
   * of minimizing/maximizing the running application which has the focus.
   * Inherit from XnVSwipeDetector, since it must detect swipe gestures.
   *
   * @author Pierre Alletru
   */
  class					E_MinimizeMaximize : public XnVSwipeDetector
  {
  private:

    // A keyboard object, used to send keyboard events to OS.
    static os::Keyboard			m_kb;

  public:

    /**
     * Default constructor.
     */
    E_MinimizeMaximize(void);

    /**
     * Destructor.
     */
    ~E_MinimizeMaximize(void);
    
    /**
     * OpenNI callback called when a swipe up gesture is recognized.
     * Perform a keyboard event to maximize current application.
     *
     * @param velocity			Velocity of the swipe movement.
     * @param angle			The angle of the movement, with respect to
     *					the Y axis (vertical).
     * @param userCxt			A pointer to some user data. Required 
     *					by OpenNI, but always NULL in this case.
     */
    static void XN_CALLBACK_TYPE	onSwipeUp(XnFloat velocity, 
						  XnFloat angle, 
						  void *userCxt);

    /**
     * OpenNI callback called when a swipe down gesture is recognized.
     * Perform a keyboard event to minimize current application.
     *
     * @param velocity			Velocity of the swipe movement.
     * @param angle			The angle of the movement, with respect to
     *					the Y axis (vertical).
     * @param userCxt			A pointer to some user data. Required 
     *					by OpenNI, but always NULL in this case.
     */
    static void XN_CALLBACK_TYPE	onSwipeDown(XnFloat velocity, 
						    XnFloat angle, 
						    void *userCxt);
  };

}

#endif //_E_MINIMIZE_MAXIMIZE_HPP_
