#ifndef _EVENT_LISTENER_HPP_
#define _EVENT_LISTENER_HPP_

#include <XnVMessageListener.h>

namespace air
{

  struct			EventListener
  {
    const char *		name;
    XnVMessageListener *	listener;
  };

}

#endif //_EVENT_LISTENER_HPP_
