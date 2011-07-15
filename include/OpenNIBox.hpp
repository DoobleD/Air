#ifndef _OPEN_NI_BOX_HPP_
#define _OPEN_NI_BOX_HPP_

// OpenNI headers
#include <XnCppWrapper.h>

namespace air
{
  class				OpenNIBox
  {
  private:
    xn::Context			m_context;
    xn::GestureGenerator	m_gestureGenerator;
    xn::HandsGenerator		m_handsGenerator;
    xn::DepthGenerator		m_depthGenerator;
    xn::EnumerationErrors	m_errors;

  public:
    void			initialize(void);
    void			run();
    void			stop(void);
    xn::Context &		getContext(void);
    xn::DepthGenerator &	getDepthGenerator(void);
  };

}


#endif //_OPEN_NI_BOX_HPP_
