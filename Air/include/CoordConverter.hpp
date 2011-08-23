#ifndef _COORD_CONVERTER_HPP_
#define _COORD_CONVERTER_HPP_


#include <XnTypes.h>

#include "OS/Screen.hpp"


// Used to 'speed' a point on screen, rather than convert to 
// the real corresponfing position.
#define DEFAULT_SPEED_FACTOR	2


namespace air
{
  /**
   * Offer methods for coordinates conversion. Every methods are static.
   *
   * @author Pierre Alletru
   */
  class			CoordConverter
  {
  private:

    // A screen object, used for screen relative conversions.
    static os::Screen	m_screen;

  public:
    
    /**
     * Converts a point in real world coordinates to a point 
     * on full screen coordinates.
     *
     * @param point	A given point.
     *
     * @return The point converted to screen coordinates.
     */
    static XnPoint3D	realWorldToScreenSize(XnPoint3D point);

    /**
     * Converts a point in real world coordinates to OpenNI 
     * screen coordinates (default is VGA).
     *
     * @param point	A given point.
     *
     * @return The point converted to OpenNI screen coordinates.
     */
    static XnPoint3D	realWorldToNIScreen(XnPoint3D point);

    /**
     * Convert a point from full screen coordinates to a point at a higher distance
     * to the center of the screen.
     *
     * @param point		A given point.
     * @param speedFactor	Optional. A factor to increase the distance.
     *
     * @return The converted point.
     */
    static XnPoint3D	screenSizeToSpeedFactor(XnPoint3D point, 
						int speedFactor = DEFAULT_SPEED_FACTOR);
  };

}

#endif //_COORD_CONVERTER_HPP_
