#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif

#include "FingersListener.hpp"
#include "CoordConverter.hpp"


using namespace air;


MouseControl		FingersListener::m_mouseControl;
os::Screen		FingersListener::m_screen;


void XN_CALLBACK_TYPE	FingersListener::FingersCreate(xn::FingersGenerator & gen,
						       XnUserID id, 
						       xn::FingersData * fingersData,
						       XnFloat time, 
						       void * userData)
{
}

void XN_CALLBACK_TYPE	FingersListener::FingersUpdate(xn::FingersGenerator & gen,
						       XnUserID id, 
						       xn::FingersData * fingersData,
						       XnFloat time, 
						       void * userData)
{
  XnPoint3D		point;
  
  m_screen.clear();
  
  for (int i = 0; i < fingersData->Size; i++)
    {
#ifdef DEBUG_MOD
      point = CoordConverter::realWorldToNIScreen(fingersData->Fingers[i]);
      g_viewer.addDisc(point.X, point.Y, 20, Color::Red);
#endif

      fingersData->Fingers[i] = 
	CoordConverter::realWorldToScreenSize(fingersData->Fingers[i]);
      m_screen.drawRectangle(fingersData->Fingers[i].X, fingersData->Fingers[i].Y, 
			     20, 20, Color::Blue);
    }

#ifdef DEBUG_MOD
  point = CoordConverter::realWorldToNIScreen(fingersData->Hand);
  g_viewer.addDisc(point.X, point.Y, 40, Color::Red);
#endif

  fingersData->Hand = CoordConverter::realWorldToScreenSize(fingersData->Hand);
  m_screen.drawRectangle(fingersData->Hand.X, fingersData->Hand.Y, 
			 40, 40, Color::Blue);
  
  m_screen.display();
  
  m_mouseControl.update(*fingersData);
}

void XN_CALLBACK_TYPE	FingersListener::FingersDestroy(xn::FingersGenerator & gen,
							XnUserID id, 
							XnFloat time,
							void * userData)
{
}
