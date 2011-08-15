#include "XnFingersExtractor.hpp"
#include "XnMath.hpp"


using namespace xn;


list<HandPeak>	FingersExtractor::m_selectedPeaks;


FingersExtractor::FingersExtractor(void) : m_persitence(NO_CLIPPING_MIN_FRAMES)
{
}

FingersExtractor::~FingersExtractor(void)
{
}

bool		FingersExtractor::IsBorderPoint(int x, int y, 
						const XnDepthPixel * depthMap)
{
  if (x < 0 || x > m_XRes || y < 0 || y > m_YRes)
    return false;  

  if (depthMap == NULL)
    {
      depthMap = m_depthMap;
      depthMap += y * m_XRes + x;
    }

  // Check points
  // . . . 
  // x   x
  // . . .
  if (x > 0 && 
      abs(*depthMap - *(depthMap - 1)) > CONTOUR_DEPTH_DISTANCE)
    return true;
  if (x < m_XRes && 
	  abs(*depthMap - *(depthMap + 1)) > CONTOUR_DEPTH_DISTANCE)
    return true;

  // Check points
  // . x . 
  // .   .
  // . x .
  if (y > 0 && 
      abs(*depthMap - *(depthMap - m_XRes)) > CONTOUR_DEPTH_DISTANCE)
    return true;
  if (y < m_YRes && 
      abs(*depthMap - *(depthMap + m_XRes)) > CONTOUR_DEPTH_DISTANCE)
    return true;

  return false;
}

bool		FingersExtractor::IsHandPoint(int x, int y,
					      const XnDepthPixel * depthMap)
{
  int		depthDiff;

  if (x < 0 || x > m_XRes || y < 0 || y > m_YRes)
    return false;  
  
  if (depthMap == NULL)
    {
      depthMap = m_depthMap;
      depthMap += y * m_XRes + x;
    }

  depthDiff = abs((int) m_handPosition.Z - *depthMap);
  
  return depthDiff <= CONTOUR_DEPTH_DISTANCE;
}

void			FingersExtractor::ExtractHandContour(void)
{
  list<Point3Df>	contour;
  const XnDepthPixel *	depthMap = m_depthMap;
  int			distanceToHandPos[2];
  int			handWindow[2];

  handWindow[0] = HAND_WINDOW_X_MAX - (int) m_distRatio * HAND_WINDOW_X_MAX;
  handWindow[1] = HAND_WINDOW_X_MAX - (int) m_distRatio * HAND_WINDOW_X_MAX;

  depthMap += 479 * m_XRes;
  for (int y = m_YRes; y > 0; y--)
    {
      for (int x = 0; x < m_XRes; x++)
	{
	  distanceToHandPos[0] = abs((int) (x - m_handPosition.X));
	  distanceToHandPos[1] = abs((int) (y - m_handPosition.Y));

	  if (distanceToHandPos[0] <= handWindow[0] &&
	      distanceToHandPos[1] <= handWindow[1])
	    {
	      if (IsHandPoint(x, y, depthMap) && 
		  IsBorderPoint(x, y, depthMap))
		contour.push_back(Point3Df((float) x, (float) y, (float) *depthMap));
	    }
	  depthMap++;
	}
      depthMap -= m_XRes * 2;
    }

  SortContourPoints(contour);
}

void			FingersExtractor::SortContourPoints(list<Point3Df> & contour)
{
  float				dist;
  list<Point3Df>		sorted;
  list<Point3Df>::iterator	closest;
  
  sorted.push_back(contour.front());
  contour.erase(contour.begin());
  while (!contour.empty())
    {
      dist = math::PointsClosest2D_BruteForce<Point3Df>(contour.begin(), 
							contour.end(),
      							sorted.back(), closest);
      
      if (dist < 10)  // Avoid keeping some forgot points
      	sorted.push_back(*closest);
      else if (contour.size() > 100) // Hand is turned, reverse to keep right order
	sorted.reverse();

      contour.erase(closest);
    }
  
  m_contour.assign(sorted.begin(), sorted.end());
}

