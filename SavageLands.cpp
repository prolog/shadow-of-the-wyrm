#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>

#include "common.hpp"
#include "global_prototypes.hpp"

#include "NCursesDisplay.hpp"
#include "Display.hpp"

#include "Log.hpp"
#include "SavageLandsEngine.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"
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
  std::string title = StringTable::get(TextKeys::SL_TITLE);
  std::string version = get_version();
	std::cout << title << " " << version << std::endl;

}

void initialize_settings()
{
  StringTable::load("savagelandstext_en.ini");
}

int parse_command_line_arguments(int argc, char* argv[])
{
  for (int x = 0; x < argc; x++)
  {
    string current_arg = argv[x];

    if (current_arg == "/test")
    {
      // JCD FIXME: Refactor
      #ifdef UNIT_TESTS
      ::testing::InitGoogleTest(&argc, argv);
      int test_result = run_unit_tests();
      return test_result;
      #else
      cout << "Unit tests are not available in release mode." << endl;
      #endif
    }
  }

  return 0;
}

int main(int argc, char* argv[])
{
  try
  {
    initialize_settings();
    XML::initialize();

    print_title();

    if (argc > 1)
    {
      return parse_command_line_arguments(argc, argv);
    }
    else
    {
      // JCD FIXME: Refactor
      DisplayPtr display(new NCursesDisplay());
      bool display_created = display->create();

      Log* log = Log::instance(LOG_NONE);

      if (display_created)
      {
        display->create();
        SavageLandsEngine engine;

        // set the display into the engine
        engine.set_display(display);
        engine.start();
      }

      display->tear_down();
    }
  }
  catch(...)
  {
    // JCD FIXME: Process XML failure.
  }

  XML::tear_down();
  Log* log_instance = Log::instance();
  delete log_instance;
  log_instance = NULL;

  return 0;
}
