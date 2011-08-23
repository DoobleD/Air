#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_


#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "OS/IKeyboard.hpp"


namespace air
{
  namespace os
  {

    /**
     * Implementation of IKeyboard for unix systems.
     * Simulates keyboard input events.
     *
     * @author Pierre Alletru
     */
    class		Keyboard : public IKeyboard
    {
    private:

      // The X11 root display.
      Display *		m_display;

    public:

      /**
       * Default constructor.
       */
      Keyboard(void);

      /**
       * Destructor.
       */
      ~Keyboard(void);

      /**
       * Simulate a key pressed.
       *
       * @param key	The key to press.
       */
      void		keyPress(int key);

      /**
       * Simulate a key released.
       *
       * @param key	The key to released.
       */
      void		keyRelease(int key);
    };
    
  }
}

#endif //_KEYBOARD_HPP_
