#ifndef _XN_MATH_TEMPLATES_HPP_
#define _XN_MATH_TEMPLATES_HPP_


#include <list>


namespace xn
{
  namespace math
  {
    /**
     * Find the closest point to a given 2D point, using basic 
     * bruteforce algorithm (exhaustive research).
     *
     * Template function. Can use different types of 
     * points structure (e.g Point2Df, Point3Df, etc).
     *
     * @param begin	An iterator from a list of points, used to start research.
     * @param end	An iterator from a list of points, used as 
     *			an end point to stop researching.
     * @param point	The reference point used for the closest point research.
     * @param closest	A reference to an iterator of the type of the research list.
     *			This iterator will be set to the position of the closest point.
     *
     * @return The distance between the given point and the closest point found.
     */
    template<typename T> 
    float		PointsClosest2D_BruteForce(typename list<T>::iterator begin,
						   typename list<T>::iterator end, 
						   const T & point,
						   typename list<T>::iterator & closest)
    {
      float		dist;
      float		minDist;
  
      minDist = -1;
      while (begin != end)
	{
	  // Force 2D distance calculation, no matter what is the nb of dimension of T
	  dist = PointsDistance((Point2Df) *begin, (Point2Df) point);
	  if (minDist == -1 || dist < minDist)
	    {
	      minDist = dist;
	      closest = begin;
	    }
      
	  ++begin;
	}
  
      return minDist;
    }
  }
}

#endif //_XN_MATH_TEMPLATES_HPP_
