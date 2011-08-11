#ifndef _NOT_MOUSE_HPP_
#define _NOT_MOUSE_HPP_

#ifdef __unix__
#include "OS/unix/Mouse.hpp"
#elif defined _WIN32
#include "OS/win32/Mouse.hpp"
#endif

#endif //_NOT_MOUSE_HPP_
