#include "CursesDisplay.hpp"
#include "CursesKeyboardController.hpp"
#include "DisplayConstants.hpp"
#include "DisplayFactory.hpp"

#ifdef ENABLE_SDL
#include "SDLDisplay.hpp"
#include "SDLKeyboardController.hpp"
#endif

using namespace std;

DisplayFactory::DisplayFactory()
{
  initialize_display_map();
  initialize_display_identifier_map();
}

DisplayFactory::~DisplayFactory()
{
}

DisplaySerializationMap DisplayFactory::display_map;
DisplayIdentifierMap DisplayFactory::display_identifier_map;

pair<DisplayPtr, ControllerPtr> DisplayFactory::create_display_details(const string& display_identifier)
{
  return create_display_details(get_class_id_for_identifier(display_identifier));
}

pair<DisplayPtr, ControllerPtr> DisplayFactory::create_display_details(const ClassIdentifier ci)
{
  pair<DisplayPtr, ControllerPtr> display_details;
  DisplaySerializationMap::iterator d_it = display_map.find(ci);

  // Make a new copy from the prototype.
  if (d_it != display_map.end())
  {
    display_details.first = DisplayPtr(d_it->second.first->clone());
    display_details.second = ControllerPtr(d_it->second.second->clone());
  }

  return display_details;
}

void DisplayFactory::initialize_display_map()
{
  display_map.clear();

  DisplayPtr curses_display = std::make_shared<CursesDisplay>();
  ControllerPtr curses_keyboard_controller = std::make_shared<CursesKeyboardController>();

  #ifdef ENABLE_SDL
  DisplayPtr sdl_display = std::make_shared<SDLDisplay>();
  ControllerPtr sdl_keyboard_controller = std::make_shared<SDLKeyboardController>();
  #endif

  display_map = DisplaySerializationMap{{ClassIdentifier::CLASS_ID_CURSES_DISPLAY, {curses_display, curses_keyboard_controller}}
  #ifdef ENABLE_SDL
                                        , {ClassIdentifier::CLASS_ID_SDL_DISPLAY, {sdl_display, sdl_keyboard_controller}}
  #endif
                                       };
}

void DisplayFactory::initialize_display_identifier_map()
{
  display_identifier_map.clear();

  display_identifier_map.insert(make_pair(DisplayIdentifier::DISPLAY_IDENTIFIER_CURSES, ClassIdentifier::CLASS_ID_CURSES_DISPLAY));

  #ifdef ENABLE_SDL
  display_identifier_map.insert(make_pair(DisplayIdentifier::DISPLAY_IDENTIFIER_SDL, ClassIdentifier::CLASS_ID_SDL_DISPLAY));
  #endif
}

ClassIdentifier DisplayFactory::get_class_id_for_identifier(const string& display_identifier)
{
  #ifdef ENABLE_SDL
  DisplayIdentifierMap::const_iterator d_it = display_identifier_map.find(display_identifier);

  if (d_it != display_identifier_map.end())
  {
    return d_it->second;
  }
  #endif

  // In the event of an unknown string, default to curses.
  return ClassIdentifier::CLASS_ID_CURSES_DISPLAY;
}
