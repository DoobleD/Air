#ifndef _NOT_KEYBOARD_HPP_
#define _NOT_KEYBOARD_HPP_

#ifdef __unix__
#include "OS/unix/Keyboard.hpp"
#elif defined _WIN32
#include "OS/win32/Keyboard.hpp"
#endif

#endif //_NOT_KEYBOARD_HPP_
