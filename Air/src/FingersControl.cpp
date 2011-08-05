#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif


#include "FingersControl.hpp"
#include "Screen.hpp"


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

#ifdef DEBUG_MOD
  for (int i = 0; i < fingersData->Size; i++)
    g_viewer.addDisc(fingersData->Fingers[i].X, fingersData->Fingers[i].Y,
		     10, Color::Red);
  g_viewer.addDisc(fingersData->Hand.X, fingersData->Hand.Y, 20, Color::Red);
#endif
  
  screen.clear();
  for (int i = 0; i < fingersData->Size; i++)
    screen.drawDisc(fingersData->Fingers[i].X, fingersData->Fingers[i].Y, 
    		    30, Color::Blue);
  screen.display();

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
