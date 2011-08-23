#ifndef _NOT_KEYBOARD_HPP_
#define _NOT_KEYBOARD_HPP_


/////////////////////////////////////////////////////////////////////
// Compiles only the paltform specific implementation of IKeyboard //
/////////////////////////////////////////////////////////////////////


#ifdef __unix__

#include "OS/unix/Keyboard.hpp"

#elif defined _WIN32

#include "OS/win32/Keyboard.hpp"

#endif


#endif //_NOT_KEYBOARD_HPP_
