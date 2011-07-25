#ifndef _SESSION_LISTENER_HPP_
#define _SESSION_LISTENER_HPP_

// NITE headers
#include <XnVSessionListener.h>


typedef enum
{
	IN_SESSION,
	NOT_IN_SESSION,
} SessionState;


namespace air
{
  
  class			SessionListener : public XnVSessionListener
  {
  private:
    SessionState	m_sessionState;

    void		OnSessionStart(const XnPoint3D & ptPosition); 
    void		OnSessionEnd();
    void		OnFocusStartDetected(const XnChar *strFocus, 
					     const XnPoint3D & ptPosition, 
					     XnFloat fProgress);
    
  public:
    SessionListener();
    ~SessionListener();
  };

}

#endif //_SESSION_LISTENER_HPP_
