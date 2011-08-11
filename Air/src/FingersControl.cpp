#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif


#include "FingersControl.hpp"
#include "Screen.hpp"
#include "CoordConverter.hpp"


using namespace air;


void XN_CALLBACK_TYPE	FingersControl::FingersCreate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      const xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData)
{
}

void XN_CALLBACK_TYPE	FingersControl::FingersUpdate(xn::FingersGenerator & gen,
						      XnUserID id, 
						      const xn::FingersData * fingersData,
						      XnFloat time, 
						      void * userData)
{
  static os::Screen	screen;
  XnPoint3D		point;
  
  screen.clear();

  for (int i = 0; i < fingersData->Size; i++)
    {
      point = CoordConverter::realWorldToScreenSize(fingersData->Fingers[i]);
      screen.drawRectangle((int) point.X, (int) point.Y, 20, 20, Color::Blue);
      
#ifdef DEBUG_MOD
      point = CoordConverter::realWorldToNIScreen(fingersData->Fingers[i]);
      g_viewer.addDisc(point.X, point.Y, 20, Color::Red);
#endif

    }
  point = CoordConverter::realWorldToScreenSize(fingersData->Hand);
  screen.drawRectangle((int) point.X, (int) point.Y, 40, 40, Color::Blue);

  screen.display();

#ifdef DEBUG_MOD
  point = CoordConverter::realWorldToNIScreen(fingersData->Hand);
  g_viewer.addDisc(point.X, point.Y, 40, Color::Red);
#endif

  // if (fingersData->Size == 1)
  //   printf("point\n");
  // else if (fingersData->Size == 2)
  //   printf("DOCE\n");
  // else if (fingersData->Size  == 5)
  //   printf("HAND!\n");
}

void XN_CALLBACK_TYPE	FingersControl::FingersDestroy(xn::FingersGenerator & gen,
						       XnUserID id, 
						       XnFloat time,
						       void * userData)
{
}
