#include "XnFingersExtractor.hpp"
#include "XnMath.hpp"


using namespace xn;


void		FingersExtractor::ExtractHandContour(DepthGenerator & depthGenerator, 
						     const XnPoint3D & handPosition)
{
  const XnDepthPixel *	depthMap;
  XnPoint3D		contourPoint;
  list<XnPoint3D>	contour;

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
		  contour.push_back(contourPoint);
		}
	    }
	  depthMap++;
	}
      depthMap -= 640 * 2;
    }

  SortContourPoints(contour);
}

void			FingersExtractor::SortContourPoints(list<XnPoint3D> & contour)
{
  float				dist;
  float				minDist;
  list<XnPoint3D>		sorted;
  list<XnPoint3D>::iterator	itBegin;
  list<XnPoint3D>::iterator	itEnd;
  list<XnPoint3D>::iterator	closestPoint;

  sorted.push_back(contour.front());
  contour.erase(contour.begin());
  while (!contour.empty())
    {
      minDist = -1;
      itBegin = contour.begin();
      itEnd = contour.end();
      while (itBegin != itEnd)
  	{
	  dist = Math::PointsDistance(*itBegin, sorted.back());
  	  if (minDist == -1 || dist < minDist)
  	    {
  	      minDist = dist;
  	      closestPoint = itBegin;
  	    }
	  ++itBegin;
  	}
      sorted.push_back(*closestPoint);
      contour.erase(closestPoint);
    }

  m_contour.assign(sorted.begin(), sorted.end());
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

void				FingersExtractor::GroupPeaksByLocation(void)
{
  HandPeak				peak;
  int					peaksDistance;
  bool					closePeakFound = true;
  list<HandPeak>::iterator		peaksBegin = m_peaks.begin();
  list<HandPeak>::iterator		peaksEnd = m_peaks.end();
  list<list<HandPeak> >::iterator	locBegin;
  list<list<HandPeak> >::iterator	locEnd;
  
  while (peaksBegin != peaksEnd)
    {
      peak = *peaksBegin;
      if (m_peaksPerLocation.empty() || closePeakFound == false)
	{
	  m_peaksPerLocation.push_back(list<HandPeak>());
	  m_peaksPerLocation.back().push_back(peak);
	}
      
      closePeakFound = false;
      locBegin = m_peaksPerLocation.begin();
      locEnd = m_peaksPerLocation.end();
      while (locBegin != locEnd && closePeakFound == false)
      	{
      	  peaksDistance = Math::PointsDistance(peak.Position, 
					       locBegin->front().Position);
      	  if (peaksDistance < PEAK_LOCATION_LENGTH)
      	    {
      	      locBegin->push_back(peak);
      	      closePeakFound = true;
      	    }
	  ++locBegin;
      	}

      ++peaksBegin;
    }
}

void			FingersExtractor::SelectGroupBestPeaks(void)
{
  HandPeak				bestPeak;
  list<HandPeak>::iterator		peaksBegin;
  list<HandPeak>::iterator		peaksEnd;
  list<list<HandPeak> >::iterator	locBegin = m_peaksPerLocation.begin();
  list<list<HandPeak> >::iterator	locEnd = m_peaksPerLocation.end();

  while (locBegin != locEnd)
    {
      bestPeak = locBegin->front();

      peaksBegin = locBegin->begin();
      peaksEnd = locBegin->end();
      while (peaksBegin != peaksEnd)
  	{
  	  if (peaksBegin->Angle < bestPeak.Angle)
  	    bestPeak = *peaksBegin;
	  ++peaksBegin;
  	}

      m_selectedPeaks.push_back(bestPeak);
      ++locBegin;
    }
}

FingersData *		FingersExtractor::GenerateFingersData(void)
{
  FingersData *			data;
  list<HandPeak>::iterator	itBegin = m_selectedPeaks.begin();
  list<HandPeak>::iterator	itEnd = m_selectedPeaks.end();
  
  data = new FingersData();
  data->Size = m_selectedPeaks.size();
  data->Fingers = new XnVector3D[data->Size];
  
  for (int i = 0; itBegin != itEnd; i++)
    {
      memcpy(&data->Fingers[i], &(*itBegin), sizeof(FingersData));
      ++itBegin;
    }
  
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
