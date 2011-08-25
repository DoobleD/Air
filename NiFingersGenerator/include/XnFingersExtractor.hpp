#ifndef _XN_FINGERS_EXTRACTOR_HPP_
#define _XN_FINGERS_EXTRACTOR_HPP_


#include <list>
#include <vector>

#include <XnCppWrapper.h>

#include "XnFingerTypes.hpp"


// Max z distance view of the sensor in mm
#define DEPTH_MAX_DIST			4000

// Defines the window in which is the hand
#define HAND_WINDOW_X_MAX		150
#define HAND_WINDOW_Y_MAX		125

// A point is a contour point if it has a minimal depth distance with adjacent points
#define CONTOUR_DEPTH_DISTANCE		75

// Selection criterion of contour peaks and valley
#define PEAK_VECTORS_LENGTH_MAX		25 // The length of contour vectors
#define PEAK_LOCATION_LENGTH_MAX	25 // The width of a finger peaks location
#define PEAK_SELECTION_ANGLE		60 // Contour peaks & valley max angle

// Defines the ratio of hand points for a valley
#define VALLEY_RATIO_OF_HANDP		0.5
#define VALLEY_AREA_MID_SIZE		10

// Default persistence : if a peak disappears, it stays a few frames, to avoid clipping
#define PERSISTENCE_FRAMES		2

// Size of the previous peaks locations recoring (used for smoothing)
#define PREV_FINGERS_SAVE		1

// If a peak has a distance with its previous position inferior to SMOOTH_DISTANCE,
// it is setted to its previous position, and therefore doesn't move.
#define SMOOTH_DISTANCE			5


using namespace std;


namespace xn
{
 
  /**
   * Extract finger tips from a hand, given the OpenNI context
   * and the hand position.
   *
   * @author Pierre ALletru
   */
  class				FingersExtractor
  {
  private:

    // The depth map of current frame
    const XnDepthPixel *	m_depthMap;

    // Hand contour points
    vector<Point3Df>		m_contour;
    // Hand peaks (= possible finger tips)
    list<HandPeak>		m_peaks;
    // Peaks grouped by their location
    list<list<HandPeak> >	m_peaksPerLocation;
    // Peaks selected as finger tips
    static list<HandPeak>	m_selectedPeaks;

    // OpenNI resolution
    int				m_XRes;
    int				m_YRes;

    // Peristence value can be changed by user & smooth can be activated/deactivated
    int				m_persistence;
    bool			m_smooth;

    // Ratio of distance between hand and depth sensor
    XnFloat			m_distRatio;
    // Orientation angle of the hand
    XnFloat			m_handAngle;
    // Hand position
    XnPoint3D			m_handPosition;
    // Palm position
    XnPoint3D			m_handCenter;

    /**
     * Check whether or not a point is a contour point. 
     *
     * @param x			x point coordinate.
     * @param y			y point coordinate.
     * @param depthMap		Optional. The depth map at the point position.
     *
     * @return true if point is a contour point, false otherwise.
     */
    bool			IsBorderPoint(int x, int y,
					      const XnDepthPixel * depthMap = NULL);

    /**
     * Check whether or not a point is a hand point. 
     *
     * @param x			x point coordinate.
     * @param y			y point coordinate.
     * @param depthMap		Optional. The depth map at the point position.
     *
     * @return true if point is a hand point, false otherwise.
     */
    bool			IsHandPoint(int x, int y,
					    const XnDepthPixel * depthMap = NULL);
    /**
     * Extract hand contour. Basically select points which are both contour points
     * and hand points within a window arround the hand position.
     */
    void			ExtractHandContour(void);

    /**
     * Order contour points based on the minimal distance between points.
     *
     * @param contour		List of contour points.
     */
    void			SortContourPoints(list<Point3Df> & contour);

    /**
     * Set information about palm position and hand orientation.
     */
    void			SetHandCenterAndOrientation(void);

    /**
     * Check whether or not a point is in a hand valley.
     *
     * @param point		A 2D point.
     *
     * @return true if point is in a hand valley, false otherwise.
     */
    bool			IsValley(const Point2Df & point);

    /**
     * Find hand contour peaks. Basically computes the angle of two vectors 
     * for each contour point, select angles below a certain value, and check they
     * are not valley points. The vectors are : 
     * - current point to a certain point forward in contour, and
     * - current point to a certain point backward in contour.
     */
    void			LocateContourPeaks(void);

    /**
     * Check whether or not two peaks are located in the same area 
     * (which represent a finger tip area).
     * 
     * @param a			A hand peak.
     * @param b			Another hand peak.
     *
     * @return true is peaks are in the same location, false otherwise.
     */
    bool			SameLocationPeaks(HandPeak a,HandPeak b);

    /**
     * Group peaks depending on their location. Each group represent the peaks
     * found on a single finger tip.
     */
    void			GroupPeaksByLocation(void);

    /**
     * Select each group best peak based on their angle value. Lower the angle,
     * higher the chance to select the angle.
     */
    void			SelectGroupBestPeaks(void);

    /**
     * Associates current peaks detected to their previous positions.
     *
     * @param selected		A list  of the peaks newly selected 
     *				for the current frame.
     */
    void			NewPeaksBindWithPrevious(list<HandPeak> & selected);

    /**
     * Smooth peaks movements. Actually set peaks to their previous positions
     * if they did not move too much. If they moved too far, use the center of mass
     * of their previous positions and actual positions.
     *
     * @param peaks		A list of the peaks to smooth.
     */
    void			SmoothPeaks(list<HandPeak> & peaks);

    /**
     * Creates the FingerData structure which will be send back to the user.
     * This structure contains the information relative to hand and fingers found.
     *
     * @param depthGen		The OpenNI depth generator.
     *
     * @return A pointer to a FingersData structure containing information on hand and
     * fingers.
     */
    FingersData *		GenerateFingersData(DepthGenerator & depthGen);

    /**
     * Clear internal data after fingers extraction is done.
     */
    void			Clear(void);

  public:

    /**
     * Default constructor.
     */
    FingersExtractor(void);
    
    /**
     * Destructor.
     */
    ~FingersExtractor(void);

    /**
     * Main method of the class. Extract fingers from a depth map, given
     * OpenNI context object and a hand position.
     * Basically extract hand contour, and select contour best peaks.
     *
     * @param context		OpenNI context.
     * @param handPosition	The position of a hand.
     *
     * @return A pointer to a FingersData structure containing information
     * about the fingers found and the hand.
     */
    FingersData *		Extract(xn::Context & context, 
					const XnPoint3D * handPosition);

    /**
     * Set the persistence of fingers. If a finger disappear, it is still "detected"
     * a few frames, to avoid abusive clipping.
     *
     * @param nbOfFrames	The number of frames a finger persist 
     *				after it disappeared.
     */
    void			SetPersistence(int nbOfFrames);

    /**
     * Activate or deactivate smoothing. Smoothing is deactivated by default.
     *
     * @param b			A boolean. True activates smoothing, 
     *				false deactivates it.
     */
    void			SetSmoothing(bool b);

    /**
     * Reset internal data to the default.
     */
    void			Reset(void);
  };
  
}

#endif //_XN_FINGERS_EXTRACTOR_HPP_
