#include "MouseControl.hpp"

#include "XnMath.hpp"


using namespace air;


Color		MouseControl::LeftButtonColor = Color::Yellow;
Color		MouseControl::RightButtonColor = Color::Red;


MouseControl::MouseControl(os::Screen & screen) : m_screen(screen), 
						  m_pointerIsRequested(false)
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

bool		MouseControl::isPointer(const xn::FingersData & fingersData)
{
  // Already in pointer mode
  if (m_mode == MODE_POINTER && m_pointerIsRequested)
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

void		MouseControl::buttonPress(const xn::FingersData & fingersData)
{
  printf("Press!\n");
  if (m_buttonPressed.GetElapsedTime() <= DOUBLE_CLICK_TIME)
    {
      // Perform double click
      m_mouse.leftButtonPress();  
      m_mouse.leftButtonRelease();
      
      m_mouse.leftButtonPress();  
      m_mouse.leftButtonRelease();
    }
  else
    {
      m_mouse.leftButtonPress();
    }

  m_mode = MODE_PRESSED;  
  m_buttonPressed.Reset();
}

void		MouseControl::buttonRelease(const xn::FingersData & fingersData)
{
  printf("Release!\n");
  m_mouse.leftButtonRelease();

  m_mode = MODE_RELEASED; // Useless for now, but could serve later
}

void		MouseControl::pointer(const xn::FingersData & fingersData)
{
  printf("MODE POINTER!\n");

  m_mouse.setPosition(fingersData.Fingers[0].X, fingersData.Fingers[0].Y); 
  m_screen.drawRectangle(fingersData.Fingers[0].X, 
			 fingersData.Fingers[0].Y, 20, 20, LeftButtonColor);

  m_mode = MODE_POINTER;
}

void		MouseControl::reset(void)
{
  m_pointerIsRequested = false;

  m_mode = MODE_NONE;
}

// void		MouseControl::update_2Fingers(const xn::FingersData & fingersData)
// {
//   XnPoint3D	finger1 = fingersData.Fingers[0];
//   XnPoint3D	finger2 = fingersData.Fingers[1];
  
//   if (finger1.X < finger2.X)
//     {
//       m_screen.drawRectangle(finger1.X, finger1.Y, 20, 20, RightButtonColor);
//       m_screen.drawRectangle(finger2.X, finger2.Y, 20, 20, LeftButtonColor);
//     }
//   else
//     {
//       m_screen.drawRectangle(finger1.X, finger1.Y, 20, 20, LeftButtonColor);
//       m_screen.drawRectangle(finger2.X, finger2.Y, 20, 20, RightButtonColor);
//     }
// }

bool		MouseControl::update(const xn::FingersData & fingersData)
{
  if (isReset(fingersData))
    {
      reset();
      return false;
    }
  else if (isButtonPress(fingersData))
    {
      buttonPress(fingersData);
    }
  else if (isPointer(fingersData))
    {
      if (isButtonRelease(fingersData))
	buttonRelease(fingersData);
      
      pointer(fingersData);
    }

  return true;
}
