#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_


#include <X11/Xlib.h>

#include "OS/IMouse.hpp"


namespace air
{
  namespace os
  {

    /**
     * Implementation of IMouse for unix systems.
     * Simulates mouse input events.
     *
     * @author Pierre Alletru
     */
    class		Mouse : public IMouse
    {
    private:

      // The X11 root display.
      Display *		m_display;

      /**
       * Simulate a button press.
       *
       * @param button	The button to press.
       */
      void		buttonPress(int button);

      /**
       * Simulate a button release.
       *
       * @param button	The button to release.
       */
      void		buttonRelease(int button);

    public:
      
      /**
       * Default constructor.
       */
      Mouse(void);

      /**
       * Destructor.
       */
      ~Mouse(void);

      /**
       * Set the position of the mouse.
       *
       * @param x	The x position.
       * @param y	The y position.
       */
      void		setPosition(double x, double y);

      /**
       * Press left button.
       */
      void		leftButtonPress(void);

      /**
       * Release left button.
       */
      void		leftButtonRelease(void);

      /**
       * Press right button.
       */
      void		rightButtonPress(void);

      /**
       * Release right button.
       */
      void		rightButtonRelease(void);

      /**
       * Press middle button.
       */
      void		middleButtonPress(void);

      /**
       * Release middle button.
       */
      void		middleButtonRelease(void);

      /**
       * Wheel up.
       */
      void		wheelUp(void);

      /**
       * Wheel down.
       */
      void		wheelDown(void);
    };

  }
}

#endif //_MOUSE_HPP_
