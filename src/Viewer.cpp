#include "Viewer.hpp"
#include "OpenNIBox.hpp"

using namespace air;

extern OpenNIBox	g_openNI;


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

void			Viewer::generateDepthSprite(void)
{
  unsigned int		iY;
  unsigned int		iX;
  unsigned int		histValue;
  unsigned int		imageSize = m_XRes * m_YRes * 4; // RGBA format
  unsigned char *	imageData = new unsigned char[imageSize];
  unsigned char *	imageDataCpy = imageData;
  const XnUInt16 *	depthData = g_openNI.getDepthGenerator().GetDepthMap();
  
  // Generate depth histogram
  generateDepthHist(depthData);
  // Create an array of pixels
  memset(imageData, 0, imageSize);
  for (iY = 0; iY < m_YRes; iY++)
    {
      for (iX = 0; iX < m_XRes; iX++)
  	{	  
  	  if (*depthData)
  	    {
  	      histValue = (unsigned int) m_depthHist[*depthData];
  	      imageData[0] = histValue; 
  	      imageData[1] = histValue;
  	      imageData[2] = histValue;
  	      imageData[3] = 255;
  	    }
  	  imageData += 4;
  	  depthData++;
  	}
    }

  // Set SFML image and sprite
  m_depthImage.LoadFromPixels(m_XRes, m_YRes, imageDataCpy);
  m_depthSprite.SetImage(m_depthImage);

  delete imageDataCpy;
}

void			Viewer::draw(void)
{
  // Generate depth sprite
  generateDepthSprite();

  // Clear window
  m_app.Clear();  

  // Stick depth sprite & hand point circle
  m_app.Draw(m_depthSprite);
  m_mutex.Lock();
  m_app.Draw(m_handPoint);
  m_mutex.Unlock();

  // Display
  m_app.Display();
}

void			Viewer::initialize(void)
{
  xn::DepthMetaData	depthMD;

  g_openNI.getDepthGenerator().GetMetaData(depthMD);

  m_YRes = depthMD.YRes();
  m_XRes = depthMD.XRes();

  m_handPoint = sf::Shape::Circle(0, 0, 20, sf::Color(255, 0, 0));

  // Create video mode
  m_app.Create(sf::VideoMode(m_XRes, m_YRes, WINDOW_BPP), WINDOW_TITLE);
}

void			Viewer::Run(void)
{
  // Initialize
  initialize();

  // Start loop
  while (m_app.IsOpened())
    {
      events();
      draw();
    }
}

void			Viewer::launch(void)
{
  // Start a thread, goes into Run(void) method (see SFML for more information)
  Launch();
}

void			Viewer::setHandPosition(double x, double y)
{
  m_mutex.Lock();
  m_handPoint.SetPosition((float) x, (float) y);
  m_mutex.Unlock();
}
