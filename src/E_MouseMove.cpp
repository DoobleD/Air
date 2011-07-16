#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif


#include <stdlib.h>

#include "E_MouseMove.hpp"
#include "OpenNIBox.hpp"
#include "Screen.hpp"

using namespace air;

extern OpenNIBox	g_openNI;

#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern Viewer		g_viewer;
#endif

// Defines for coordinate positions.
#define	PX		0
#define PY		1


E_MouseMove::E_MouseMove() : XnVPointControl("MouseMove")
{
  // TODO: multi-platform
  m_screenSize[PX] = m_screen.getResX();
  m_screenSize[PY] = m_screen.getResX();
  m_screenMidSize[PX] = m_screenSize[PX] / 2;
  m_screenMidSize[PY] = m_screenSize[PY] / 2;
}

E_MouseMove::~E_MouseMove()
{
}

void		E_MouseMove::OnPointCreate(const XnVHandPointContext * cxt)
{
  xn::DepthMetaData	depthMD;

  g_openNI.getDepthGenerator().GetMetaData(depthMD);

  m_YRes = depthMD.YRes();
  m_XRes = depthMD.XRes();
}

//TODO: optimize o)
void		E_MouseMove::OnPointUpdate(const XnVHandPointContext * cxt)
{
  XnPoint3D	projPos;
  double	prop[2];
  double	speed[2];
  
  g_openNI.getDepthGenerator().ConvertRealWorldToProjective(1, 
  							    &cxt->ptPosition, 
  							    &projPos);

#ifdef DEBUG_MOD
  g_viewer.setHandPosition(projPos.X, projPos.Y);
#endif
  
  prop[PX] = projPos.X / m_XRes * m_screenSize[PX];
  prop[PY] = projPos.Y / m_YRes * m_screenSize[PY];

  speed[PX] = (double) abs((int) prop[PX] - m_screenMidSize[PX]) / 
    (double) m_screenMidSize[PX] * SPEED_FACTOR;
  speed[PY] = (double) abs((int) prop[PY] - m_screenMidSize[PY]) / 
    (double)m_screenMidSize[PY] * SPEED_FACTOR;

  if (prop[PX] <= m_screenMidSize[PX])
    prop[PX] -= speed[PX] * prop[PX];
  else
    prop[PX] += speed[PX] * prop[PX];
  if (prop[PY] <= m_screenMidSize[PY])
    prop[PY] -= speed[PY] * prop[PY];
  else
    prop[PY] += speed[PY] * prop[PY];

  // TODO: multi-platform
  m_mouse.setPosition(prop[PX], prop[PY]);
}

void		E_MouseMove::OnPointDestroy(XnUInt32 nID)
{
}
