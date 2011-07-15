#ifndef _NITE_BOX_HPP_
#define _NITE_BOX_HPP_

// NITE headers
#include <XnVNite.h>

// Air headers
#include "SessionListener.hpp"

namespace air
{
  class				NITEBox
  {
  private:
    XnVSessionManager		m_session;
    XnVBroadcaster		m_mainBroadcaster;

  public:
    void			initialize(SessionListener & sessionListener);
    XnVSessionManager &		getSession(void);
    XnVBroadcaster &		getMainBroadcaster(void);
  };
  
}

#endif //_NITE_BOX_HPP_
