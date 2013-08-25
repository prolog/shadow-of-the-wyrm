#ifdef _MSC_VER
#include <tchar.h>
#endif

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <boost/archive/archive_exception.hpp>

#include "common.hpp"
#include "global_prototypes.hpp"

#include "CursesKeyboardController.hpp"

#include "CursesDisplay.hpp"
#include "DisplayConstants.hpp"
#include "DisplayFactory.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Metadata.hpp"
#include "SavageLandsEngine.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "XMLDataStructures.hpp"
#include "XMLFileReader.hpp"

#ifdef UNIT_TESTS
#include "gtest/gtest.h"
#endif

using namespace std;
using namespace xercesc;

void print_title(void);
void initialize_settings(void);
int parse_command_line_arguments(int argc, char* argv[]);

#ifdef UNIT_TESTS
int run_unit_tests();

int run_unit_tests()
{
  int test_result = RUN_ALL_TESTS();
  return test_result;
}
#endif

void print_title()
{
  Metadata meta;

  std::string title = StringTable::get(TextKeys::SL_TITLE);
  std::string version = meta.get_version();
	std::cout << title << " " << version << std::endl;

}

int parse_command_line_arguments(int argc, char* argv[])
{
  for (int x = 0; x < argc; x++)
  {
    string current_arg = argv[x];

    if (current_arg == "/test")
    {
      #ifdef UNIT_TESTS
      ::testing::InitGoogleTest(&argc, argv);
      int test_result = run_unit_tests();
      return test_result;
      #else
      cout << "Unit tests are not available in release mode." << endl;
      #endif
    }
    else
    {
      cout << "Unknown argument: " << current_arg << endl;
    }
  }

  return 0;
}

#ifdef _MSC_VER
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  try
  {
    XML::initialize();
    Log& log = Log::instance();
    log.set_log_level(LOG_ERROR);
    log.trace("main - testing");

    print_title();

    if (argc > 1)
    {
      return parse_command_line_arguments(argc, argv);
    }
    else
    {
      // JCD FIXME: Refactor.  This id should eventually be in a .rc
      // type file, so that each individual person can set their own
      // settings...
      string display_id = DisplayIdentifier::DISPLAY_IDENTIFIER_CURSES;
      pair<DisplayPtr, ControllerPtr> display_details = DisplayFactory::create_display_details(display_id);
      DisplayPtr display = display_details.first;
      ControllerPtr controller = display_details.second;

      bool display_created = display->create();

      if (display_created)
      {
        SavageLandsEngine engine;

        // set the display into the engine
        engine.set_controller(controller);
        engine.set_display(display);
        engine.start();
      }

      display->tear_down();
    }
  }
  catch(...)
  {
    Log::instance().log("Unable to run Savage Lands!");
  }

  XML::tear_down();

  return 0;
}
