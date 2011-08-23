#ifndef _E_KILL_CURRENT_HPP_
#define _E_KILL_CURRENT_HPP_


// NITE header
#include <XnVPushDetector.h>

#include "OS/Keyboard.hpp"


// Required minimum movement speed
#define KC_MIN_SPEED			0.65f


namespace air
{

  /**
   * Event class. Associate push gesture to the action
   * of closing the running application which has the focus.
   * Inherit from XnVPushDetector, since it must detect push gestures.
   *
   * @author Pierre Alletru
   */
  class					E_KillCurrent : public XnVPushDetector
  {
  private:

    // A keyboard object, used to send keyboard events to OS.
    static os::Keyboard			m_kb;
    
  public:

    /**
     * Default constructor.
     */
    E_KillCurrent(void);

    /**
     * Destructor.
     */
    ~E_KillCurrent(void);
    
    /**
     * OpenNI callback called when a push gesture is recognized.
     * Perform an 'Alt + F4' keyboard event to kill current application.
     *
     * @param velocity			Velocity of the push movement.
     * @param angle			The angle of the movement, with respect to
     *					the Z axis (depth).
     * @param userCxt			A pointer to some user data. Required 
     *					by OpenNI, but always NULL in this case.
     */
    static void XN_CALLBACK_TYPE	onPush(XnFloat velocity, 
					       XnFloat angle, 
					       void *userCxt);
  };
  
}

#endif //_E_KILL_CURRENT_HPP_
