#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif

#include <iostream>

#include "SessionListener.hpp"
#include "NITEBox.hpp"
#include "OpenNIBox.hpp"
#include "EventListener.hpp"
#include "FingersListener.hpp"

using namespace air;

extern NITEBox		g_NITE;
extern OpenNIBox	g_openNI;
extern EventListener	g_eventListeners[];


SessionListener::SessionListener(void) : m_sessionState(NOT_IN_SESSION)
{
}

SessionListener::~SessionListener(void)
{
}

void			SessionListener::OnFocusStartDetected(const XnChar* strFocus, 
							      const XnPoint3D& ptPosition, 
							      XnFloat fProgress)
{
  std::cout << "Focus progress" << std::endl;
}

void			SessionListener::OnSessionStart(const XnPoint3D& ptPosition)
{
  XnVBroadcaster &		broadcaster = g_NITE.getMainBroadcaster();
  xn::FingersGenerator &	fingersGen = g_openNI.getFingersGenerator();
  
  std::cout << "Session start" << std::endl;
  m_sessionState = IN_SESSION;

  for (int i = 0; g_eventListeners[i].name; i++)
    broadcaster.AddListener(g_eventListeners[i].listener);

  fingersGen.SetSmoothing(true);
  fingersGen.RegisterFingersCallbacks(FingersListener::FingersCreate, 
				      FingersListener::FingersUpdate,
				      FingersListener::FingersDestroy, 
				      NULL);
}

void			SessionListener::OnSessionEnd()
{
  std::cout << "Session end"  << std::endl;
  m_sessionState = NOT_IN_SESSION;
}