void			FingersExtractor::SetHandCenterAndOrientation(void)
{
  // Set center

  Point2Df		base1 = m_contour.front();
  Point2Df		base2 = m_contour.back();
  Point2Df		handPos(m_handPosition.X, m_handPosition.Y);
  Point2Df		baseCenter;
  Point2Df		handCenter;
 
  baseCenter = math::PointsCenter(base1, base2);
  handCenter = math::PointsCenter(baseCenter, handPos);

  m_handCenter.X = handCenter.X;
  m_handCenter.Y = handCenter.Y;
  m_handCenter.Z = m_handPosition.Z;

  // Set orientation
  Vector2Df		v1;
  Vector2Df		v2;
  Point2Df		YAxisInvert(handCenter.X, 0);

  v1 = math::PointsVector(baseCenter, handCenter);
  v2 = math::PointsVector(baseCenter, YAxisInvert);

  m_handAngle = math::VectorsAngle(v1, v2);
  if (baseCenter.X < handCenter.X)
    m_handAngle = -m_handAngle;
}

bool			FingersExtractor::IsValley(const Point2Df & point)
{
  int			startX = (int) point.X - VALLEY_AREA_MID_SIZE;
  int			startY = (int)point.Y - VALLEY_AREA_MID_SIZE;
  int			endX = (int) point.X + VALLEY_AREA_MID_SIZE;
  int			endY = (int) point.Y + VALLEY_AREA_MID_SIZE;
  int			nbOfHandPoint = 0;
  int			areaSize = VALLEY_AREA_MID_SIZE * 2;

  areaSize *= areaSize;

  if (startX < 0)
    startX = 0;
  if (startY < 0)
    startY  = 0;
  if (endX > m_XRes)
    endX = m_XRes;
  if (endY > m_YRes)
    endY = m_YRes;
    
  while (startY < endY)
    {
      for (int _startX = startX; _startX < endX; _startX++)
	{
	  if (IsHandPoint(_startX, startY))
	    nbOfHandPoint++;
	}
      startY++;
    }

  return ((float) nbOfHandPoint / (float) areaSize) > VALLEY_RATIO_OF_HANDP;
}

void			FingersExtractor::LocateContourPeaks(void)
{
  Point3Df		cur;
  Point3Df		pre;
  Point3Df		nex;

  Vector2Df		v1;
  Vector2Df		v2;
  float			vectorsAngle;

  int			vectorLength;
  int			stop;

  vectorLength = PEAK_VECTORS_LENGTH_MAX - (int) m_distRatio * PEAK_VECTORS_LENGTH_MAX;
  stop = m_contour.size() - vectorLength;
  for (int i = vectorLength; i < stop; i++)
    {
      cur = m_contour[i];
      pre = m_contour[i - vectorLength];
      nex = m_contour[i + vectorLength];      

      v1 = math::PointsVector(cur, pre);
      v2 = math::PointsVector(cur, nex);

      vectorsAngle = math::VectorsAngle(v1, v2);

      if (vectorsAngle < PEAK_SELECTION_ANGLE && !IsValley(cur))
	m_peaks.push_back(HandPeak(cur, vectorsAngle));
    }
}

bool					FingersExtractor::SameLocationPeaks(HandPeak a,
									    HandPeak b)
{
  static int				locationLength = PEAK_LOCATION_LENGTH_MAX - 
					(int) m_distRatio * PEAK_LOCATION_LENGTH_MAX;

  float					peaksDistance;

  peaksDistance = math::PointsDistance((Point2Df) a.Position, 
				       (Point2Df) b.Position);

  return peaksDistance < locationLength;
}

void					FingersExtractor::GroupPeaksByLocation(void)
{
  HandPeak				peak;
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
      	  if (SameLocationPeaks(peak, locBegin->front()))
      	    {
      	      locBegin->push_back(peak);
      	      closePeakFound = true;
      	    }
	  ++locBegin;
      	}

      ++peaksBegin;
    }
}

void					FingersExtractor::SelectGroupBestPeaks(void)
{
  HandPeak				bestPeak;
  list<HandPeak>			selected;
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

      selected.push_back(bestPeak);
      ++locBegin;
    }

  if (m_selectedPeaks.empty() || !m_persitence) // First detection or no persistence
    m_selectedPeaks.assign(selected.begin(), selected.end());
  else
    AvoidClipping(selected);
}

