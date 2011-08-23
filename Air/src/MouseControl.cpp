#include "MouseControl.hpp"
#include "CoordConverter.hpp"

#include "XnMath.hpp"


using namespace air;


const Color &		MouseControl::LeftButtonColor = Color::Yellow;
const Color &		MouseControl::RightButtonColor = Color::Red;


MouseControl::MouseControl(os::Screen & screen) : m_screen(screen), 
						  m_pointerIsRequested(false),
						  m_switchIsRequested(false),
						  m_grabIsRequested(false),
						  m_scrollIsRequested(false),
						  m_pointerIsOut(false),
						  m_currentButton(BUTTON_LEFT),
						  m_mode(MODE_NONE)
{
}

MouseControl::~MouseControl(void)
{
}

bool		MouseControl::isButtonPress(const xn::FingersData & fingersData)
{
  return fingersData.Size == 0 && m_mode == MODE_POINTER;
}

bool		MouseControl::isButtonRelease(const xn::FingersData & fingersData)
{
  return fingersData.Size == 1 && m_mode == MODE_PRESSED;
}

bool		MouseControl::isSwitchButton(const xn::FingersData & fingersData)
{
  return fingersData.Size == 2 && m_mode == MODE_POINTER;
}

bool		MouseControl::isGrab(const xn::FingersData & fingersData)
{
  return fingersData.Size == 0 && m_mode == MODE_PRESSED;
}

bool		MouseControl::isScroll(const xn::FingersData & fingersData)
{
  return (fingersData.Size == 0 && m_mode == MODE_NONE) || m_mode == MODE_SCROLL;
}

bool		MouseControl::isPointer(const xn::FingersData & fingersData)
{
  // Already in pointer mode
  if (m_mode == MODE_POINTER)
    return true;

  // Pointer gesture
  if (fingersData.Size == 1)
    {
      // Start pointer request
      if (!m_pointerIsRequested)
	{
	  m_pointerIsRequested = true;
	  m_pointerRequested.Reset();
	} // Pointer gesture for a few seconds, enter pointer mode
      else if (m_pointerRequested.GetElapsedTime() > POINTER_GESTURE_TIME)
	{
	  return true;
	}
    }

  return false;
}

bool		MouseControl::isReset(const xn::FingersData & fingersData)
{
  return fingersData.Size > REQUIRED_MAX_FINGERS || 
    (fingersData.Size == REQUIRED_MAX_FINGERS && m_mode != MODE_POINTER);
}

void		MouseControl::switchButton(void)
{
  if (!m_switchIsRequested)
    {
      m_switchIsRequested = true;
      m_switchRequested.Reset();
    }
  else if (m_switchRequested.GetElapsedTime() > SWITCH_GESTURE_TIME)
    {
      if (m_currentButton == BUTTON_LEFT)
	m_currentButton = BUTTON_RIGHT;
      else
	m_currentButton = BUTTON_LEFT;
      
      m_switchIsRequested = false;
    }
}

void		MouseControl::buttonPress(void)
{
  if (m_currentButton == BUTTON_LEFT && 
      m_buttonPressed.GetElapsedTime() <= DOUBLE_CLICK_TIME)
    {
      // Perform double click
      m_mouse.leftButtonPress();  
      m_mouse.leftButtonRelease();
      
      m_mouse.leftButtonPress();  
      m_mouse.leftButtonRelease();
    }
  else
    {
      if (m_currentButton == BUTTON_LEFT)
	m_mouse.leftButtonPress();
      else
	m_mouse.rightButtonPress();
    }

  m_mode = MODE_PRESSED;  
  m_buttonPressed.Reset();
}

void		MouseControl::buttonRelease(void)
{
  if (m_currentButton == BUTTON_LEFT)
    m_mouse.leftButtonRelease();
  else
    m_mouse.rightButtonRelease();

  m_grabIsRequested = false;
  
  m_currentButton = BUTTON_LEFT;

  m_mode = MODE_RELEASED; // Useless for now, but could serve later
}

void		MouseControl::grab(const XnPoint3D & pointer)
{
  if (!m_grabIsRequested)
    {
      m_grabIsRequested = true;
      m_grabRequested.Reset();
    }
  else if (m_grabRequested.GetElapsedTime() > GRAB_GESTURE_TIME)
    {
      m_mouse.setPosition(pointer.X, pointer.Y);      
    }
}

