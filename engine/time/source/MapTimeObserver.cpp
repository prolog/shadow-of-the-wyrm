#include "Game.hpp"
#include "MapTimeObserver.hpp"
#include "MapUtils.hpp"
#include "Setting.hpp"

using namespace std;

MapTimeObserver::MapTimeObserver()
{
}

void MapTimeObserver::notify(const ulonglong /*minutes_passed*/)
{
  Game& game = Game::instance();
  bool periodically_update_creatures = game.get_settings_ref().get_setting_as_bool(Setting::PERIODICALLY_UPDATE_CREATURES);

  if (periodically_update_creatures)
  {
    MapPtr map = game.get_current_map();
    MapUtils::update_creatures(map);
  }
}

std::unique_ptr<ITimeObserver> MapTimeObserver::clone()
{
  std::unique_ptr<ITimeObserver> mto = std::make_unique<MapTimeObserver>(*this);
  return mto;
}

ClassIdentifier MapTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapTimeObserver_test.cpp"
#endif

