#ifndef _VIEWER_HPP_
#define _VIEWER_HPP_

// SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// NITE header
#include <XnTypes.h>


#define MAX_DEPTH	10000
#define WINDOW_TITLE	"Air Viewer"
#define WINDOW_BPP	32


namespace air
{

  class			Viewer : public sf::Thread
  {
  private:
    sf::RenderWindow	m_app;
    sf::Event		m_event;
    sf::Sprite		m_depthSprite;
    sf::Image		m_depthImage;
    sf::Shape		m_handPoint;
    sf::Mutex		m_mutex;

    unsigned int	m_XRes;
    unsigned int	m_YRes;
    double		m_depthHist[MAX_DEPTH];

    void		Run(void); // Threaded method (see SFML)
    void		events(void);
    void		draw(void);
    void		initialize(void);
    void		generateDepthHist(const XnUInt16 * depthData);
    void		generateDepthSprite(void);

  public:
    void		launch(void);
    void		setHandPosition(double x, double y);
  };

}

#endif //_VIEWER_HPP_
