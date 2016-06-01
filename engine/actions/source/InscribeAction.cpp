#include "InscribeAction.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

InscribeAction::InscribeAction()
: invalid_ts_messages({{TileSuperType::TILE_SUPER_TYPE_AIR, ActionTextKeys::ACTION_INSCRIBE_AIR}, {TileSuperType::TILE_SUPER_TYPE_WATER, ActionTextKeys::ACTION_INSCRIBE_WATER}, {TileSuperType::TILE_SUPER_TYPE_UNDEFINED, ActionTextKeys::ACTION_INSCRIBE_WORLD_MAP}})
{
}

ActionCostValue InscribeAction::inscribe(CreaturePtr creature) const
{
  if (creature != nullptr && creature->get_is_player())
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map != nullptr)
    {
      MapType map_type = map->get_map_type();

      if (map_type != MapType::MAP_TYPE_WORLD)
      {
        TileSuperType tst = TileSuperType::TILE_SUPER_TYPE_UNDEFINED;
        TilePtr creature_tile = map->at(map->get_location(creature->get_id()));

        if (creature_tile != nullptr)
        {
          tst = creature_tile->get_tile_super_type();

          // Can only inscribe on ground - not on water, in the air, etc.
          if (tst == TileSuperType::TILE_SUPER_TYPE_GROUND)
          {
            // ...
          }
          else
          {
            add_invalid_tile_super_type_message(tst);
          }

          return get_action_cost_value(creature);
        }
      }
      else
      {
        add_inscribe_on_world_map_message();
      }
    }
  }

  return 0;
}

void InscribeAction::add_inscribe_on_world_map_message() const
{
  IMessageManager& manager = MessageManagerFactory::instance();

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_INSCRIBE_WORLD_MAP));
  manager.send();
}

void InscribeAction::add_invalid_tile_super_type_message(const TileSuperType tst) const
{
  auto ts_it = invalid_ts_messages.find(tst);

  if (ts_it != invalid_ts_messages.end())
  {
    string ts_sid = ts_it->second;

    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ts_sid));
    manager.send();
  }
}

ActionCostValue InscribeAction::get_action_cost_value(CreaturePtr creature) const
{
  ActionCostValue acv = 0;

  if (creature != nullptr)
  {
    acv = 100;
  }

  return acv;
}

