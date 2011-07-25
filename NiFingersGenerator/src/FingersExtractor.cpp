#include "XnFingersExtractor.hpp"
#include "XnMath.hpp"


using namespace xn;


void		FingersExtractor::ExtractHandContour(DepthGenerator & depthGenerator, 
						     const XnPoint3D & handPosition)
{
  const XnDepthPixel *	depthMap;
  XnPoint3D		contourPoint;

  depthMap = depthGenerator.GetDepthMap();
  depthMap += 479 * 640;
  for (int y = 480; y > 0; y--)
    {
      for (int x = 0; x < 640; x++)
	{
	  if (abs((int) (x - handPosition.X)) <= 75 &&
	      abs((int) (y - handPosition.Y)) <= 100)
	    {
	      if ((abs(*depthMap - *(depthMap - 1)) >= 100 ||
		   abs(*depthMap - *(depthMap + 1)) >= 100) &&
		  abs((int) handPosition.Z - *depthMap) <= 100)
		{
		  contourPoint.X = x;
		  contourPoint.Y = y;
		  contourPoint.Z = *depthMap;
		  m_contour.push_back(contourPoint);
		}
	    }
	  depthMap++;
	}
      depthMap -= 640 * 2;
    }
}

void			FingersExtractor::SortContourPoints(void)
{
  vector<XnPoint3D>	tmpSorted;
  float			minDist;
  float			dist;
  int			minPos;

  tmpSorted.push_back(m_contour[0]);
  m_contour.erase(m_contour.begin());
  while (!m_contour.empty())
    {
      minDist = -1;
      for (int i = 0; i < m_contour.size(); i++)
  	{
  	  dist = Math::PointsDistance(m_contour[i], tmpSorted.back());
  	  if (dist < minDist || minDist == -1)
  	    {
  	      minDist = dist;
  	      minPos = i;
  	    }
  	}
      tmpSorted.push_back(m_contour[minPos]);
      m_contour.erase(m_contour.begin() + minPos);
    }

  m_contour.swap(tmpSorted);
}

void			FingersExtractor::LocateContourPeaks(void)
{
  XnPoint3D		cur;
  XnPoint3D		pre;
  XnPoint3D		nex;

  XnVector3D		v1;
  XnVector3D		v2;
  XnVector3D		crossProduct;
  float			vectorsAngle;

  int			stop = m_contour.size() - VECTORS_LENGTH;

  for (int i = VECTORS_LENGTH; i < stop; i++)
    {
      cur = m_contour[i];
      pre = m_contour[i - VECTORS_LENGTH];
      nex = m_contour[i + VECTORS_LENGTH];
      
      v1 = Math::PointsVector(cur, pre);
      v2 = Math::PointsVector(cur, nex);

      vectorsAngle = Math::VectorsAngle(v1, v2);
      crossProduct = Math::VectorsCrossProduct(v1, v2);

      if (vectorsAngle < SELECTION_ANGLE && crossProduct.Z < 0)
	m_handPeaks.push_back(HandPeak(cur, vectorsAngle));
    }
}

FingersData *		FingersExtractor::GenerateFingersData(void)
{
  FingersData *		data;

  data = new FingersData();
  data->Size = m_handPeaks.size();
  data->Fingers = new XnVector3D[data->Size];

  for (int i = 0; i < data->Size; i++)
    memcpy(&data->Fingers[i], &m_handPeaks[i], sizeof(FingersData));

  return data;
}

FingersData *		FingersExtractor::Extract(xn::Context & context,
						  const XnPoint3D * handPosition)
{
  XnPoint3D		projPos;
  FingersData *		fingersData;
  DepthGenerator	depthGen;

  if (context.FindExistingNode(XN_NODE_TYPE_DEPTH, depthGen) != XN_STATUS_OK)
    return NULL;

  depthGen.ConvertRealWorldToProjective(1, handPosition, &projPos);

  ExtractHandContour(depthGen, projPos);
  SortContourPoints();
  LocateContourPeaks();

  fingersData = GenerateFingersData();

  ClearAll();

  return fingersData;
}

void			FingersExtractor::ClearAll(void)
{
  m_contour.clear();
  m_handPeaks.clear();
}
