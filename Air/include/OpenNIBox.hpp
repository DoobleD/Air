#ifndef _OPEN_NI_BOX_HPP_
#define _OPEN_NI_BOX_HPP_


// OpenNI header
#include <XnCppWrapper.h>

// Fingers generator OpenNI-compliant module
#include "XnFingersGenerator.hpp"


namespace air
{

  /**
   * Handle OpenNI operations and data.
   *
   * @author Pierre Alletru
   */
  class				OpenNIBox
  {
  private:
    
    xn::Context			m_context;
    xn::GestureGenerator	m_gestureGenerator;
    xn::HandsGenerator		m_handsGenerator;
    xn::DepthGenerator		m_depthGenerator;
    xn::FingersGenerator	m_fingersGenerator;
    xn::EnumerationErrors	m_errors;

  public:

    /**
     * Initialize OpenNI framework.
     */
    void			initialize(void);

    /**
     * Run OpenNI,updating session for each frame.
     */
    void			waitAndUpdate(void);

    /**
     * Stop and clean OpenNI.
     */
    void			stop(void);

    /**
     * Get the context.
     *
     * @return A reference to the OpenNI context object.
     */    
    xn::Context &		getContext(void);

    /**
     * Get the depth generator.
     *
     * @return A reference to the OpenNI depth generator object.
     */
    xn::DepthGenerator &	getDepthGenerator(void);

    /**
     * Get the fingers generator.
     *
     * @return A reference to the FingersGenerator object.
     */    
    xn::FingersGenerator &	getFingersGenerator(void);
  };

}


#endif //_OPEN_NI_BOX_HPP_
