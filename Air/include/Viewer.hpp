#ifndef _VIEWER_HPP_
#define _VIEWER_HPP_


// STL header
#include <list>

// SFML header
#include <SFML/Graphics.hpp>

// NITE header
#include <XnTypes.h>

// Air header
#include "Color.hpp"


// Maximum depth of the sensor.
#define MAX_DEPTH	10000
// Title of the window.
#define WINDOW_TITLE	"Air Viewer"
// Window bit per pixel (color precision).
#define WINDOW_BPP	32
// Window dimension.
#define WINDOW_WIDTH	320
#define WINDOW_HEIGHT	240


using namespace std;


namespace air
{

  /**
   * Show an image of what the sensor see and what Air detects
   * in a window. Use SFML library (see http://www.sfml-dev.org/).
   * Should not be used if DEBUG_MOD is not defined.
   *
   * @author Pierre Alletru
   */
  class			Viewer
  {

    /**
     * Represent a point on the screen with a given color.
     *
     * @author Pierre Alletru
     */
    struct		ColoredPoint
    {
      // Point coordinates.
      sf::Vector2i	p;
      // Point color.
      sf::Color		c;
      
      /**
       * Default constructor.
       */
      ColoredPoint(void) {}

      /**
       * Constructor.
       *
       * @param _p	The point position.
       * @param _c	The point color.
       */
      ColoredPoint(sf::Vector2i _p, sf::Color _c)
      {p = _p; c = _c;}
    };

  private:

    // SFML window.
    sf::RenderWindow	m_app;
    // SFML events.
    sf::Event		m_event;
    // SFML sprite and image to draw on window.
    // At each frame, the image is filled and then a sprite is generated, which
    // is drawn to thw window.
    sf::Sprite		m_globalSprite;
    sf::Image		m_globalImage;

    // Points and shapes to draw.
    list<ColoredPoint>	m_points;
    list<sf::Shape>	m_shapes;

    // OpenNI resolution (VGA by default).
    unsigned int	m_XRes;
    unsigned int	m_YRes;

    // Data to build depth histogram.
    unsigned int	m_imageDataSize;
    unsigned char *	m_imageData;
    double		m_depthHist[MAX_DEPTH];    

    /**
     * Handle imput events (e.g. keybord presses, mouse click, ...).
     */
    void		events(void);

    /**
     * Draw all on window. Generated a global sprite with an histogram of the depth
     * map, with colored points, draw it on window, and draw shapes.
     */
    void		draw(void);

    /**
     * Generate an histogram of the depth data recorded by the depth sensor.
     * Lower is the depth of a point, lighter is its color. This produces a
     * depth image of the scene.
     *
     * @param depthData		A pointer to a depth map.
     */
    void		generateDepthHist(const XnUInt16 * depthData);

    /**
     * Draw a image representing the depth of the scene to the window.
     */
    void		drawDepthMap(void);
    
    /**
     * Draw colored points to the window.
     */
    void		drawPoints(void);

    /**
     * Draw shapes to the window.
     */
    void		drawShapes(void);

    /**
     * Clear the window and internal data.
     */
    void		clear(void);

    /**
     * Clear the list of points to draw.
     */
    void		clearPoints(void);

    /**
     * Clear the list of shapes to draw.
     */
    void		clearShapes(void);

    /**
     * Generates the global sprite to draw on window.
     */
    void		generateGlobalSprite(void);

  public:
    
    /**
     * Default constructor.
     */
    Viewer(void);
    
    /**
     * Destructor.
     */
    ~Viewer(void);

    /**
     * Initialize the viewer.
     */
    void		initialize(void);

    /**
     * Update the window (interpret events, clear and draw).
     */
    void		update(void);

    /**
     * Add a point to draw on the window.
     *
     * @param x		The x coordinate of the point.
     * @param y		The y coordinate of the point.
     * @param color	The color of the point.
     */
    void		addPoint(int x, int y, const Color & color);

    /**
     * Add a filled disc to draw on the window.
     *
     * @param x		The x coordinate of the disc.
     * @param y		The y coordinate of the disc.
     * @param d		The diameter of the disc.
     * @param color	The color of the disc.
     */
    void		addDisc(int x, int y, int d, const Color & color);
  };

}

#endif //_VIEWER_HPP_
