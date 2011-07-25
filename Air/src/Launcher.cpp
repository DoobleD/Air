#ifdef DEBUG_MOD
#include "Viewer.hpp"

extern air::Viewer	g_viewer;
#endif


#include <iostream>

#include "Launcher.hpp"
#include "Viewer.hpp"
#include "OpenNIBox.hpp"
#include "NITEBox.hpp"

using namespace air;

extern OpenNIBox	g_openNI;
extern NITEBox		g_NITE;


void			Launcher::initilize(void)
{
  // Initialize OpenNI
  g_openNI.initialize();

  // Initialize NITE
  g_NITE.initialize(m_sessionListener);

#ifdef DEBUG_MOD
  // Initialize the viewer
  try
    {
      g_viewer.initialize();
    }
  catch (const std::string & e)
    {
      std::cerr << "Can't initialize the viewer." << std::endl;
    }
#endif
}

void			Launcher::run(void)
{
  while (TRUE)
    {
      g_openNI.waitAndUpdate();
      
      g_NITE.update();
      
#ifdef DEBUG_MOD
      g_viewer.update();
#endif
    }
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
  
  // Main loop
  run();
  
  // Clean up
  shutdown();
}
