#ifndef _E_SHOW_DESKTOP_HPP_
#define _E_SHOW_DESKTOP_HPP_

// NITE header
#include <XnVCircleDetector.h>

#include "OS/Keyboard.hpp"


// Required minimun radius of the circle detected.
#define SD_MIN_RADIUS			60
// Required minimum time elpased between two circle gestures.
// Avoid abusive succesive show desktop actions.
#define SD_MIN_TIME			1


namespace air
{

  /**
   * Event class. Associate circle gesture to the action
   * of show desktop/restore windows (Super + D keyboard event).
   * Inherit from XnVCircleDetector, since it must detect circle gestures.
   *
   * @author Pierre Alletru
   */
  class					E_ShowDesktop : public XnVCircleDetector
  {
  private:

    // A keyboard object, used to send keyboard events to OS.
    static os::Keyboard			m_kb;
    
  public:

    /**
     * Default constructor.
     */
    E_ShowDesktop(void);

    /**
     * Destructor.
     */
    ~E_ShowDesktop(void);
    
    /**
     * OpenNI callback called when a circle gesture is recognized.
     * Perform a 'Super + D' keyboard event to show desktop/restore windows.
     *
     * @param times			The number of times a circle has been detected.
     * @param confident			Indicate wheter or not the detection is
     *					confident.
     * @param circle			A pointer to a structure containing some
     *					information on the circle detected.
     * @param userCxt			A pointer to some user data. Required 
     *					by OpenNI, but always NULL in this case.
     */
    static void XN_CALLBACK_TYPE	onCircle(XnFloat times, 
						 XnBool confident,
						 const XnVCircle * circle, 
						 void * userCxt);
  };
  
}

#endif //_E_SHOW_DESKTOP_HPP_
