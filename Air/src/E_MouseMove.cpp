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

#include <SFML/Graphics.hpp>
#include <vector>
  class Valley
  {
  public:
    sf::Vector3f pos;
    float	angle;
    Valley(sf::Vector3f a, float b) {pos = a; angle = b;}
    ~Valley() {}
  };

void test(XnPoint3D & handPos)
{
  const XnDepthPixel * depth = g_openNI.getDepthGenerator().GetDepthMap();
  vector<sf::Vector3f> contour;

  depth += 479 * 640;
  for (int y = 480; y > 0; y--)
    {
      for (int x = 0; x < 640; x++)
	{
	  if (abs((int) (x - handPos.X)) <= 75 &&
	      abs((int) (y - handPos.Y)) <= 100)
	    {
	      if ((abs(*depth - *(depth - 1)) >= 100 ||
	      	  abs(*depth - *(depth + 1)) >= 100) &&
		  abs((int) handPos.Z - *depth) <= 100)
		{
		  contour.push_back(sf::Vector3f(x, y, *depth));
		  //g_viewer.addPoint(x, y, "black");
		}
	    }
	  depth++;
	}
      depth -= 640 * 2;
    }

  std::vector<sf::Vector3f> newL;
  newL.push_back(contour[0]);
  contour.erase(contour.begin());
  float min;
  float dist;
  int minPos;
  while (!contour.empty())
    {
      min = -1;
      sf::Vector3f lastMin = newL.back();
      for (int i = 0; i < contour.size(); i++)
  	{
  	  float xd = contour[i].x - lastMin.x;
  	  float yd = contour[i].y - lastMin.y;
  	  dist = sqrt(xd * xd + yd * yd);
  	  if (dist < min || min == -1)
  	    {
  	      min = dist;
  	      minPos = i;
	      //	      printf("save\n");
  	    }
  	}
      newL.push_back(contour[minPos]);
      contour.erase(contour.begin() + minPos);
    }
  
  for (int i = 0; i < newL.size(); i++)
    {
      //g_viewer.addCircle((int)newL[i].x, (int)newL[i].y, 3, (const char *) "red");
      g_viewer.addPoint(newL[i].x, newL[i].y, "black");
    }

#define VECDIS 16
#define ANGLE 60

  vector<Valley> pretenders;
  for (int i = 0; i < newL.size(); i++)
    {
      if (i > VECDIS && i < (newL.size() - VECDIS * 2))
	{
	  sf::Vector3f curr = newL[i];
	  sf::Vector3f prev = newL[i - VECDIS];
	  sf::Vector3f next = newL[i + VECDIS];

	  sf::Vector3f V1(prev.x - curr.x, prev.y - curr.y, prev.z - curr.z);
	  sf::Vector3f V2(next.x - curr.x, next.y - curr.y, next.z - curr.z);

	  float dotProduct = V1.x * V2.x + V1.y * V2.y;

	  float magnitude1 = sqrtf(V1.x * V1.x + V1.y * V1.y);
	  float magnitude2 = sqrtf(V2.x * V2.x + V2.y * V2.y);

	  float angle = (dotProduct / (magnitude1 * magnitude2));// Since a.b = |a||b| * cos(t)
	  angle = acosf(angle);
	  angle *= (180 / 3.14);

	  sf::Vector3f crossProduct(V1.y * V2.z - V1.z * V2.y, 
				    V1.z * V2.x - V1.x * V2.z,
				    V1.x * V2.y - V1.y * V2.x);
	  
	  if (angle < ANGLE && crossProduct.z < 0)
	    pretenders.push_back(Valley(curr, angle));
	  //g_viewer.addCircle((int)curr.x, (int)curr.y, 5, (const char *) "red");
	}
    }
#define SPACE 25
  vector<Valley> selected;
  for (int i = 0; i < pretenders.size(); i++)
    {
      if (selected.size() < 5)
	{
	  if (selected.size() == 0)
	    selected.push_back(pretenders[i]);
	  else
	    {
	      for (int j = 0; j < selected.size(); j++)
		{
		  float xd = pretenders[i].pos.x - selected[j].pos.x;
		  float yd = pretenders[i].pos.y - selected[j].pos.y;
		  float dist = sqrt(xd * xd + yd * yd);
		  if (dist > SPACE)
		    selected.push_back(pretenders[i]);
		}
	    }
	}
      else
	{
	  for (int j = 0; j < 5; j++)
	    {
	      float xd = pretenders[i].pos.x - selected[j].pos.x;
	      float yd = pretenders[i].pos.y - selected[j].pos.y;
	      float dist = sqrt(xd * xd + yd * yd);
	      if (pretenders[j].angle < selected[j].angle && dist > SPACE)
		{
		  // selected.erase(selected.begin() + j);
		  // selected.insert(selected.begin() + j, pretenders[i]);
		  selected[j] = pretenders[i];
		}
	    }
	}
    }

  for (int i = 0; i < selected.size(); i++)  
    g_viewer.addCircle((int)selected[i].pos.x, (int)selected[i].pos.y, 10, (const char *) "red");  
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
  //
  // test(projPos);
  //  test2(projPos);
  //test3(projPos);
  //

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
