#include "MouseControl.hpp"

#include "XnMath.hpp"


using namespace air;


MouseControl::MouseControl(os::Screen & screen) : m_screen(screen)
{
}

MouseControl::~MouseControl(void)
{
}

bool		MouseControl::isAMouseMode(xn::FingersData & fingersData)
{
  return fingersData.Size <= REQUIRED_MAX_FINGERS;
}

void		MouseControl::resetMode(void)
{
  m_mode = MODE_NONE;
}

void		MouseControl::update(xn::FingersData & fingersData)
{
  Color		leftButtonColor = Color::Green;
  Color		rightButtonColor = Color::Red;
  
  if (fingersData.Size == 0)
    {
      //      m_mouse.wheelDown();
      if (m_mode == MODE_POINTER)
	{
	  printf("Press!\n");
	  m_mode = MODE_PRESSED;
	  m_mouse.leftButtonPress();
	}
      // else if (m_mode == MODE_SCROLL)
      // 	{
      // 	  if (fingersData.Hand.Y > m_scrollPos.Y)
      // 	    printf("Scroll down\n");
      // 	  else
      // 	    printf("Scroll up\n");
      // 	  m_scrollPos = fingersData.Hand;
      // 	}
      // else if (m_mode == MODE_POINTER)
      // 	{
      // 	  printf("Scroll on\n");
      // 	  m_mode = MODE_SCROLL;
      // 	  m_scrollPos = fingersData.Hand;
      // 	}
    }
  else if (fingersData.Size == 1)
    {
      if (m_mode == MODE_NONE)
	{
	  printf("MODE POINTER!!\n");
	  m_mode = MODE_POINTER;
	}
      else if (m_mode == MODE_PRESSED)
	{
	  printf("Release!\n");
	  m_mode = MODE_POINTER;
	  m_mouse.leftButtonRelease();
	}

      m_mouse.setPosition(fingersData.Fingers[0].X, fingersData.Fingers[0].Y); 
      m_screen.drawRectangle(fingersData.Fingers[0].X, 
			     fingersData.Fingers[0].Y, 20, 20, leftButtonColor);
    }
  else if (fingersData.Size == 2)
    {
      XnPoint3D		finger1 = fingersData.Fingers[0];
      XnPoint3D		finger2 = fingersData.Fingers[1];
      
      if (finger1.X < finger2.X)
	{
	  m_screen.drawRectangle(finger1.X, finger1.Y, 20, 20, rightButtonColor);
	  m_screen.drawRectangle(finger2.X, finger2.Y, 20, 20, leftButtonColor);
	}
      else
	{
	  m_screen.drawRectangle(finger1.X, finger1.Y, 20, 20, leftButtonColor);
	  m_screen.drawRectangle(finger2.X, finger2.Y, 20, 20, rightButtonColor);
	}
    }
}
