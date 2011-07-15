#include <iostream>

#include "Launcher.hpp"
#include "Viewer.hpp"
#include "OpenNIBox.hpp"
#include "NITEBox.hpp"

using namespace air;

extern OpenNIBox	g_openNI;
extern NITEBox		g_NITE;

#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern Viewer		g_viewer;
#endif

void			Launcher::initilize(void)
{
  // Initialize OpenNI
  g_openNI.initialize();

  // Initialize NITE
  g_NITE.initialize(m_sessionListener);
}

void			Launcher::run(void)
{
  // Run OpenNI, updating NITE for each frame
  g_openNI.run();
}

void			Launcher::shutdown(void)
{
  // Stop OpenNI
  g_openNI.stop();
}

void			Launcher::launch(void)
{
  try
    {
      // Initilize OpenNI, Air and NITE components
      initilize();
    }
  catch (const std::string & e)
    {
      std::cerr << "Can't initilize Kinect software." << std::endl 
		<< "Please check that a Kinect is connected to the computer, " 
		<< "and plugged to power outlet." << std::endl;
      throw;
    }

#ifdef DEBUG_MOD
  try
    {
      g_viewer.launch();
    }
  catch (const std::string & e)
    {
      std::cerr << "Can't run the viewer." << std::endl;
    }
#endif
  
  // Main loop
  run();
  
  // Clean up
  shutdown();
}
