#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif

#include <iostream>

#include "SessionListener.hpp"
#include "NITEBox.hpp"
#include "OpenNIBox.hpp"
#include "EventListener.hpp"

using namespace air;

extern NITEBox		g_NITE;
extern OpenNIBox	g_openNI;
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
  std::cout << "Focus progress" << std::endl;
}

void XN_CALLBACK_TYPE Hand_Create(xn::FingersGenerator&,
				  XnUserID nId, const xn::FingersData * data,
				  XnFloat fTime, void* pCookie)
{
}

void XN_CALLBACK_TYPE Hand_Update(xn::FingersGenerator&,
				  XnUserID nId, const xn::FingersData * data,
				  XnFloat fTime, void* pCookie)
{
  for (int i = 0; i < data->Size; i++)
    g_viewer.addCircle(data->Fingers[i].X, data->Fingers[i].Y,
  		       10, "Red");
}

void XN_CALLBACK_TYPE Hand_Destroy(xn::FingersGenerator&,
				   XnUserID nId, XnFloat fTime,
				   void* pCookie)
{
}

void			SessionListener::OnSessionStart(const XnPoint3D& ptPosition)
{
  XnVBroadcaster &	broadcaster = g_NITE.getMainBroadcaster();
  
  std::cout << "Session start" << std::endl;
  m_sessionState = IN_SESSION;

  for (int i = 0; g_eventListeners[i].name; i++)
    broadcaster.AddListener(g_eventListeners[i].listener);

  // Test
  xn::FingersGenerator fg = g_openNI.getFingersGenerator();

  fg.RegisterFingersCallbacks(Hand_Create, Hand_Update, Hand_Destroy, NULL);
  fg.SetSmoothing(0.1f);
  //
}

void			SessionListener::OnSessionEnd()
{
  std::cout << "Session end"  << std::endl;
  m_sessionState = NOT_IN_SESSION;
}
