#include "CoordConverter.hpp"

#include "OpenNIBox.hpp"

using namespace air;

extern OpenNIBox	g_openNI;

os::Screen		CoordConverter::m_screen;

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
