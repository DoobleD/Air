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
//int toto = 1;
void			Viewer::drawPoints(void)
{
  list<sf::Vector2i>::iterator	itBegin = m_points.begin();
  list<sf::Vector2i>::iterator	itEnd = m_points.end();
  unsigned char *		imageDataPtr;

  // static int truc = 1;
  // int i = 0;
  // toto++;
  // if (toto == 200) {m_points.clear(); truc = 1;}
  // if (toto > 200) {
  while (itBegin != itEnd)// && i < truc)
    {
      imageDataPtr = m_imageData;

      imageDataPtr += (itBegin->y * m_XRes + itBegin->x) * 4;
      imageDataPtr[0] = 0;
      imageDataPtr[1] = 0;
      imageDataPtr[2] = 255;
      imageDataPtr[3] = 255;
      //i++;
      ++itBegin;
    }//}
  // truc++;
  // printf("%d\n", truc);
}

void			Viewer::drawShapes(void)
{
  list<sf::Shape>::iterator	itBegin = m_shapes.begin();
  list<sf::Shape>::iterator	itEnd = m_shapes.end();

  while (itBegin != itEnd)
    {
      m_app.Draw(*itBegin);
      //m_shapes.erase(itBegin);
      ++itBegin;
    }
}

void			Viewer::generateGlobalSprite(void)
{
  //drawDepthMap();
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
  m_app.Create(sf::VideoMode(m_XRes, m_YRes, WINDOW_BPP), WINDOW_TITLE);

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

void			Viewer::addPoint(int x, int y, const char * color)
{
  m_points.push_back(sf::Vector2i(x, y));
}


void			Viewer::addCircle(int x, int y, int r, const char * color)
{
  m_shapes.push_back(sf::Shape::Circle(x, y, r, sf::Color(255, 0, 0)));
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
