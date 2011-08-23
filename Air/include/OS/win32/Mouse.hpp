#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_


#include "OS/IMouse.hpp"


namespace air
{
  namespace os
  {

    /**
     * Implementation of IMouse for Windows.
     * Simulates mouse input events.
     *
     * @author Pierre Alletru
     */
    class		Mouse : public IMouse
    {
    private:

      // Screen resolution.
      int		m_resX;
      int		m_resY;

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
