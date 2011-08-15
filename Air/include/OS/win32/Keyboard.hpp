#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_

#include "OS/IKeyboard.hpp"


namespace air
{
  namespace os
  {
    
    class		Keyboard : public IKeyboard
    {
    public:
      void		keyPress(int key);
      void		keyRelease(int key);
    };
    
  }
}

#endif //_KEYBOARD_HPP_
