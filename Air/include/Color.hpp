#ifndef _COLOR_HPP_
#define _COLOR_HPP_


#include <string>


namespace air
{
  
  /**
   * Represent a RGBA color.
   *
   * @author Pierre Alletru
   */
  struct		Color
  {
    // Static colors often used.
    static const Color	Black;
    static const Color  Red;
    static const Color  Green;
    static const Color  Blue;
    static const Color  Cyan;
    static const Color  Yellow;
    static const Color  Magenta;
    static const Color  White;

    // red, green, blue, and alpha (transparency) values.
    int			r;
    int			g;
    int			b;
    int			a; // 0 = invisible, 255 = opaque.

    /**
     * Constructor.
     *
     * @param _r	Optional. A red value (0 - 255).
     * @param _g	Optional. A green value (0 - 255).
     * @param _b	Optional. A blue value (0 - 255).
     * @param _a	Optional. An alpha value (0 - 255).
     */
    Color(int _r = 0, int _g = 0, 
	  int _b = 0, int _a = 255);

    /**
     * Get a string which represent the RGB values.
     * For example, red (255, 0, 0) would be : #FF0000.
     *
     * @return A string corresponding to the RGB values of the color.
     */
    const std::string	getRGBString(void) const;
  };

}

#endif //_COLOR_HPP_
