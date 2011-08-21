#include "CoordConverter.hpp"

#include "OpenNIBox.hpp"

using namespace air;

extern OpenNIBox	g_openNI;



os::Screen		CoordConverter::m_screen;

// Defines for coordinate positions.
#define	PX		0
#define PY		1


XnPoint3D		CoordConverter::realWorldToScreenSize(XnPoint3D point)
{
  XnPoint3D		prop;
  XnPoint3D		projPos;
  xn::DepthMetaData	depthMD;

  g_openNI.getDepthGenerator().GetMetaData(depthMD);
  g_openNI.getDepthGenerator().ConvertRealWorldToProjective(1, 
  							    &point, 
  							    &projPos);
  prop.X = projPos.X / depthMD.XRes() * m_screen.getResX();
  prop.Y = projPos.Y / depthMD.YRes() * m_screen.getResY();
  prop.Z = projPos.Z;

  return prop;
}

XnPoint3D		CoordConverter::realWorldToNIScreen(XnPoint3D point)
{
  int			XRes;
  int			YRes;
  XnPoint3D		projPos;
  
  g_openNI.getDepthGenerator().ConvertRealWorldToProjective(1, 
  							    &point, 
  							    &projPos);
  return projPos;
}


XnPoint3D		CoordConverter::screenSizeToSpeedFactor(XnPoint3D point,
								int speedFactor)
{
  int			screenMidSize[2];
  float			speed[2];
  
  screenMidSize[PX] = m_screen.getResX() / 2;
  screenMidSize[PY] = m_screen.getResY() / 2;

  speed[PX] = (float) abs((int) point.X - screenMidSize[PX]) / 
    (float) screenMidSize[PX] * speedFactor;
  speed[PY] = (float) abs((int) point.Y - screenMidSize[PY]) / 
    (float) screenMidSize[PY] * speedFactor;
  
  if (point.X <= screenMidSize[PX])
    point.X -= speed[PX] * point.X;
  else
    point.X += speed[PX] * point.X;
  if (point.Y <= screenMidSize[PY])
    point.Y -= speed[PY] * point.Y;
  else
    point.Y += speed[PY] * point.Y;

  return point;
}
