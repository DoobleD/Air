#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_

#include "OS/IKeyboard.hpp"

#include <X11/Xlib.h>
#include <X11/keysym.h>


namespace air
{
  namespace os
  {
    
    class		Keyboard : public IKeyboard
    {
    private:
      Display *		m_display;

    public:
      Keyboard(void);
      ~Keyboard(void);

      void		keyPress(int key);
      void		keyRelease(int key);
    };
    
  }
}

#endif //_KEYBOARD_HPP_
