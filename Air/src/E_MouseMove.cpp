#include "E_MouseMove.hpp"
#include "Screen.hpp"
#include "CoordConverter.hpp"


using namespace air;


// Defines for coordinate positions.
#define	PX		0
#define PY		1


E_MouseMove::E_MouseMove() : XnVPointControl("MouseMove")
{
  os::Screen	screen;

  m_screenSize[PX] = screen.getResX();
  m_screenSize[PY] = screen.getResX();
  m_screenMidSize[PX] = m_screenSize[PX] / 2;
  m_screenMidSize[PY] = m_screenSize[PY] / 2;
}

E_MouseMove::~E_MouseMove()
{
}

void		E_MouseMove::OnPointCreate(const XnVHandPointContext * cxt)
{
}

void		E_MouseMove::OnPointUpdate(const XnVHandPointContext * cxt)
{
  XnPoint3D	prop;
  float		speed[2];
  
  prop = CoordConverter::realWorldToScreenSize(cxt->ptPosition);
  
  speed[PX] = (double) abs((int) prop.X - m_screenMidSize[PX]) / 
    (double) m_screenMidSize[PX] * SPEED_FACTOR;
  speed[PY] = (double) abs((int) prop.Y - m_screenMidSize[PY]) / 
    (double)m_screenMidSize[PY] * SPEED_FACTOR;
  
  if (prop.X <= m_screenMidSize[PX])
    prop.X -= speed[PX] * prop.X;
  else
    prop.X += speed[PX] * prop.X;
  if (prop.Y <= m_screenMidSize[PY])
    prop.Y -= speed[PY] * prop.Y;
  else
    prop.Y += speed[PY] * prop.Y;

  m_mouse.setPosition(prop.X, prop.Y);
}

void		E_MouseMove::OnPointDestroy(XnUInt32 nID)
{
}
