#include <boost/make_shared.hpp>
#include "ControllerFactory.hpp"
#include "CursesKeyboardController.hpp"
#include "NullKeyboardController.hpp"

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

  return controller;
}

void ControllerFactory::initialize_controller_map()
{
  controller_map.clear();

  ControllerPtr keyboard = boost::make_shared<CursesKeyboardController>();
  ControllerPtr nullcont = boost::make_shared<NullKeyboardController>();

  controller_map.insert(make_pair(CLASS_ID_CURSES_KEYBOARD_CONTROLLER, keyboard));
  controller_map.insert(make_pair(CLASS_ID_NULL_KEYBOARD_CONTROLLER, nullcont));
}

