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
  float			vectorsAngle;

  int			stop = m_contour.size() - PEAK_VECTORS_LENGTH;

  for (int i = PEAK_VECTORS_LENGTH; i < stop; i++)
    {
      cur = m_contour[i];
      pre = m_contour[i - PEAK_VECTORS_LENGTH];
      nex = m_contour[i + PEAK_VECTORS_LENGTH];
      
      v1 = Math::PointsVector(cur, pre);
      v2 = Math::PointsVector(cur, nex);

      vectorsAngle = Math::VectorsAngle(v1, v2);

      if (vectorsAngle < PEAK_SELECTION_ANGLE && 
	  v1.Y > 0 && v2.Y > 0)
	m_peaks.push_back(HandPeak(cur, vectorsAngle));
    }
}

void			FingersExtractor::GroupPeaksByLocation(void)
{
  HandPeak			peak;
  int				nbOfPeaks;
  int				nbOfLocations;
  int				peaksDistance;
  bool				closePeakFound = true;
    
  nbOfPeaks = m_peaks.size();
  for (int i = 0; i < nbOfPeaks; i++)
    {
      peak = m_peaks[i];
      if (m_peaksPerLocation.empty() || closePeakFound == false)
	{
	  m_peaksPerLocation.push_back(vector<HandPeak>());
	  m_peaksPerLocation.back().push_back(peak);
	}
      
      closePeakFound = false;
      nbOfLocations = m_peaksPerLocation.size();
      for (int j = 0; j < nbOfLocations && closePeakFound == false; j++)
      	{
      	  peaksDistance = Math::PointsDistance(peak.Position, 
      					       m_peaksPerLocation[j].back().Position);
      	  if (peaksDistance < PEAK_LOCATION_LENGTH)
      	    {
      	      m_peaksPerLocation[j].push_back(peak);
      	      closePeakFound = true;
      	    }
      	}
    }

}

void			FingersExtractor::SelectGroupBestPeaks(void)
{
  HandPeak		bestPeak;
  int			nbOfLocation = m_peaksPerLocation.size();
  int			nbOfPeaks;

  for (int i = 0; i < nbOfLocation; i++)
    {
      bestPeak = m_peaksPerLocation[i][0];
      nbOfPeaks = m_peaksPerLocation[i].size();
      for (int j = 1; j < nbOfPeaks; j++)
	{
	  if (m_peaksPerLocation[i][j].Angle < bestPeak.Angle)
	    bestPeak = m_peaksPerLocation[i][j];
	}
      m_selectedPeaks.push_back(bestPeak);
    }
}

FingersData *		FingersExtractor::GenerateFingersData(void)
{
  FingersData *		data;
  
  data = new FingersData();
  data->Size = m_selectedPeaks.size();
  data->Fingers = new XnVector3D[data->Size];
  
  for (int i = 0; i < data->Size; i++)
    memcpy(&data->Fingers[i], &m_selectedPeaks[i], sizeof(FingersData));
  
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
  GroupPeaksByLocation();
  SelectGroupBestPeaks();

  fingersData = GenerateFingersData();

  ClearAll();

  return fingersData;
}

void			FingersExtractor::ClearAll(void)
{
  m_contour.clear();
  m_peaks.clear();
  m_peaksPerLocation.clear();
  m_selectedPeaks.clear();
}
