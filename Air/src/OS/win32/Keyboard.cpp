#include <windows.h>

#include "OS/Keyboard.hpp"


using namespace air::os;


int IKeyboard::AltLeft = VK_LMENU;
int IKeyboard::ShiftLeft = VK_LSHIFT;
int IKeyboard::SuperLeft = VK_LWIN;
int IKeyboard::Escape = VK_ESCAPE;
int IKeyboard::Tab = VK_TAB;
int IKeyboard::F9 = VK_F9;
int IKeyboard::F10 = VK_F10;
int IKeyboard::D = VkKeyScan('D');
int IKeyboard::Up = VK_UP;
int IKeyboard::Down = VK_DOWN;


void		Keyboard::keyPress(int key)
{
  keybd_event(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), 0, 0);
}

void		Keyboard::keyRelease(int key)
{
  keybd_event(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), KEYEVENTF_KEYUP, 0);
}
