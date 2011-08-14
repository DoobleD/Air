#ifndef _XN_MATH_TEMPLATES_HPP_
#define _XN_MATH_TEMPLATES_HPP_

#include <list>


namespace xn
{
  namespace math
  {
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
