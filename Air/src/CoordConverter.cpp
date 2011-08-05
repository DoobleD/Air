#include "CoordConverter.hpp"

#include "OpenNIBox.hpp"
#include "Screen.hpp"

using namespace air;

extern OpenNIBox	g_openNI;


XnPoint3D		CoordConverter::realWorldToScreenSize(XnPoint3D point)
{
  int			XRes;
  int			YRes;
  XnPoint3D		prop;
  XnPoint3D		projPos;
  xn::DepthMetaData	depthMD;
  static os::Screen	screen;

  g_openNI.getDepthGenerator().GetMetaData(depthMD);
  g_openNI.getDepthGenerator().ConvertRealWorldToProjective(1, 
  							    &point, 
  							    &projPos);
  XRes = depthMD.XRes();
  YRes = depthMD.YRes();

  prop.X = projPos.X / XRes * screen.getResX();
  prop.Y = projPos.Y / YRes * screen.getResY();
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
