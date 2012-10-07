#include <boost/make_shared.hpp>
#include "CursesDisplay.hpp"
#include "DisplayFactory.hpp"

using namespace std;

DisplayFactory::DisplayFactory()
{
}

DisplayFactory::~DisplayFactory()
{
}

DisplaySerializationMap DisplayFactory::display_map;

DisplayPtr DisplayFactory::create_display(const ClassIdentifier ci)
{
  DisplayPtr display;

  // Initialize the map the first time this function is called.
  if (display_map.empty())
  {
    initialize_display_map();
  }

  DisplaySerializationMap::iterator d_it = display_map.find(ci);

  // Make a new copy from the prototype.
  if (d_it != display_map.end())
  {
    display = DisplayPtr(d_it->second->clone());
  }

  return display;
}

void DisplayFactory::initialize_display_map()
{
  display_map.clear();

  DisplayPtr curses_display = boost::make_shared<CursesDisplay>();

  display_map.insert(make_pair(CLASS_ID_CURSES_DISPLAY, curses_display));
}