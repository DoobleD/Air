#ifndef _MOUSE_CONTROL_HPP_
#define _MOUSE_CONTROL_HPP_


#include <SFML/System.hpp>

#include "XnFingerTypes.hpp"

#include "OS/Mouse.hpp"
#include "OS/Screen.hpp"

// Maximum number of fingers for mouse gestures
#define	REQUIRED_MAX_FINGERS	2

// Max time (in seconds) between two clicks for a double click
#define DOUBLE_CLICK_TIME	0.5 

// Min time (in seconds) required with the pointer gesture to enter pointer mode 
#define POINTER_GESTURE_TIME	2 

// Modes
#define MODE_NONE		0
#define MODE_POINTER		1
#define MODE_PRESSED		2
#define MODE_RELEASED		3
#define MODE_SCROLL		4


namespace air
{
  class			MouseControl
  {
  private:
    char		m_mode;

    os::Mouse		m_mouse;
    os::Screen &	m_screen;
    
    XnPoint3D		m_scrollPos;

    sf::Clock		m_buttonPressed;
    sf::Clock		m_pointerRequested;

    bool		m_pointerIsRequested;

    static Color	LeftButtonColor;
    static Color	RightButtonColor;

    bool		isReset(const xn::FingersData & fingersData);
    bool		isButtonPress(const xn::FingersData & fingersData);
    bool		isButtonRelease(const xn::FingersData & fingersData);
    bool		isPointer(const xn::FingersData & fingersData);

    void		buttonPress(const xn::FingersData & fingersData);
    void		buttonRelease(const xn::FingersData & fingersData);
    void		pointer(const xn::FingersData & fingersData);
    void		reset(void);

  public:
    MouseControl(os::Screen & screen);
    ~MouseControl(void);

    bool		update(const xn::FingersData & fingersData);
  };
}

#endif //_MOUSE_CONTROL_HPP_
