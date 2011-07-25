#ifndef _NITE_BOX_HPP_
#define _NITE_BOX_HPP_

// NITE headers
#include <XnVNite.h>

// Air headers
#include "SessionListener.hpp"

namespace air
{
  /**
   * Handle NITE operations and data.
   *
   * @author Pierre Alletru
   */
  class				NITEBox
  {
  private:

    XnVSessionManager		m_session;
    XnVBroadcaster		m_mainBroadcaster;

  public:

    /**
     * Initialize NITE.
     * @param sessionListener	The session to associate with NITE. This session 
				contains the callbacks to NITE session events 
				(session start, session end, focus start).
     */
    void			initialize(SessionListener & sessionListener);

    /**
     * Get the current active session associated with NITE.
     * @return The NITE session object.
     */
    XnVSessionManager &		getSession(void);

    /**
     * Get the main event broadcaster of the current session. The broadcaster
     * broadcast events to NITE event listeners related to specific gestures 
     * (e.g. push gesture).
     * @return The NITE broadcaster object.
     */
    XnVBroadcaster &		getMainBroadcaster(void);

    void			update(void);
  };
  
}

#endif //_NITE_BOX_HPP_
