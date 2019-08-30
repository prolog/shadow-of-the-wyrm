#include <stdio.h>

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/filesystem.hpp>

#include "common.hpp"
#include "global_prototypes.hpp"

#include "CursesKeyboardController.hpp"

#include "Conversion.hpp"
#include "CursesDisplay.hpp"
#include "DisplayConstants.hpp"
#include "DisplayFactory.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "LogFiles.hpp"
#include "Metadata.hpp"
#include "SDL.hpp"
#include "ShadowOfTheWyrmEngine.hpp"
#include "Settings.hpp"
#include "Setting.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "UnhandledExceptions.hpp"
#include "XMLDataStructures.hpp"
#include "XMLFileReader.hpp"

#ifdef UNIT_TESTS
#include "gtest/gtest.h"
#endif

#ifdef _MSC_VER
#include <tchar.h>
#endif

using namespace std;
using namespace xercesc;

void print_title();
void run_game(DisplayPtr display, ControllerPtr controller, Settings& settings);
void remove_old_logfiles(const Settings& settings);
bool check_write_permissions();
int parse_command_line_arguments(int argc, char* argv[]);
void set_display_settings(DisplayPtr display, const Settings& settings);

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

  std::string version = meta.get_version();
	std::cout << "Shadow of the Wyrm " << version << std::endl;

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
      cout << "Unit tests are not available in this build." << endl;
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
  register_unhandled_exception_handler();
  Log& log = Log::instance();

  try
  {
    log.set_log_level(LoggingLevel::LOG_ERROR);
    log.trace("main - testing");

    print_title();

    if (argc > 1)
    {
      return parse_command_line_arguments(argc, argv);
    }
    else
    {
      Settings settings(true);
      string display_id = settings.get_setting(Setting::DISPLAY);
      SDL sdl;

      if (display_id == DisplayIdentifier::DISPLAY_IDENTIFIER_SDL)
      {
        sdl.set_up();
      }

      remove_old_logfiles(settings);

      // Set the default display and controller.
      DisplayFactory di;
      pair<DisplayPtr, ControllerPtr> display_details = di.create_display_details(display_id);

      DisplayPtr display = display_details.first;
      ControllerPtr controller = display_details.second;

      bool write_ok = check_write_permissions();

      if (!write_ok)
      {
        cout << "No write permissions in current directory!" << endl;
        throw "error";
      }

      if (display)
      {
        set_display_settings(display, settings);

        if (display->create())
        {
          run_game(display, controller, settings);
        }
      }
      else
      {
        // Reset the display, try again.
        if (display)
        {
          display->tear_down();
        }

        log.error("main - Could not create display!");
       
        cerr << "Could not create display.  Resize terminal to 80x25 and hit enter." << endl;
        string foo;
        std::getline(cin, foo);

        if (display && display->create())
        {
          run_game(display, controller, settings);
        }
        else
        {
          cerr << "\nCould not create display.";
          throw "error";
        }
      }

      if (display_id == DisplayIdentifier::DISPLAY_IDENTIFIER_SDL)
      {
        sdl.tear_down();
      }
    }
  }
  catch(...)
  {
    log.error("main - Unable to run Shadow of the Wyrm!");
    return 1;
  }

  return 0;
}

void run_game(DisplayPtr display, ControllerPtr controller, Settings& settings)
{
  cout << "\nLoading Shadow of the Wyrm..." << endl;

  ShadowOfTheWyrmEngine engine;

  // set the default display into the engine
  engine.set_display(display);
  engine.set_controller(controller);
  engine.start(settings);

  display->tear_down();
}

bool check_write_permissions()
{
  bool can_write = true;

  string fname = "test";
  ofstream test_file;
  test_file.open(fname, ios::out | ios::binary);

  if (!test_file.good())
  {
    can_write = false;
  }
  else
  {
    test_file.close();
    std::remove(fname.c_str());
  }
  
  return can_write;
}

void remove_old_logfiles(const Settings& settings)
{
  int days_old = String::to_int(settings.get_setting(Setting::REMOVE_LOGS_DAYS_OLD));

  if (days_old > -1)
  {
    LogFiles lf;
    lf.remove_old(days_old);
  }
}

void set_display_settings(DisplayPtr display, const Settings& settings)
{
  if (display != nullptr)
  {
    string display_font = settings.get_setting(Setting::DISPLAY_FONT);
    string display_tile_size = settings.get_setting(Setting::DISPLAY_TILE_SIZE);
    display->set_property(Setting::DISPLAY_FONT, display_font);
    display->set_property(Setting::DISPLAY_TILE_SIZE, display_tile_size);
  }
}