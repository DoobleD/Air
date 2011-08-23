#ifndef _FINGERS_LISTENER_HPP_
#define _FINGERS_LISTENER_HPP_


#include "XnFingersGenerator.hpp"

#include "MouseControl.hpp"
#include "OS/Screen.hpp"


namespace air
{
  
  /**
   * Handle the fingers related callbacks, which are called by xn::FingersGenerator.
   * Transmitt fingers data to a MouseControl object, since fingers are 
   * controlling mouse. If no mouse action is recognized, simply display fingers 
   * positions above screen.
   *
   * @author Pierre Alletru
   */
  class					FingersListener
  {
  private:
    
    // A screen object used to draw fingers on screen.
    static os::Screen			m_screen;
    // The MouseControl object recognizing fingers gestures and perform mouse actions.
    static MouseControl			m_mouseControl;

    /**
     * Called only if DEBUG_MOD is defined. Draw circles on debug screen where 
     * detected finger tips are located, and where the hand palm is located.
     *
     * @param fingersData		A pointer to a structure containing fingers
     *					information.
     */
    static void				showDebug(xn::FingersData * fingersData);

    /**
     * Draw rectangles above OS screen where detected finger tips are located, 
     * and where the hand palm is located.
     *
     * @param fingersData		A pointer to a structure containing fingers
     *					information.
     */
    static void				drawHandToScreen(xn::FingersData * fingersData);

    /**
     * Converts real world finger coordinates in the given FingersData structure, to
     * their corresponding coordinates on OS screen.
     *
     * @param fingersData		A pointer to a structure containing fingers
     *					information.
     */
    static void				toScreenCoord(xn::FingersData * fingersData);

  public:

    /**
     * xn::FingersGenerator callback called when a hand and its fingers has been
     * detected for the first time in the session. Does no action.
     *
     * @param gen			A reference to the FingersGenerator object
     *					which has detected the hand and generated 
     *					the given data.
     * @param id			The hand id.
     * @param fingersData		A pointer to a structure containing hand and 
     *					fingers information.
     * @param time			A timestamp, in seconds.
     * @param userData			A pointer to some undefined data. 
     *					Not used here (is equal to NULL).
     */
    static void XN_CALLBACK_TYPE	FingersCreate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData);
    
    /**
     * xn::FingersGenerator callback called every frame while a hand and its fingers
     * are still detected, indicating hand and fingers positions and 
     * related information. 
     * Essentially transmitt data to the MouseControl object member, and
     * draw fingers on OS screen if MouseControl doesn't recognize any fingers gesture.
     *
     * @param gen			A reference to the FingersGenerator object
     *					which has detected the hand and generated 
     *					the given data.
     * @param id			The hand id.
     * @param fingersData		A pointer to a structure containing hand and 
     *					fingers information.
     * @param time			A timestamp, in seconds.
     * @param userData			A pointer to some undefined data. 
     *					Not used here (is equal to NULL).
     */
    static void XN_CALLBACK_TYPE	FingersUpdate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData);

    /**
     * xn::FingersGenerator callback called when a hand is lost 
     * (is no longer detected).
     *
     * @param gen			A reference to the FingersGenerator object
     *					which has pereviously detected the hand.
     * @param id			The hand id.
     * @param time			A timestamp, in seconds.
     * @param userData			A pointer to some undefined data. 
     *					Not used here (is equal to NULL).
     */
    static void XN_CALLBACK_TYPE	FingersDestroy(xn::FingersGenerator & gen,
						       XnUserID id, 
						       XnFloat time,
						       void * userData);
  };

}

#endif //_FINGERS_LISTENER_HPP_
