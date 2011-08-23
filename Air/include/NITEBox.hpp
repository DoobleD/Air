#ifndef _NITE_BOX_HPP_
#define _NITE_BOX_HPP_


// NITE header
#include <XnVNite.h>

// Air header
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

    // The NITE's session object.
    XnVSessionManager		m_session;
    // Used to broadcast events to all NITE's listener (see SessionListener.hpp).
    XnVBroadcaster		m_mainBroadcaster;

  public:

    /**
     * Initialize NITE.
     *
     * @param sessionListener	The session to associate with NITE. This session 
     *				contains the callbacks to NITE session events 
     *				(session start, session end, focus start).
     */
    void			initialize(SessionListener & sessionListener);

    /**
     * Get the current active session associated with NITE.
     *
     * @return The NITE's session object.
     */
    XnVSessionManager &		getSession(void);

    /**
     * Get the main event broadcaster of the current session. The broadcaster
     * broadcast events to NITE event listeners related to specific gestures 
     * (e.g. push gesture).
     *
     * @return A reference to the NITE's broadcaster object.
     */
    XnVBroadcaster &		getMainBroadcaster(void);

    /**
     * Update NITE. Use OpenNI to recognize events and transmitt them to NITE's
     * session. Should be called for each frame.
     */
    void			update(void);
  };
  
}

#endif //_NITE_BOX_HPP_
