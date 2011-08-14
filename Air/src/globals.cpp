#ifdef DEBUG_MOD
#include "Viewer.hpp"

air::Viewer	g_viewer;
#endif


#include "OpenNIBox.hpp"
#include "NITEBox.hpp"

#include "EventListener.hpp"

#include "E_ShowDesktop.hpp"
#include "E_SwitchTabLeft.hpp"
#include "E_SwitchTabRight.hpp"
#include "E_Minimize.hpp"
#include "E_Maximize.hpp"


using namespace air;


OpenNIBox	g_openNI;
NITEBox		g_NITE;

EventListener	g_eventListeners[] =
  {
    {"Minimize", new E_Minimize()},
    {"Maximize", new E_Maximize()},
    {"SwitchTabLeft", new E_SwitchTabLeft()},
    {"SwitchTabRight", new E_SwitchTabRight()},
    {"ShowDesktop", new E_ShowDesktop()},
    {NULL, NULL}
  };
