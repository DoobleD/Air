#include "Screen.hpp"

#include <stdlib.h>

// No use of 'using namespace air::os' to avoid conflict with a struct Screen form Xlib

air::os::Screen::Screen(void)
{
  m_display = XOpenDisplay(0);
  m_rootWindow = DefaultRootWindow(m_display);
  m_colorMap = DefaultColormap(m_display, 0);

  buildGraphicContext();
  buildRefreshWin();
}

air::os::Screen::~Screen(void)
{
  XFreeGC(m_display, m_gc);
  XDestroyWindow(m_display, m_refreshWin);
  XCloseDisplay(m_display);
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

  m_gc = XCreateGC(m_display, m_rootWindow, 
		   GCFunction | GCPlaneMask |  GCForeground | 
		   GCBackground | GCLineWidth | GCLineStyle |
		   GCCapStyle  | GCJoinStyle  |  GCFillStyle  |  
		   GCFillRule | GCClipXOrigin |  GCClipYOrigin  |  
		   GCClipMask  | GCSubwindowMode | GCGraphicsExposures, 
		   &gcVal);
}

void			air::os::Screen::buildRefreshWin(void)
{
  XSetWindowAttributes	attr;
  unsigned long		mask;
  Visual		visual;
  int			screen;
  
  screen = DefaultScreen(m_display);

  attr.background_pixmap = None;
  attr.override_redirect = True;
  attr.backing_store = NotUseful;
  attr.save_under = False;
  
  mask = (CWBackPixmap | CWOverrideRedirect | CWBackingStore | CWSaveUnder);

  visual.visualid = CopyFromParent;

  m_refreshWin = XCreateWindow(m_display, m_rootWindow, 0, 0, 1440, 900,
			       0, DefaultDepth(m_display, screen), 
			       InputOutput, &visual, mask, &attr);
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
  XUnmapWindow(m_display, m_refreshWin);
  XMapWindow (m_display, m_refreshWin);
}

void			air::os::Screen::drawDisc(int x, int y, int diameter, 
						  const air::Color & color)
{
  XColor		xcolor;

  // Set GC color
  XParseColor(m_display, m_colorMap, color.getRGBString().c_str(), &xcolor);
  XAllocColor(m_display, m_colorMap, &xcolor);
  XSetForeground(m_display, m_gc, xcolor.pixel);
  
  // Draw
  XFillArc(m_display, m_rootWindow, m_gc, x, y + diameter, 
	   diameter, diameter, 23040, 23040);
}

void			air::os::Screen::display(void)
{
  XFlush(m_display);
}
