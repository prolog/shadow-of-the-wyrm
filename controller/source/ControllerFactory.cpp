#include <boost/assert.hpp>
#include "ControllerFactory.hpp"
#include "CursesKeyboardController.hpp"
#include "Log.hpp"
#include "NullKeyboardController.hpp"
#include "SDLKeyboardController.hpp"

using namespace std;

ControllerSerializationMap ControllerFactory::controller_map;

ControllerFactory::ControllerFactory()
{
}

ControllerFactory::~ControllerFactory()
{
}

ControllerPtr ControllerFactory::create_controller(const ClassIdentifier ci)
{
  ControllerPtr controller;

  if (controller_map.empty())
  {
    initialize_controller_map();
  }

  ControllerSerializationMap::iterator c_it = controller_map.find(ci);

  if (c_it != controller_map.end())
  {
    controller = ControllerPtr(c_it->second->clone());
  }
  else
  {
    // Forgot to update the class ID map!
    string s_cl_id = std::to_string(static_cast<int>(ci));
    string msg = "ControllerFactory::create_controller - Could not instantiate with class_id " + s_cl_id;
    Log::instance().error(msg);
    BOOST_ASSERT_MSG(false, msg.c_str());
  }

  return controller;
}

void ControllerFactory::initialize_controller_map()
{
  controller_map.clear();

  ControllerPtr keyboard = std::make_shared<CursesKeyboardController>();
  ControllerPtr sdlcont  = std::make_shared<SDLKeyboardController>();
  ControllerPtr nullcont = std::make_shared<NullKeyboardController>();

  controller_map = ControllerSerializationMap{ { ClassIdentifier::CLASS_ID_CURSES_KEYBOARD_CONTROLLER, keyboard }, 
                                               { ClassIdentifier::CLASS_ID_SDL_KEYBOARD_CONTROLLER, sdlcont },
                                               { ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER, nullcont } };
}

