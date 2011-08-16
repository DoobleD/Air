#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif

#include "FingersListener.hpp"
#include "CoordConverter.hpp"


using namespace air;


os::Screen		FingersListener::m_screen;
MouseControl		FingersListener::m_mouseControl(m_screen);


void			FingersListener::showDebug(xn::FingersData * fingersData)
{
  XnPoint3D		point;

  for (int i = 0; i < fingersData->Size; i++)
    {
      point = CoordConverter::realWorldToNIScreen(fingersData->Fingers[i]);
      g_viewer.addDisc(point.X, point.Y, 20, Color::Red);
    }

  point = CoordConverter::realWorldToNIScreen(fingersData->Hand);
  g_viewer.addDisc(point.X, point.Y, 40, Color::Red);
}

void			FingersListener::drawHandToScreen(xn::FingersData * fingersData)
{
  XnPoint3D		point;

  for (int i = 0; i < fingersData->Size; i++)
    {
      m_screen.drawRectangle(fingersData->Fingers[i].X, fingersData->Fingers[i].Y, 
			     20, 20, Color::Blue);
    }
  
  m_screen.drawRectangle(fingersData->Hand.X, fingersData->Hand.Y, 
			 40, 40, Color::Blue);
}

void			FingersListener::toScreenCoord(xn::FingersData * fingersData)
{
  for (int i = 0; i < fingersData->Size; i++)
    {
      fingersData->Fingers[i] = 
	CoordConverter::realWorldToScreenSize(fingersData->Fingers[i]);
    }
  fingersData->Hand = CoordConverter::realWorldToScreenSize(fingersData->Hand);
}

void XN_CALLBACK_TYPE	FingersListener::FingersUpdate(xn::FingersGenerator & gen,
						       XnUserID id, 
						       xn::FingersData * fingersData,
						       XnFloat time, 
						       void * userData)
{
#ifdef DEBUG_MOD
  showDebug(fingersData);
#endif

  toScreenCoord(fingersData);
  
  m_screen.clear();
  
  if (!m_mouseControl.update(*fingersData))
    {
      drawHandToScreen(fingersData);
    }

  m_screen.display();  
}

void XN_CALLBACK_TYPE	FingersListener::FingersCreate(xn::FingersGenerator & gen,
						       XnUserID id, 
						       xn::FingersData * fingersData,
						       XnFloat time, 
						       void * userData)
{
}

void XN_CALLBACK_TYPE	FingersListener::FingersDestroy(xn::FingersGenerator & gen,
							XnUserID id, 
							XnFloat time,
							void * userData)
{
}
