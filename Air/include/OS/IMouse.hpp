#ifndef _IMOUSE_HPP_
#define _IMOUSE_HPP_

namespace air
{
  namespace os
  {

    /**
     * Interface for an object simulating mouse events.
     * Since this is an interface, all methods a pure virtual, and
     * therefore needs to be implemented by child classes.
     *
     * @author Pierre Alletru
     */
    class		IMouse
    {
    public:

      /**
       * Set the position of the mouse.
       *
       * @param x	The x position.
       * @param y	The y position.
       */
      virtual void	setPosition(double x, double y) = 0;

      /**
       * Press left button.
       */
      virtual void	leftButtonPress(void) = 0;

      /**
       * Release left button.
       */
      virtual void	leftButtonRelease(void) = 0;

      /**
       * Press right button.
       */
      virtual void	rightButtonPress(void) = 0;

      /**
       * Release right button.
       */
      virtual void	rightButtonRelease(void) = 0;

      /**
       * Press middle button.
       */
      virtual void	middleButtonPress(void) = 0;

      /**
       * Release middle button.
       */
      virtual void	middleButtonRelease(void) = 0;

      /**
       * Wheel up.
       */
      virtual void	wheelUp(void) = 0;

      /**
       * Wheel down.
       */
      virtual void	wheelDown(void) = 0;
    };

  }
}

#endif //_IMOUSE_HPP_
