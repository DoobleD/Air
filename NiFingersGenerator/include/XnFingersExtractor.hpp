#ifndef _XN_FINGERS_EXTRACTOR_HPP_
#define _XN_FINGERS_EXTRACTOR_HPP_

#include <XnCppWrapper.h>

#include <list>
#include <vector>

#include "XnFingerTypes.hpp"

#define PEAK_VECTORS_LENGTH	16
#define PEAK_SELECTION_ANGLE	60
#define PEAK_LOCATION_LENGTH	15

using namespace std;


namespace xn
{
 
  class				FingersExtractor
  {
  private:
    vector<XnPoint3D>		m_contour;
    list<HandPeak>		m_peaks;
    list<list<HandPeak> >	m_peaksPerLocation;
    list<HandPeak>		m_selectedPeaks;

    void			ExtractHandContour(DepthGenerator & depthGenerator, 
						   const XnPoint3D & handPosition);
    void			SortContourPoints(list<XnPoint3D> & contour);
    void			LocateContourPeaks(void);
    void			GroupPeaksByLocation(void);
    void			SelectGroupBestPeaks(void);
    FingersData *		GenerateFingersData(void);
    void			ClearAll(void);

  public:
    FingersData *		Extract(xn::Context & context, 
					const XnPoint3D * handPosition);
  };
  
}

#endif //_XN_FINGERS_EXTRACTOR_HPP_
