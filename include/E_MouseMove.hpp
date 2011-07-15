#ifndef _E_MOUSE_MOVE_HPP_
#define _E_MOUSE_MOVE_HPP_

// OpenNI headers
#include <XnCppWrapper.h>

// NITE headers
#include <XnVPointControl.h>


#define SPEED_FACTOR	3


namespace air
{
  
  class			E_MouseMove : public XnVPointControl
  {
  private:
    unsigned int	m_XRes;
    unsigned int	m_YRes;
    int			m_screenSize[2];
    int			m_screenMidSize[2];

  public:
    E_MouseMove();
    ~E_MouseMove();

    void		OnPointCreate(const XnVHandPointContext* cxt);
    void		OnPointUpdate(const XnVHandPointContext* cxt);
    void		OnPointDestroy(XnUInt32 nID);
  };

}

#endif //_E_MOUSE_MOVE_HPP_
