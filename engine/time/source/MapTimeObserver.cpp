#include "Game.hpp"
#include "CreatureGenerationConstants.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapTimeObserver.hpp"
#include "MapUtils.hpp"
#include "TerrainGeneratorFactory.hpp"

using namespace std;

MapTimeObserver::MapTimeObserver()
{
}

void MapTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  MapUtils::update_creatures(map);
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