void				FingersExtractor::AvoidClipping(list<HandPeak> & selected)
{
  // Current frame peaks
  list<HandPeak>::iterator	sBegin = selected.begin();
  list<HandPeak>::iterator	sEnd = selected.end();

  // Previous frame peaks
  list<HandPeak>::iterator	pBegin;
  list<HandPeak>::iterator	pEnd;

  list<HandPeak>		noClipping;
  bool				found;

  while (sBegin != sEnd)
    {
      found = false;
      pBegin = m_selectedPeaks.begin();
      pEnd = m_selectedPeaks.end();

      while (pBegin != pEnd && !found)
	{
      	  if (SameLocationPeaks(*sBegin, *pBegin))
	    {
	      sBegin->FramesVisible = pBegin->FramesVisible;
	      if (sBegin->FramesVisible < m_persitence)
		sBegin->FramesVisible++;
	      
	      noClipping.push_back(*sBegin);

	      sBegin = selected.erase(sBegin);
	      m_selectedPeaks.erase(pBegin);
	      found = true;
	    }

	  pBegin++;
	}
      
      if (!found)
	++sBegin;      
    }

  // New fingers appeared.
  if (!selected.empty()) 
    noClipping.insert(noClipping.end(), selected.begin(), selected.end());

  // Some fingers disappeared. 
  for (pBegin = m_selectedPeaks.begin(),
       pEnd = m_selectedPeaks.end(); pBegin != pEnd; pBegin++)
    {
      pBegin->FramesVisible--;
      if (pBegin->FramesVisible >= 0)
	noClipping.push_back(*pBegin);
    }
  
  m_selectedPeaks.clear();
  m_selectedPeaks.assign(noClipping.begin(), noClipping.end());
}

FingersData *			FingersExtractor::GenerateFingersData(DepthGenerator & depthGen)
{
  FingersData *			data;
  list<HandPeak>::iterator	begin = m_selectedPeaks.begin();
  list<HandPeak>::iterator	end = m_selectedPeaks.end();
  
  data = new FingersData();
  data->Size = m_selectedPeaks.size();
  data->Fingers = new XnVector3D[data->Size];
  data->Hand = m_handCenter;
  data->HandAngle = m_handAngle;
  
  depthGen.ConvertProjectiveToRealWorld(1, &data->Hand, &data->Hand);
  for (int i = 0; begin != end; i++)
    {
      data->Fingers[i].X = begin->Position.X;
      data->Fingers[i].Y = begin->Position.Y;
      data->Fingers[i].Z = begin->Position.Z;
      
      depthGen.ConvertProjectiveToRealWorld(1, &data->Fingers[i], &data->Fingers[i]);
      ++begin;
    }

  return data;
}
// #include <sys/time.h>
// #include <iostream>
FingersData *		FingersExtractor::Extract(xn::Context & context,
						  const XnPoint3D * handPosition)
{
  XnPoint3D		projPos;
  FingersData *		fingersData;
  DepthGenerator	depthGen;
  xn::DepthMetaData     depthMD;

  if (context.FindExistingNode(XN_NODE_TYPE_DEPTH, depthGen) != XN_STATUS_OK)
    return NULL;

  depthGen.ConvertRealWorldToProjective(1, handPosition, &projPos);

  depthGen.GetMetaData(depthMD);
  m_XRes = depthMD.XRes();
  m_YRes = depthMD.YRes();

  m_handPosition = projPos;
  m_depthMap = depthGen.GetDepthMap();
  m_distRatio = projPos.Z / 4000;

  // struct timeval t1;
  // struct timeval t2;
  // struct timeval t3;
  // struct timeval t4;
  // struct timeval t5;

  // gettimeofday(&t1, NULL);
  ExtractHandContour();
  SetHandCenterAndOrientation();
  // gettimeofday(&t2, NULL);
  LocateContourPeaks();
  // gettimeofday(&t3, NULL);
  GroupPeaksByLocation();
  // gettimeofday(&t4, NULL);
  SelectGroupBestPeaks();
  // gettimeofday(&t5, NULL);
  
  // std::cout << "1 " << t2.tv_usec - t1.tv_usec << std::endl;
  // std::cout << "2 " << t3.tv_usec - t2.tv_usec << std::endl;
  // std::cout << "3 " << t4.tv_usec - t3.tv_usec << std::endl;
  // std::cout << "4 " << t5.tv_usec - t4.tv_usec << std::endl;

  fingersData = GenerateFingersData(depthGen);

  Clear();

  return fingersData;
}

void			FingersExtractor::SetPersistence(int nbOfFrames)
{
  m_persitence = nbOfFrames;
}

void			FingersExtractor::Clear(void)
{
  m_contour.clear();
  m_peaks.clear();
  m_peaksPerLocation.clear();
}

void			FingersExtractor::Reset(void)
{
  Clear();

  m_persitence = NO_CLIPPING_MIN_FRAMES;
  m_selectedPeaks.clear();
}
