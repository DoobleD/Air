#ifdef DEBUG_MOD
#include "Viewer.hpp"

air::Viewer	g_viewer;
#endif


#include "OpenNIBox.hpp"
#include "NITEBox.hpp"

#include "EventListener.hpp"

#include "E_ShowDesktop.hpp"
#include "E_SwitchTab.hpp"
#include "E_MinimizeMaximize.hpp"


using namespace air;


OpenNIBox	g_openNI;
NITEBox		g_NITE;

EventListener	g_eventListeners[] =
  {
    {"MinimizeMaximize", new E_MinimizeMaximize()},
    {"SwitchTab", new E_SwitchTab()},
    {"ShowDesktop", new E_ShowDesktop()},
    {NULL, NULL}
  };
