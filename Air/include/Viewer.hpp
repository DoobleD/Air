#ifndef _VIEWER_HPP_
#define _VIEWER_HPP_

// STL headers
#include <list>

// SFML headers
#include <SFML/Graphics.hpp>

// NITE header
#include <XnTypes.h>


#define MAX_DEPTH	10000
#define WINDOW_TITLE	"Air Viewer"
#define WINDOW_BPP	32

using namespace std;


namespace air
{

  class			Viewer
  {
  private:
    sf::RenderWindow	m_app;
    sf::Event		m_event;
    sf::Sprite		m_globalSprite;
    sf::Image		m_globalImage;
    list<sf::Vector2i>	m_points;
    list<sf::Shape>	m_shapes;

    unsigned int	m_XRes;
    unsigned int	m_YRes;
    unsigned int	m_imageDataSize;
    unsigned char *	m_imageData;
    double		m_depthHist[MAX_DEPTH];    

    void		events(void);
    void		draw(void);
    void		generateDepthHist(const XnUInt16 * depthData);
    void		drawDepthMap(void);
    void		drawPoints(void);
    void		drawShapes(void);
    void		clear(void);
    void		clearPoints(void);
    void		clearShapes(void);
    void		generateGlobalSprite(void);

  public:
    Viewer(void);
    ~Viewer(void);

    void		initialize(void);
    void		update(void);
    void		addPoint(int x, int y, const char * color);
    void		addCircle(int x, int y, int r, const char * color);
  };

}

#endif //_VIEWER_HPP_
