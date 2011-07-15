#include "NITEBox.hpp"
#include "OpenNIBox.hpp"
#include "SessionListener.hpp"
#include "error.hpp"

using namespace air;

extern OpenNIBox	g_openNI;


void			NITEBox::initialize(SessionListener & sessionListener)
{
  XnStatus		rs;
  
  rs = m_session.Initialize(&g_openNI.getContext(), "Wave", "RaiseHand");
  CHECK_RS(rs, "SessionManager::Initialize");
      
  m_session.RegisterSession(&sessionListener);
  m_session.AddListener(&m_mainBroadcaster);
}

XnVSessionManager &	NITEBox::getSession(void)
{
  return m_session;
}

XnVBroadcaster &	NITEBox::getMainBroadcaster(void)
{
  return m_mainBroadcaster;
}
