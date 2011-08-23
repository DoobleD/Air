#ifndef _IKEYBOARD_HPP_
#define _IKEYBOARD_HPP_

namespace air
{
  namespace os
  {

    /**
     * Interface for an object simulating keyboard events.
     * Since this is an interface, all methods a pure virtual, and
     * therefore needs to be implemented by child classes.
     *
     * @author Pierre Alletru
     */
    class		IKeyboard
    {
    public:

      // The keyboard keys available
      static int	AltLeft;
      static int	ShiftLeft;
      static int	SuperLeft;
      static int	Escape;
      static int	Tab;
      static int	F4;
      static int	F9;
      static int	F10;
      static int	D;
      static int	Up;
      static int	Down;

      /**
       * Simulate a key pressed.
       *
       * @param key	The key to press.
       */
      virtual void	keyPress(int key) = 0;

      /**
       * Simulate a key released.
       *
       * @param key	The key to released.
       */
      virtual void	keyRelease(int key) = 0;
    };

  }
}

#endif //_IKEYBOARD_HPP_
