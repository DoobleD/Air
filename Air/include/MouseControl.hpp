#ifndef _MOUSE_CONTROL_HPP_
#define _MOUSE_CONTROL_HPP_


#include <SFML/System.hpp>

#include "XnFingerTypes.hpp"

#include "OS/Mouse.hpp"
#include "OS/Screen.hpp"


// Maximum number of fingers possible to have a mouse gesture.
#define	REQUIRED_MAX_FINGERS	2

// Maximum time (in seconds) between two clicks for a double click.
#define DOUBLE_CLICK_TIME	0.5

// Minimum time (either in seconds or frames) required to gestures 
// before processing it.
#define POINTER_GESTURE_TIME	2
#define SWITCH_GESTURE_TIME	0.5
#define GRAB_GESTURE_TIME	1
#define SCROLL_GESTURE_TIME	1

// Button defines.
#define BUTTON_LEFT		0
#define BUTTON_RIGHT		1

// Screen margin after which pointer is recognized.
#define POINTER_OUT_MARGIN	0

// Factor used to speed pointer movement.
#define SPEED_UP_POINTER_FACTOR	1.25

// Modes. A mode states which is the current action performed.
#define MODE_NONE		0
#define MODE_POINTER		1
#define MODE_PRESSED		2
#define MODE_RELEASED		3
#define MODE_SCROLL		4


namespace air
{

  /**
   * Search for hand and fingers gesture corresponding to mouse actions,
   * and process it if found any. Should always be instantiated as a static object
   * since the behavior of most gestures depends to previous gestures performed.
   *
   * @author Pierre Alletru
   */
  class				MouseControl
  {
  private:
    
    // The current mode. States the current action performed.
    char			m_mode;

    // Mouse and Screen object used to draw on OS screen and perform mouse actions.
    // Screen object comes from another object : MouseControl may add shapes to
    // draw on screen, but does not actually displays it or clear screen.
    os::Mouse			m_mouse;
    os::Screen &		m_screen;
    
    // Timers used to know for how long a gesture has been performed. Needed
    // to avoid undesired mixed behaviour.
    sf::Clock			m_buttonPressed;
    sf::Clock			m_pointerRequested;
    sf::Clock			m_switchRequested;
    sf::Clock			m_grabRequested;
    sf::Clock			m_scrollRequested;

    // State wheter or not the pointer is out of the detection area 
    // (see POINTER_OUT_MARGIN).
    bool			m_pointerIsOut;

    // States if some actions are "requested" (means, the corresponding gestures has
    // been recognized).
    bool			m_pointerIsRequested;
    bool			m_switchIsRequested;
    bool			m_grabIsRequested;
    bool			m_scrollIsRequested;

    // The current mouse button selected (see defines above).
    char			m_currentButton;

    // The colors to use when adding a shape to screen, depending of
    // which is the current mouse button used.
    static const Color & 	LeftButtonColor;
    static const Color &	RightButtonColor;
    
    /**
     * Search for a reset gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isReset(const xn::FingersData & fingersData);

    /**
     * Search for a button press gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isButtonPress(const xn::FingersData & fingersData);

    /**
     * Search for a button release gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isButtonRelease(const xn::FingersData & fingersData);

    /**
     * Search for a reset gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isSwitchButton(const xn::FingersData & fingersData);

    /**
     * Search for a pointer gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isPointer(const xn::FingersData & fingersData);

    /**
     * Search for a grab gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isGrab(const xn::FingersData & fingersData);

    /**
     * Search for a scroll gesture.
     *
     * @param fingersData	A pointer to a structure containing information
     *				about hand and fingers.
     *
     * @return true if the gesture is found, false otherwise.
     */
    bool			isScroll(const xn::FingersData & fingersData);

    /**
     * Perform a button press action, depending on which is the 
     * current button selected. 
     */
    void			buttonPress(void);

    /**
     * Perform a button release action.
     */
    void			buttonRelease(void);

    /**
     * Perform a swicth button action. Changes the current button selected.
     */
    void			switchButton(void);

    /**
     * Perform a grab action. Equivalent to hold a button pressed and move the mouse.
     *
     * @param pointer		The position of the pointer.
     */
    void			grab(const XnPoint3D & pointer);

    /**
     * Perform a scroll action. Equivalent to hold the middle button (the wheel) 
     * pressed and move the mouse.
     *
     * @param pointer		The position of the pointer.
     */
    void			scroll(const XnPoint3D & pointer);

    /**
     * Perform a 'pointer action'. Essentially moves the mouse at the given position.
     *
     * @param pointer		A pointer to the position of the pointer.
     */
    void			pointer(XnPoint3D * pointer);

    /**
     * Reset all internal states and reset to the default mode (MODE_NONE).
     */
    void			reset(void);

    /**
     * Get the pointer position. The pointer chosen is the farest finger from the palm.
     * In the most suitable case, using both index and thumb, this is the index.
     *
     * @param fingersData	A reference to a structure containing information
     *				about hand and fingers.
     *
     * @return A pointer to the (finger) pointer.
     */
    XnPoint3D *			getPointer(const xn::FingersData & fingersData);

  public:

    /**
     * Constructor.
     *
     * @param screen		A reference to a Screen object, used to add shapes to
     *				screen, mainly to indicate pointer position.
     */
    MouseControl(os::Screen & screen);

    /**
     * Destructor.
     */
    ~MouseControl(void);

    /**
     * Interpret fingers gestures. Should be called every frame.
     *
     * @param fingersData	A reference to a structure containing information
     *				about hand and fingers.
     *
     * @return true if a gesture has been recognized and interpreted, false otherwise.
     */
    bool			update(const xn::FingersData & fingersData);
  };
}

#endif //_MOUSE_CONTROL_HPP_
