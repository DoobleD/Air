#include <iostream>
#include <exception>
#include <string>

#include "Launcher.hpp"

/**
 * Main entry of Air program. Essential call the run method Launcher.
 *
 * @author Pierre Alletru
 */
int			main(void)
{
  air::Launcher	*	launcher = new air::Launcher();
  
  try
    {
      //      launcher->configure(DEFAULT_CONF_FILE);
      launcher->launch();
    }
  catch (const std::string & e)
    {
      std::cerr << "Error: " << e << std::endl;
      
      delete launcher;
      return EXIT_FAILURE;
    }

  delete launcher;
  return EXIT_SUCCESS;
}
