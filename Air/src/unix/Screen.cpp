#include "Screen.hpp"

#include <stdlib.h>

// No use of 'using namespace air::os' to avoid conflict with a struct Screen form Xlib

air::os::Screen::Screen(void)
{
  m_display = XOpenDisplay(0);
  m_screen = DefaultScreen(m_display);
  m_rootWindow = DefaultRootWindow(m_display);

  m_threadRunning = false;
}

air::os::Screen::~Screen(void)
{
  if (m_threadRunning)
    {
      m_threadRunning = false;
      Wait();
    }
}

int			air::os::Screen::getResX(void)
{
  XWindowAttributes 	attributes;

  XGetWindowAttributes(m_display, m_rootWindow, &attributes);

  return attributes.width;
}

int			air::os::Screen::getResY(void)
{
  XWindowAttributes 	attributes;

  XGetWindowAttributes(m_display, m_rootWindow, &attributes);

  return attributes.height;
}

void			air::os::Screen::clear(void)
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

void			air::os::Screen::drawRectangle(int x, int y, 
						       int sizeX, int sizeY, 
						       const air::Color & color)
{
  Rectangle		rect;

  rect.x = x;
  rect.y = y;
  rect.sizeX = sizeX;
  rect.sizeY = sizeY;
  rect.color = color;

  m_mutex.Lock();

  m_rectangles.push_back(rect);

  m_mutex.Unlock();
}

void			air::os::Screen::display(void)
{
  if (!m_threadRunning)
    {
      m_threadRunning = true;
      Launch();
    }
}

void			air::os::Screen::initializeXComponents(void)
{

  m_pixmapBuffer = XCreatePixmap(m_display, m_rootWindow,
				 getResX(), getResY(), 
				 DefaultDepth(m_display, m_screen));
  
  m_colorMap = DefaultColormap(m_display, m_screen);

  buildGraphicContext();
}

void			air::os::Screen::buildGraphicContext(void)
{
  XGCValues		gcVal;

  gcVal.function	= GXcopy;
  gcVal.plane_mask	= AllPlanes;
  gcVal.foreground	= WhitePixel(m_display, 0);
  gcVal.background	= BlackPixel(m_display, 0);
  gcVal.line_width	= 1;
  gcVal.line_style	= LineSolid;
  gcVal.cap_style	= CapButt;
  gcVal.join_style	= JoinMiter;
  gcVal.fill_style	= FillOpaqueStippled;
  gcVal.fill_rule	= WindingRule;
  gcVal.graphics_exposures = False;
  gcVal.clip_x_origin	= 0;
  gcVal.clip_y_origin	= 0;
  gcVal.clip_mask	= None;
  gcVal.subwindow_mode	= IncludeInferiors;

  m_gc = XCreateGC(m_display, m_pixmapBuffer, 
		   GCFunction | GCPlaneMask |  GCForeground | 
		   GCBackground | GCLineWidth | GCLineStyle |
		   GCCapStyle  | GCJoinStyle  |  GCFillStyle  |  
		   GCFillRule | GCClipXOrigin |  GCClipYOrigin  |  
		   GCClipMask  | GCSubwindowMode | GCGraphicsExposures, 
		   &gcVal);
}

Window			air::os::Screen::createInvisibleWin(int x, int y, 
							    int sizeX, int sizeY)
{
  XSetWindowAttributes	attr;
  unsigned long		mask;
  Visual		visual;
  
  attr.background_pixmap = None;
  attr.override_redirect = True;
  attr.backing_store = NotUseful;
  attr.save_under = False;
  
  mask = (CWBackPixmap | CWOverrideRedirect | CWBackingStore | CWSaveUnder);

  visual.visualid = CopyFromParent;

  return XCreateWindow(m_display, m_rootWindow, x, y, sizeX, sizeY,
		       0, DefaultDepth(m_display, m_screen), 
		       InputOutput, &visual, mask, &attr);
}

void			air::os::Screen::restoreOSScreen(void)
{
  std::list<Rectangle>::iterator	begin = m_rectangles.begin();
  std::list<Rectangle>::iterator	end = m_rectangles.end();
  Window				refreshWin;

  while (begin != end)
    {
      // To redraw the drawn part of the screen, an invisible window of the desired 
      // size and placed at a given location is created, and is 'activated'
      // (XMapWindow) quickly to generate a refresh event at this place on the screen.

      refreshWin = createInvisibleWin(begin->x, begin->y, begin->sizeX, begin->sizeY);

      XMapWindow(m_display, refreshWin);
      XUnmapWindow(m_display, refreshWin);

      XDestroyWindow(m_display, refreshWin);

      if (begin->erased)
  	begin = m_rectangles.erase(begin);
      else
  	++begin;
    }
}

void			air::os::Screen::paintRectangles(void)
{
  std::list<Rectangle>::iterator	begin = m_rectangles.begin();
  std::list<Rectangle>::iterator	end = m_rectangles.end();
  XColor				xcolor;

  while (begin != end)
    {
      // Create XColor
      XParseColor(m_display, m_colorMap, 
		  begin->color.getRGBString().c_str(), &xcolor);
      XAllocColor(m_display, m_colorMap, &xcolor);
      XSetForeground(m_display, m_gc, xcolor.pixel);

      // Draw to buffer
      XFillRectangle(m_display, m_pixmapBuffer, m_gc, 
		     0, 0, begin->sizeX, begin->sizeY);

      // Past buffer to entire window
      XCopyArea(m_display, m_pixmapBuffer, m_rootWindow, m_gc, 
		0, 0, begin->sizeX, begin->sizeY, begin->x, begin->y);

      // Free color
      XFreeColors(m_display, m_colorMap, &xcolor.pixel, 1, 0);  

      ++begin;
    }
}

void			air::os::Screen::paintAll(void)
{
  paintRectangles();
  // In future: paintCircles, paintPoints, etc
}

void			air::os::Screen::destroyXComponents(void)
{
  XFreePixmap(m_display, m_pixmapBuffer);
  XFreeGC(m_display, m_gc);
  XFreeColormap(m_display, m_colorMap);
  XCloseDisplay(m_display);
}

void			air::os::Screen::Run(void)
{
  sf::Clock		clock;
  float			fps = 1.f / _FPS;

  m_mutex.Lock();
  initializeXComponents();
  m_mutex.Unlock();

  while (m_threadRunning)
    {
      clock.Reset();

      m_mutex.Lock();

      restoreOSScreen();
      paintAll();

      m_mutex.Unlock();
      
      XFlush(m_display);
      
      sf::Sleep(fps - clock.GetElapsedTime());
    }

  m_mutex.Lock();
  destroyXComponents();
  m_mutex.Unlock();
}
