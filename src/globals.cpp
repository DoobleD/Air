#ifdef DEBUG_MOD
#include "Viewer.hpp"

air::Viewer	g_viewer;
#endif


#include "OpenNIBox.hpp"
#include "NITEBox.hpp"

#include "EventListener.hpp"
#include "E_MouseMove.hpp"
#include "E_LeftClick.hpp"
#include "E_RightClick.hpp"
#include "E_SwitchTab.hpp"
#include "E_Minimize.hpp"
#include "E_Maximize.hpp"
#include "E_ShowKeyboard.hpp"


using namespace air;


OpenNIBox	g_openNI;
NITEBox		g_NITE;

EventListener	g_eventListeners[] =
  {
    {"MouseMove", new E_MouseMove()},
    {"LeftClick", new E_LeftClick()},
    //{"RightClick", new E_RightClick()},
    {"Minimize", new E_Minimize()},
    {"Maximize", new E_Maximize()},
    {"SwitchTab", new E_SwitchTab()},
    {"ShowKeyboard", new E_ShowKeyboard()},
    {NULL, NULL}
  };
