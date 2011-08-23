#ifndef _ERROR_HPP_
#define _ERROR_HPP_


#include <string>


////////////////////////////////////////////
// Defines errors macros and definitions //
//////////////////////////////////////////

/**
 * Check the OpenNI return status returned by most functions.
 * If the status is not valid (= XN_STATUS_OK), throw an
 * exception with a string containing the status of the error.
 *
 * @author OpenNI, modified by Pierre Alletru
 */
#define CHECK_RS(rs, what)			\
  if (rs != XN_STATUS_OK)			\
    {						\
      std::string s(what);			\
      s += " failed: ";				\
      s += xnGetStatusString(rs);		\
      throw s;					\
    }

#endif //_ERROR_HPP_