void		MouseControl::scroll(const XnPoint3D & pointer)
{
  if (!m_scrollIsRequested)
    {
      m_scrollIsRequested = true;
      m_scrollRequested.Reset();
    }
  else if (m_scrollRequested.GetElapsedTime() > SCROLL_GESTURE_TIME)
    {
      m_mouse.setPosition(pointer.X, pointer.Y);
      
      if (m_mode == MODE_NONE)
	{
	  m_mouse.middleButtonPress();
	  
	  m_mode = MODE_SCROLL;
	}
    }
}

void		MouseControl::pointer(XnPoint3D * pointer)
{
  static int	marginMaxX = m_screen.getResX() - POINTER_OUT_MARGIN;
  static int	marginMaxY = m_screen.getResY() - POINTER_OUT_MARGIN;

  if (pointer)
    {
      // *pointer = CoordConverter::screenSizeToSpeedFactor(*pointer, 
      // 							 SPEED_UP_POINTER_FACTOR);
      
      if (pointer->X >= POINTER_OUT_MARGIN && pointer->Y <= marginMaxX &&
      	  pointer->Y >= POINTER_OUT_MARGIN && pointer->Y <= marginMaxY)
      	{
	  m_mouse.setPosition(pointer->X + 10, pointer->Y + 10); 
	  
	  if (m_currentButton == BUTTON_LEFT)
	    m_screen.drawRectangle(pointer->X, pointer->Y, 20, 20, LeftButtonColor);
	  else
	    m_screen.drawRectangle(pointer->X, pointer->Y, 20, 20, RightButtonColor);
	  
	  m_pointerIsOut = false;
      	}
      else
      	m_pointerIsOut = true;
    }
  
  m_mode = MODE_POINTER;
}

void		MouseControl::reset(void)
{
  // Reset all requests
  m_pointerIsRequested = false;
  m_switchIsRequested = false;
  m_scrollIsRequested = false;
  m_grabIsRequested = false;

  // No more pointer, so it can't be out
  m_pointerIsOut = false;
      
  // Reset actual mouse clicks
  m_mouse.middleButtonRelease();
  if (m_mode == MODE_PRESSED)
    {
      if (m_currentButton == BUTTON_LEFT)
	m_mouse.leftButtonRelease();
      else
	m_mouse.rightButtonRelease();
    }
  
  // Reset to left button
  m_currentButton = BUTTON_LEFT;
  
  // Reset mode
  m_mode = MODE_NONE;
}

XnPoint3D *	MouseControl::getPointer(const xn::FingersData & fingersData)
{
  if (fingersData.Size == 1)
    return &fingersData.Fingers[0];
  
  if (fingersData.Size == 2)
    {
      XnPoint3D	*	p1 = &fingersData.Fingers[0];
      XnPoint3D	*	p2 = &fingersData.Fingers[1];
      
      xn::Point2Df	f1(p1->X, p1->Y);
      xn::Point2Df	f2(p2->X, p2->Y);
      xn::Point2Df	h(fingersData.Hand.X, fingersData.Hand.Y);
 
      if (xn::math::PointsDistance(h, f1) < xn::math::PointsDistance(h, f2))
	return p2;
      else
	return p1;
    }
  
  return NULL;
}

bool		MouseControl::update(const xn::FingersData & fingersData)
{
  bool		isSwitch = false;

  if (isReset(fingersData))
    {
      reset();
      return false;
    }

  if (isScroll(fingersData))
    {
      scroll(fingersData.Hand);
    }

  if (!m_pointerIsOut)
    {
      if (isSwitchButton(fingersData))
	{
	  isSwitch = true;
	  switchButton();
	}
      else if (isButtonPress(fingersData))
	{
	  buttonPress();
	}
      else if (isGrab(fingersData))
	{
	  grab(fingersData.Hand);
	}
    }
      
  if (isPointer(fingersData))
    {
      if (!isSwitch)
	m_switchIsRequested = false;
      
      if (isButtonRelease(fingersData))
	buttonRelease();
      
      pointer(getPointer(fingersData));
    }

  return true;
}
