#include "InscribeAction.hpp"
#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "TileProperties.hpp"

using namespace std;

const size_t InscribeAction::MAX_INSCRIPTION_LENGTH = 32;

InscribeAction::InscribeAction()
: inscription_messages({{TileSuperType::TILE_SUPER_TYPE_GROUND, ActionTextKeys::ACTION_INSCRIBE_GROUND}, {TileSuperType::TILE_SUPER_TYPE_AIR, ActionTextKeys::ACTION_INSCRIBE_AIR}, {TileSuperType::TILE_SUPER_TYPE_WATER, ActionTextKeys::ACTION_INSCRIBE_WATER}, {TileSuperType::TILE_SUPER_TYPE_UNDEFINED, ActionTextKeys::ACTION_INSCRIBE_WORLD_MAP}})
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
          CurrentCreatureAbilities cca;

          if (!cca.can_read(creature))
          {
            IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_INSCRIBE_ILLITERATE));
            manager.send();
          }
          else
          {
            tst = creature_tile->get_tile_super_type();

            // Can only inscribe messages on ground - not on water, in the air, etc.
            if (tst == TileSuperType::TILE_SUPER_TYPE_GROUND)
            {
              create_inscription(creature, creature_tile);
            }

            add_inscription_super_type_message(tst);

            return get_action_cost_value(creature);
          }
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

void InscribeAction::create_inscription(CreaturePtr creature, TilePtr tile) const
{
  if (creature != nullptr && tile != nullptr)
  {
    IMessageManager& manager = MM::instance();

    // Get/shorten the inscription.
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_INSCRIBE_QUERY));
    manager.send();

    string inscription = creature->get_decision_strategy()->get_controller()->get_line();
    inscription = inscription.substr(0, MAX_INSCRIPTION_LENGTH);
    
    // Set the inscription on the tile.
    tile->set_inscription_sid(inscription);

    // User might be a smartass and try to enter a page of text.
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    
    // Hard redraw, player might be a smartass who entered ten lines of text 
    // (jerk).
    manager.clear_if_necessary();
    game.update_display(creature, current_map, creature->get_decision_strategy()->get_fov_map(), true);
  }
}

void InscribeAction::add_inscribe_on_world_map_message() const
{
  IMessageManager& manager = MM::instance();

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_INSCRIBE_WORLD_MAP));
  manager.send();
}

void InscribeAction::add_inscription_super_type_message(const TileSuperType tst) const
{
  auto ts_it = inscription_messages.find(tst);

  if (ts_it != inscription_messages.end())
  {
    string ts_sid = ts_it->second;

    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ts_sid));
    manager.send();
  }
}

ActionCostValue InscribeAction::get_action_cost_value(CreaturePtr creature) const
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    acv = ActionCostConstants::INSCRIBE;
  }

  return acv;
}

