#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_


#include "OS/IKeyboard.hpp"


namespace air
{
  namespace os
  {
    /**
     * Implementation of IKeyboard for Windows.
     * Simulates keyboard input events.
     *
     * @author Pierre Alletru
     */    
    class		Keyboard : public IKeyboard
    {
    public:

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
