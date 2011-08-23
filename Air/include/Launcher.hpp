#ifndef _LAUNCHER_HPP_
#define _LAUNCHER_HPP_

#include "OpenNIBox.hpp"
#include "NITEBox.hpp"
#include "SessionListener.hpp"


// Path the a default configuration file. Actually not used in the current version.
#define DEFAULT_CONF_FILE	"./conf/default.xml"


namespace air
{

  /**
   * Launch Air: initialize OpenNI & NITE, and start main loop.
   * Also launch the viewer when DEBUG_MOD is defined.
   *
   * @author Pierre Alletru
   */
  class				Launcher
  {
  private:

    // Contains callbacks relative to session events.
    SessionListener		m_sessionListener;

    /**
     * Initialize Air. Essentially initialize OpenNI & NITE software.
     */
    void			initilize(void);

    /**
     * Air main loop. Essentially wait for OpenNI data, and
     * update NITE's session for each frame.
     */
    void			run(void);

    /**
     * Shutdown Air. Essentially shutdown OpenNI.
     */
    void			shutdown(void);

  public:

    /**
     * The method to call to launch Air.
     */
    void			launch(void);
  };

}

#endif //_LAUNCHER_HPP_
