#include "Game.hpp"
#include "MapTimeObserver.hpp"

using std::string;

MapTimeObserver::MapTimeObserver()
{
}

void MapTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();

  // Get the current map.  Check to see if it can be updated with
  // creatures, and if it can, create the appropriate generator and
  // call the update function.
  //
  // ...  
}

ITimeObserver* MapTimeObserver::clone() 
{
  return new MapTimeObserver(*this);
}

ClassIdentifier MapTimeObserver::internal_class_identifier() const
{
  return CLASS_ID_MAP_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapTimeObserver_test.cpp"
#endif

