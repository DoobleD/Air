#include "Viewer.hpp"
#include "OpenNIBox.hpp"

using namespace air;

extern OpenNIBox	g_openNI;


Viewer::Viewer(void) : m_imageData(NULL)
{
}

Viewer::~Viewer(void)
{
  if (m_imageData)
    delete m_imageData;
}

void			Viewer::events(void)
{
  while (m_app.GetEvent(m_event))
    {
      // Close window : exit
      if (m_event.Type == sf::Event::Closed)
  	m_app.Close();
      if ((m_event.Type == sf::Event::KeyPressed) && 
  	  (m_event.Key.Code == sf::Key::Escape))
  	m_app.Close();
    }
}

void			Viewer::generateDepthHist(const XnUInt16 * depthData)
{
  unsigned int		iY;
  unsigned int		iX;
  unsigned int		idx;
  unsigned int		numberOfPoints = 0;

  // Calculate the accumulative histogram
  memset(m_depthHist, 0, MAX_DEPTH * sizeof(*m_depthHist));
  for (iY = 0; iY < m_YRes; iY++)
    {
      for (iX = 0; iX < m_XRes; iX++)
  	{
  	  if (*depthData != 0)
  	    {
  	      m_depthHist[*depthData]++;
  	      numberOfPoints++;
  	    }	  
  	  depthData++;
  	}
    }
  for (idx = 1; idx < MAX_DEPTH; idx++)
    {
      m_depthHist[idx] += m_depthHist[idx - 1];
    }
  if (numberOfPoints)
    {
      for (idx = 1; idx < MAX_DEPTH; idx++)
  	m_depthHist[idx] = (unsigned int) 
  	  (256 * (1.0f - (m_depthHist[idx] / numberOfPoints)));
    }
}

void			Viewer::drawDepthMap(void)
{
  unsigned int		iY;
  unsigned int		iX;
  unsigned int		histValue;
  unsigned char *	imageDataPtr = m_imageData;
  const XnUInt16 *	depthData = g_openNI.getDepthGenerator().GetDepthMap();
  
  // Generate depth histogram
  generateDepthHist(depthData);

  // Create an array of pixels
  for (iY = 0; iY < m_YRes; iY++)
    {
      for (iX = 0; iX < m_XRes; iX++)
  	{	  
  	  if (*depthData)
  	    {
  	      histValue = (unsigned int) m_depthHist[*depthData];
  	      imageDataPtr[0] = histValue; 
  	      imageDataPtr[1] = histValue;
  	      imageDataPtr[2] = histValue;
  	      imageDataPtr[3] = 255;
  	    }
  	  imageDataPtr += 4;
  	  depthData++;
  	}
    }
}

void			Viewer::drawPoints(void)
{
  list<ColoredPoint>::iterator	begin = m_points.begin();
  list<ColoredPoint>::iterator	end = m_points.end();
  unsigned char *		imageDataPtr;

  while (begin != end)
    {
      imageDataPtr = m_imageData;

      imageDataPtr += (begin->p.y * m_XRes + begin->p.x) * 4;
      imageDataPtr[0] = begin->c.r;
      imageDataPtr[1] = begin->c.g;
      imageDataPtr[2] = begin->c.b;
      imageDataPtr[3] = begin->c.a;

      ++begin;
    }
}

void			Viewer::drawShapes(void)
{
  list<sf::Shape>::iterator	begin = m_shapes.begin();
  list<sf::Shape>::iterator	end = m_shapes.end();

  while (begin != end)
    {
      m_app.Draw(*begin);
      ++begin;
    }
}

void			Viewer::generateGlobalSprite(void)
{
  drawDepthMap();
  drawPoints();

  // Set SFML image and sprite
  m_globalImage.LoadFromPixels(m_XRes, m_YRes, m_imageData);
  m_globalSprite.SetImage(m_globalImage);
}

void			Viewer::draw(void)
{
  // Generate depth sprite
  generateGlobalSprite();
    
  // Stick global sprite & sfml shapes
  m_app.Draw(m_globalSprite);
  drawShapes();  

  // Display
  m_app.Display();
}

void			Viewer::initialize(void)
{
  xn::DepthMetaData	depthMD;

  g_openNI.getDepthGenerator().GetMetaData(depthMD);

  m_YRes = depthMD.YRes();
  m_XRes = depthMD.XRes();

  m_imageDataSize = m_XRes * m_YRes * 4; // RGBA format
  m_imageData = new unsigned char[m_imageDataSize];

  // Create video mode
  m_app.Create(sf::VideoMode(m_XRes, m_YRes, WINDOW_BPP), 
	       WINDOW_TITLE,
	       sf::Style::None);

}

void			Viewer::update(void)
{
  if (m_app.IsOpened())
    {
      events();
      draw();
      clear();
    }
}

void			Viewer::clearPoints(void)
{
  m_points.clear();
}

void			Viewer::clearShapes(void)
{
  m_shapes.clear();
}

void			Viewer::addPoint(int x, int y, const Color & color)
{
  m_points.push_back(ColoredPoint(sf::Vector2i(x, y), 
				  sf::Color(color.r, color.g, color.b)));
}


void			Viewer::addDisc(int x, int y, int d, const Color & color)
{
  m_shapes.push_back(sf::Shape::Circle(x, y, d / 2, 
				       sf::Color(color.r, color.g, color.b)));
}

void			Viewer::clear(void)
{
  // Clear image data
  memset(m_imageData, 0, m_imageDataSize);

  // Clear points & shapes
  clearPoints();
  clearShapes();

  // Clear window & clear shape list
  m_app.Clear();  
}
