#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

#define CHECK_RS(rs, what)			\
  if (rs != XN_STATUS_OK)			\
    {						\
      std::string s(what);			\
      s += " failed: ";				\
      s += xnGetStatusString(rs);		\
      throw s;					\
    }

#define CHECK_ERRORS(rs, errors, what)		\
  if (rs == XN_STATUS_NO_NODE_PRESENT)		\
    {						\
      XnChar strError[1024];			\
      errors.ToString(strError, 1024);		\
      throw strError;				\
    }

#endif //_ERROR_HPP_
