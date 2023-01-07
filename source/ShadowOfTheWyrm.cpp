// MSXML is a POS and doesn't play nice with Xerces.
#ifndef __MSXML_LIBRARY_DEFINED__
#define __MSXML_LIBRARY_DEFINED__
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>

#include "UnhandledExceptions.hpp"

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
#include "DisplaySettings.hpp"
#include "Environment.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "LogFiles.hpp"
#include "Metadata.hpp"
#include "RNG.hpp"
#include "SDLInit.hpp"
#include "ShadowOfTheWyrmEngine.hpp"
#include "Settings.hpp"
#include "Setting.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
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
std::string run_game(DisplayPtr display, ControllerPtr controller, Settings& settings);
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

int main(int argc, char* argv[])
{
  register_unhandled_exception_handler();

  try
  {
    std::srand(static_cast<unsigned int>(std::time(0)));
    print_title();

    if (argc > 1)
    {
      return parse_command_line_arguments(argc, argv);
    }
    else
    {
      Settings user_settings(true, true);
      Settings settings(true, false);

      settings.merge_user_settings(user_settings);

      Log& log = Log::instance(&settings);
      log.set_log_level(LoggingLevel::LOG_ERROR);

      Environment::create_userdata_directory(&settings);
      Environment::create_empty_user_settings_if_necessary(&settings);

      string display_id = settings.get_setting(Setting::DISPLAY);
      string msg;

      #ifdef ENABLE_SDL
      SDLInit sdl;

      if (display_id == DisplayIdentifier::DISPLAY_IDENTIFIER_SDL)
      {
        sdl.set_up();
      }
      #endif

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

      log.debug("Created display.");

      if (display)
      {
        set_display_settings(display, settings);
        display->display_splash(true);

        msg = run_game(display, controller, settings);

        if (!msg.empty())
        {
          cout << msg << endl;
        }
      }
      else
      {
        // Reset the display, try again.
        if (display)
        {
          display->tear_down();
        }
      }

      if (display_id == DisplayIdentifier::DISPLAY_IDENTIFIER_SDL)
      {
        #ifdef ENABLE_SDL
        sdl.tear_down();
        #endif
      }
    }
  }
  catch(std::exception& e)
  {
    ostringstream ss;
    ss << "Unable to run Shadow of the Wyrm: " << e.what();
    std::cerr << ss.str();
    
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unable to run Shadow of the Wyrm - unknown exception";
    return 1;
  }

  return 0;
}

string run_game(DisplayPtr display, ControllerPtr controller, Settings& settings)
{
  string msg;
  Log& log = Log::instance();
  ShadowOfTheWyrmEngine engine;

  // set the default display into the engine
  engine.set_display(display);
  engine.set_controller(controller);

  log.debug("Starting SotW.");
  msg = engine.start(settings);

  display->tear_down();
  return msg;
}

bool check_write_permissions()
{
  bool can_write = true;

  string fname = "test";
  std::ofstream test_file;
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
    vector<string> setting_names = { DisplaySettings::DISPLAY_SETTING_COLOUR,
                                     Setting::DISPLAY_SPLASH_IMAGE,
                                     Setting::DISPLAY_FONT, 
                                     Setting::DISPLAY_TILE_SIZE, 
                                     Setting::DISPLAY_TILE_GLYPHS_PER_LINE, 
                                     Setting::DISPLAY_NUM_GLYPHS };

    for (const string& s : setting_names)
    {
      display->set_property(s, settings.get_setting(s));
    }

    // Get all the SDL display settings
    map<string, string> sdl_display_settings = settings.get_settings_starts_with(Setting::DISPLAY_SDL_PREFIX);
    for (auto& s_pair : sdl_display_settings)
    {
      display->set_property(s_pair.first, s_pair.second);
    }
  }
}
