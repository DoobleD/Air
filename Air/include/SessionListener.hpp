#ifndef _SESSION_LISTENER_HPP_
#define _SESSION_LISTENER_HPP_


// NITE header
#include <XnVSessionListener.h>


/**
 * Possible session states.
 */
typedef enum
{
	IN_SESSION,
	NOT_IN_SESSION,
} SessionState;


namespace air
{
  
  /**
   * Implements the NITE's session class XnVSessionListener.
   * The On* methods are called by NITE when a session event occurs 
   * (e.g. session is created, ends, ...).
   *
   * @author Pierre Alletru
   */
  class			SessionListener : public XnVSessionListener
  {
  private:

    // The current session state.
    SessionState	m_sessionState;

    /**
     * Called by NITE when a specific gesture is detected. Currently, this gesture 
     * is a wave gesture.
     *
     * Register NITE events listener to the NITE event broadcaster, and the fingers 
     * callbacks to the FingersGenerator. So Air is ready to handle all gesture events.
     *
     *
     * @param ptPosition	The position where the session start gesture has been
     *				detected.
     */
    void		OnSessionStart(const XnPoint3D & ptPosition); 

    /**
     * Called by NITE when the session ends (the hand is lost).
     */
    void		OnSessionEnd(void);

    /**
     * Called by NITE when the gesture focus begins to detect the start gesture.
     *
     * @param strFocus		The name of the gesture which has the focus.
     * @param ptPosition	The position where the is focus.
     * @param progress		The progress of the gesture.
     */
    void		OnFocusStartDetected(const XnChar *strFocus, 
					     const XnPoint3D & ptPosition, 
					     XnFloat progress);
    
  public:

    /**
     * Default constructor.
     */
    SessionListener(void);
    
    /**
     * Destructor.
     */
    ~SessionListener(void);
  };

}

#endif //_SESSION_LISTENER_HPP_
