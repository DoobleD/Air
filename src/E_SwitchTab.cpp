#include "E_SwitchTab.hpp"

using namespace air;

E_SwitchTab::E_SwitchTab() : XnVCircleDetector("SwitchTab")
{
  RegisterCircle(NULL, &E_SwitchTab::onCircle);
}

E_SwitchTab::~E_SwitchTab()
{
}

void XN_CALLBACK_TYPE		E_SwitchTab::onCircle(XnFloat times, 
						      XnBool confident, 
						      const XnVCircle *circle, 
						      void *userCxt)
{
  printf("SWITCH TAB!\n");
}
