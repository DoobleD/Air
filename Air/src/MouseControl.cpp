#include "MouseControl.hpp"

#include "XnMath.hpp"


using namespace air;


Color		MouseControl::LeftButtonColor = Color::Yellow;
Color		MouseControl::RightButtonColor = Color::Red;


MouseControl::MouseControl(os::Screen & screen) : m_screen(screen), 
						  m_pointerIsRequested(false),
						  m_switchIsRequested(false),
						  m_grabIsRequested(false),
						  m_currentButton(BUTTON_LEFT),
						  m_mode(MODE_NONE),
						  m_resetRequested(0)
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

bool		MouseControl::isPointer(const xn::FingersData & fingersData)
{
  if (m_pointerIsRequested)
    printf("true\n");
  else
    printf("false\n");
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
  return fingersData.Size > REQUIRED_MAX_FINGERS;
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
      printf("SWITCH BUTTON\n");
      
      if (m_currentButton == BUTTON_LEFT)
	m_currentButton = BUTTON_RIGHT;
      else
	m_currentButton = BUTTON_LEFT;
      
      m_switchIsRequested = false;
    }
}

void		MouseControl::buttonPress(void)
{
  printf("Press!\n");
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
  printf("Release!\n");

  if (m_currentButton == BUTTON_LEFT)
    m_mouse.leftButtonRelease();
  else
    m_mouse.rightButtonRelease();

  m_grabIsRequested = false;
  
  m_currentButton = BUTTON_LEFT;

  m_mode = MODE_RELEASED; // Useless for now, but could serve later
}

void		MouseControl::grab(const xn::FingersData & fingersData)
{
  if (!m_grabIsRequested)
    {
      m_grabIsRequested = true;
      m_grabRequested.Reset();
    }
  else if (m_grabRequested.GetElapsedTime() > GRAB_GESTURE_TIME)
    {
      m_mouse.setPosition(fingersData.Hand.X, fingersData.Hand.Y);      
    }
}

void		MouseControl::pointer(XnPoint3D * pointer)
{
  Color		buttonColor;

  printf("MODE POINTER!\n");

  m_mouse.setPosition(pointer->X, pointer->Y); 

  if (m_currentButton == BUTTON_LEFT)
    buttonColor = LeftButtonColor;
  else
    buttonColor = RightButtonColor;

  m_screen.drawRectangle(pointer->X, pointer->Y, 20, 20, buttonColor);

  m_mode = MODE_POINTER;
}

bool		MouseControl::reset(void)
{
  if (m_mode == MODE_NONE)
    {
      m_pointerIsRequested = false;
      return true;
    }

  if (m_resetRequested > RESET_GESTURE_FRAMES)
    {
      m_resetRequested = 0;
      m_pointerIsRequested = false;
      m_switchIsRequested = false;
      
      m_currentButton = BUTTON_LEFT;
      
      m_mode = MODE_NONE;

      return true;
    }
  
  m_resetRequested++;

  return false;
}

void		MouseControl::resetSwitch(void)
{
  m_switchIsRequested = false;
}

XnPoint3D *	MouseControl::getPointer(const xn::FingersData & fingersData)
{
  if (fingersData.Size == 1)
    return &fingersData.Fingers[0];
  
  if (fingersData.Size == 2)
    {
      XnPoint3D	*	p1 = &fingersData.Fingers[0];
      XnPoint3D	*	p2 = &fingersData.Fingers[1];

      return (p1->X < p2->X ? p2 : p1);
    }
  
  return NULL;
}

bool		MouseControl::update(const xn::FingersData & fingersData)
{
  bool		isSwitch = false;

  if (isReset(fingersData))
    {
      return !reset();
    }
  
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
      grab(fingersData);
    }

  if (isPointer(fingersData))
    {
      if (!isSwitch)
	resetSwitch();

      if (isButtonRelease(fingersData))
	buttonRelease();
      
      pointer(getPointer(fingersData));
    }

  return true;
}
