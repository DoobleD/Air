#ifndef _IKEYBOARD_HPP_
#define _IKEYBOARD_HPP_

namespace air
{
  namespace os
  {

    class		IKeyboard
    {
    public:
      static int	AltLeft;
      static int	ShiftLeft;
      static int	SuperLeft;
      static int	Escape;
      static int	Tab;
      static int	F9;
      static int	F10;
      static int	D;
      static int	Up;
      static int	Down;

      virtual void	keyPress(int key) = 0;
      virtual void	keyRelease(int key) = 0;
    };

  }
}

#endif //_IKEYBOARD_HPP_
