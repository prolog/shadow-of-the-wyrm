#include <boost/make_shared.hpp>
#include "CursesDisplay.hpp"
#include "DisplayFactory.hpp"

DisplayPtr DisplayFactory::create_display(const ClassIdentifier ci)
{
  DisplayPtr display;

  if (ci == CLASS_ID_CURSES_DISPLAY)
  {
    display = boost::make_shared<CursesDisplay>();
  }

  return display;
}

