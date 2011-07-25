#ifndef _XN_FINGERS_EXTRACTOR_HPP_
#define _XN_FINGERS_EXTRACTOR_HPP_

#include <XnCppWrapper.h>

#include <list>
#include <vector>

#include "XnFingerTypes.hpp"

#define VECTORS_LENGTH	16
#define SELECTION_ANGLE	60


using namespace std;


namespace xn
{
 
  class			FingersExtractor
  {
  private:
    vector<XnPoint3D>	m_contour;
    vector<HandPeak>	m_handPeaks;

    void		ExtractHandContour(DepthGenerator & depthGenerator, 
					   const XnPoint3D & handPosition);
    void		SortContourPoints(void);
    void		LocateContourPeaks(void);
    FingersData *	GenerateFingersData(void);
    void		ClearAll(void);

  public:
    FingersData *	Extract(xn::Context & context, 
				const XnPoint3D * handPosition);
  };
  
}

#endif //_XN_FINGERS_EXTRACTOR_HPP_
