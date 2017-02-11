#include "ShopsTimeObserver.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MapItemGenerator.hpp"
#include "MessageManagerFactory.hpp"
#include "PlayerConstants.hpp"

using namespace std;

ShopsTimeObserver::ShopsTimeObserver()
{
}

void ShopsTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();
  MapRegistry& mr = game.get_map_registry_ref();

  MapRegistryMap& maps = mr.get_maps_ref();

  for (auto& m_pair : maps)
  {
    MapPtr cur_map = m_pair.second;

    if (cur_map != nullptr)
    {
      map<string, Shop> shops = cur_map->get_shops();

      if (!shops.empty() && cur_map->has_player())
      {
        IMessageManager& manager = MM::instance();
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_REPOP_SHOP));
        manager.send();
      }

      for (const auto& s_pair : shops)
      {
        MapItemGenerator mig;
        mig.repop_shop(cur_map, s_pair.first);
      }
    }
  }
}

ITimeObserver* ShopsTimeObserver::clone() 
{
  return new ShopsTimeObserver(*this);
}

ClassIdentifier ShopsTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SHOPS_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShopsTimeObserver_test.cpp"
#endif

