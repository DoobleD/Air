#ifndef _E_SWITCH_TAB_HPP_
#define _E_SWITCH_TAB_HPP_


// NITE header
#include <XnVSwipeDetector.h>

#include "OS/Keyboard.hpp"


// Required minimum movement speed
#define ST_MIN_SPEED			1.35 // m/s


namespace air
{

  /**
   * Event class. Associate left/right swipe gesture to the action
   * of switching between the current running applications.
   * Inherit from XnVSwipeDetector, since it must detect swipe gestures.
   *
   * @author Pierre Alletru
   */
  class					E_SwitchTab : public XnVSwipeDetector
  {
  private:

    // A keyboard object, used to send keyboard events to OS.
    static os::Keyboard			m_kb;

  public:
    
    /**
     * Default constructor.
     */
    E_SwitchTab(void);
    
    /**
     * Destructor.
     */
    ~E_SwitchTab(void);

    /**
     * OpenNI callback called when a swipe left or swipe right gesture is recognized.
     * Perform an 'Alt + Tab' keyboard event to switch current applications.
     *
     * @param velocity			Velocity of the swipe movement.
     * @param angle			The angle of the movement, with respect to
     *					the X axis (horizontal).
     * @param userCxt			A pointer to some user data. Required 
     *					by OpenNI, but always NULL in this case.
     */    
    static void XN_CALLBACK_TYPE	onSwipe(XnFloat velocity, 
						XnFloat angle, 
						void *userCxt);
  };

}

#endif //_E_SWITCH_TAB_HPP_
