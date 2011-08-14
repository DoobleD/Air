#include "OS/Screen.hpp"


using namespace air::os;


Screen::Screen(void)
{
  m_threadRunning = false;
}

Screen::~Screen(void)
{
  if (m_threadRunning)
    {
      m_threadRunning = false;
      Wait();
    }
}

int		Screen::getResX(void)
{
  return GetSystemMetrics(SM_CXFULLSCREEN);
}

int		Screen::getResY(void)
{
  return GetSystemMetrics(SM_CYFULLSCREEN);
}


void		Screen::clear(void)
{
  m_mutex.Lock();

  std::list<Rectangle>::iterator	begin = m_rectangles.begin();
  std::list<Rectangle>::iterator	end = m_rectangles.end();

  while (begin != end)
    {
      begin->erased = true;
      ++begin;
    }

  m_mutex.Unlock();
}

void		Screen::drawRectangle(int x, int y, 
				      int sizeX, int sizeY, 
				      const air::Color & color)
{
  if (x >= 0 && x < getResX() &&
      y >= 0 && y < getResY())
    {
      Rectangle	rect;
      
      rect.coord.left = x;
      rect.coord.top = y;
      rect.coord.right = x + sizeX;
      rect.coord.bottom = y + sizeY;
      rect.color = RGB(color.r, color.g, color.b);
      
      m_mutex.Lock();
      
      m_rectangles.push_back(rect);
      
      m_mutex.Unlock();
    }
}

void		Screen::display(void)
{
  if (!m_threadRunning)
    {
      m_threadRunning = true;
      Launch();
    }
}

void		Screen::restoreOSScreen(void)
{
  //  Redraw modified zones of screen
  std::list<Rectangle>::iterator	begin = m_rectangles.begin();
  std::list<Rectangle>::iterator	end = m_rectangles.end();

  while (begin != end)
    {
      RedrawWindow(0, &(begin->coord), 0, RDW_INVALIDATE | RDW_ALLCHILDREN);

      if (begin->erased)
	begin = m_rectangles.erase(begin);
      else
	++begin;
    }
}

void		Screen::paintRectangles(void)
{
  std::list<Rectangle>::iterator	begin = m_rectangles.begin();
  std::list<Rectangle>::iterator	end = m_rectangles.end();
  HBRUSH				brush;
  
  while (begin != end)
    {
      brush = CreateSolidBrush(begin->color);

      FillRect(m_memDC, &(begin->coord), brush);
      BitBlt(m_screenDC, begin->coord.left, begin->coord.top, 
      	     begin->coord.right - begin->coord.left, 
	     begin->coord.bottom - begin->coord.top,
      	     m_memDC, begin->coord.left, begin->coord.top, SRCCOPY);      

      DeleteObject(brush);

      ++begin;
    }
}

void		Screen::paintAll(void)
{
  paintRectangles();
  // In future: paintCircles, paintPoints, etc
}

void		Screen::destroyGDIComponents(void)
{
  SelectObject(m_memDC, m_bmapHandle);
  DeleteObject(m_bmap);
  DeleteDC(m_memDC);
  ReleaseDC(0, m_screenDC);
}

void		Screen::initializeGDIComponents(void)
{
  m_screenDC = GetDC(0);
  m_memDC = CreateCompatibleDC(m_screenDC);
  m_bmap = CreateCompatibleBitmap(m_screenDC, getResX(), getResY());
  m_bmapHandle = SelectObject(m_memDC, m_bmap);
}

void		Screen::Run(void)
{
  sf::Clock	clock;
  float		fps = 1.f / _FPS;

  initializeGDIComponents();

  clock.Reset();
  while (m_threadRunning)
    {
      clock.Reset();

      m_mutex.Lock();
      
      restoreOSScreen();
      paintAll();

      m_mutex.Unlock();

      sf::Sleep(fps - clock.GetElapsedTime());
    }

  destroyGDIComponents();
}
