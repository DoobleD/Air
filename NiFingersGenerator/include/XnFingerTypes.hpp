#ifndef _XN_FINGER_TYPES_HPP_
#define _XN_FINGER_TYPES_HPP_


#include <list>

#include <XnTypes.h>


namespace xn
{
  ////////////////
  // Math types //
  ////////////////

  /**
   * Represent a point in a 2D carthesian plan.
   *
   * @author Pierre Alletru
   */
  struct			Point2Df
  {
    float			X;
    float			Y;

    Point2Df(void) {}
    Point2Df(float x, float y) {X = x; Y = y;}
  };

  /**
   * Represent a point in 3D.
   *
   * @author Pierre Alletru
   */
  struct			Point3Df : public Point2Df
  {
    float			Z;

    Point3Df(void) {}
    Point3Df(float x, float y, float z) : Point2Df(x, y) {X = x; Y = y; Z = z;}
  };


  typedef Point2Df		Vector2Df;
  typedef Point3Df		Vector3Df;


  ///////////////////////
  // More geneal types //
  ///////////////////////

  /**
   * Represent a hand peak.
   *
   * @author Pierre Alletru
   */
  struct			HandPeak
  {
    // Peak position.
    Point3Df			Position;
    // Peak angle.
    float			Angle;
    // Number of frames the peak has been detected.
    int				FramesVisible;
    // Previous positions of peaks, if any.
    std::list<Point3Df>		Previous;

    /**
     * Default constructor.
     */
    HandPeak(void) {}
    
    /**
     * Constructor.
     *
     * @param position		The position of the peak.
     * @param angle		The angle of the peak.
     */
    HandPeak(Point3Df position, float angle) 
    {Position = position; Angle = angle; FramesVisible = 0;}

    /**
     * Destructor.
     */
    ~HandPeak(void)
    {Previous.clear();}
  };
  
  /**
   * Contains information about detected fingers. Is filled by 
   * FingersExtractor and then is transmitted to user by FingersGenerator.
   *
   * @author Pierre Alletru
   */
  struct			FingersData
  {
    // An array of detected fingers positions.
    XnVector3D *		Fingers;
    // Position of the hand (center of the palm).
    XnVector3D			Hand;
    // Orientation angle of the hand.
    XnFloat			HandAngle;
    // Size of 'Fingers', the array of fingers 
    // (so represent the number of fingers detected).
    XnUInt32			Size;
    
    /**
     * Destructor.
     */
    ~FingersData() {delete Fingers;}
  };
  
}

#endif //_XN_FINGER_TYPES_HPP_
