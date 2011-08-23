#ifndef _NOT_SCREEN_HPP_
#define _NOT_SCREEN_HPP_


///////////////////////////////////////////////////////////////////
// Compiles only the paltform specific implementation of IScreen //
///////////////////////////////////////////////////////////////////


#ifdef __unix__

#include "OS/unix/Screen.hpp"

#elif defined _WIN32

#include "OS/win32/Screen.hpp"

#endif


#endif //_NOT_SCREEN_HPP_
