#include "SessionListener.hpp"
#include "NITEBox.hpp"
#include "EventListener.hpp"

using namespace air;

extern NITEBox		g_NITE;
extern EventListener	g_eventListeners[];


SessionListener::SessionListener() : m_sessionState(NOT_IN_SESSION)
{
}

SessionListener::~SessionListener()
{
}

void			SessionListener::OnFocusStartDetected(const XnChar* strFocus, 
							      const XnPoint3D& ptPosition, 
							      XnFloat fProgress)
{
  printf("Focus progress\n");
}

void			SessionListener::OnSessionStart(const XnPoint3D& ptPosition)
{
  XnVBroadcaster &	broadcaster = g_NITE.getMainBroadcaster();
  
  printf("Session start\n");
  m_sessionState = IN_SESSION;

  for (int i = 0; g_eventListeners[i].name; i++)
    broadcaster.AddListener(g_eventListeners[i].listener);
}

void			SessionListener::OnSessionEnd()
{
  printf("Session end\n");
  m_sessionState = NOT_IN_SESSION;
}
