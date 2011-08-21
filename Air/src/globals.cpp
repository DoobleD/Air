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
#include "E_KillCurrent.hpp"


using namespace air;


OpenNIBox	g_openNI;
NITEBox		g_NITE;

EventListener	g_eventListeners[] =
  {
    {new E_MinimizeMaximize()},
    {new E_SwitchTab()},
    {new E_ShowDesktop()},
    {new E_KillCurrent()},
    {NULL}
  };
