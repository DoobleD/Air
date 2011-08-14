#ifndef _XN_FINGERS_EXTRACTOR_HPP_
#define _XN_FINGERS_EXTRACTOR_HPP_

#include "XnFingerTypes.hpp"

#include <XnCppWrapper.h>

#include <list>
#include <vector>


#define DEPTH_MAX_DIST			4000

#define HAND_WINDOW_X_MAX		150
#define HAND_WINDOW_Y_MAX		125

#define CONTOUR_DEPTH_DISTANCE		75

#define PEAK_VECTORS_LENGTH_MAX		25
#define PEAK_LOCATION_LENGTH_MAX	25
#define PEAK_SELECTION_ANGLE		70

#define VALLEY_RATIO_OF_HANDP		0.5
#define VALLEY_AREA_MID_SIZE		10


using namespace std;


namespace xn
{
 
  class				FingersExtractor
  {
  private:
    const XnDepthPixel *	m_depthMap;

    vector<Point3Df>		m_contour;
    list<HandPeak>		m_peaks;
    list<list<HandPeak> >	m_peaksPerLocation;
    list<HandPeak>		m_selectedPeaks;

    int				m_XRes;
    int				m_YRes;

    XnFloat			m_distRatio;
    XnFloat			m_handAngle;
    XnPoint3D			m_handPosition;
    XnPoint3D			m_handCenter;

    bool			IsBorderPoint(int x, int y,
					      const XnDepthPixel * depthMap = NULL);
    bool			IsHandPoint(int x, int y,
					    const XnDepthPixel * depthMap = NULL);
    void			ExtractHandContour(void);
    void			SortContourPoints(list<Point3Df> & contour);
    void			SetHandCenterAndOrientation(void);
    bool			IsValley(const Point2Df & point);
    void			LocateContourPeaks(void);
    void			GroupPeaksByLocation(void);
    void			SelectGroupBestPeaks(void);
    void			SmoothPeaks(void);
    FingersData *		GenerateFingersData(DepthGenerator & depthGen);
    void			ClearAll(void);

  public:
    FingersData *		Extract(xn::Context & context, 
					const XnPoint3D * handPosition);
  };
  
}

#endif //_XN_FINGERS_EXTRACTOR_HPP_
