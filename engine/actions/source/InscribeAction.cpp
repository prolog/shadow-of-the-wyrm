#include "InscribeAction.hpp"
#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "TileProperties.hpp"

using namespace std;

const size_t InscribeAction::MAX_INSCRIPTION_LENGTH = 32;

InscribeAction::InscribeAction()
: inscription_messages({{TileSuperType::TILE_SUPER_TYPE_GROUND, ActionTextKeys::ACTION_INSCRIBE_GROUND}, {TileSuperType::TILE_SUPER_TYPE_AIR, ActionTextKeys::ACTION_INSCRIBE_AIR}, {TileSuperType::TILE_SUPER_TYPE_WATER, ActionTextKeys::ACTION_INSCRIBE_WATER}, {TileSuperType::TILE_SUPER_TYPE_UNDEFINED, ActionTextKeys::ACTION_INSCRIBE_AIR}})
{
}

ActionCostValue InscribeAction::inscribe(CreaturePtr creature) const
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && creature->get_is_player())
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map != nullptr)
    {
      MapType map_type = map->get_map_type();
      TilePtr creature_tile = map->at(map->get_location(creature->get_id()));

      if (map_type != MapType::MAP_TYPE_WORLD)
      {
        TileSuperType tst = TileSuperType::TILE_SUPER_TYPE_UNDEFINED;

        if (creature_tile != nullptr)
        {
          CurrentCreatureAbilities cca;

          if (!cca.can_read(creature))
          {
            IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_INSCRIBE_ILLITERATE));
            manager.send();
          }
          else
          {
            tst = creature_tile->get_tile_super_type();

            // Can only inscribe messages on ground - not on water, in the air, etc.
            if (tst == TileSuperType::TILE_SUPER_TYPE_GROUND)
            {
              acv = create_inscription(creature, creature_tile, false);
            }
            else
            {
              acv = get_action_cost_value(creature);
            }

            if (acv > ActionCostConstants::NO_ACTION)
            {
              add_inscription_super_type_message(tst);
            }
          }
        }
      }
      else
      {
        acv = create_inscription(creature, creature_tile, true);
      }
    }
  }

  return acv;
}

ActionCostValue InscribeAction::create_inscription(CreaturePtr creature, TilePtr tile, const bool is_world_map) const
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && tile != nullptr)
  {
    IMessageManager& manager = MMF::instance();
    string message_sid = ActionTextKeys::ACTION_INSCRIBE_QUERY;

    if (is_world_map)
    {
      message_sid = ActionTextKeys::ACTION_INSCRIBE_WORLD_QUERY;
    }

    // Get/shorten the inscription.
    string inscription = manager.add_new_message_with_prompt(StringTable::get(message_sid));
    inscription = inscription.substr(0, MAX_INSCRIPTION_LENGTH);
  
    if (!inscription.empty())
    {
      // Set the inscription on the tile.
      tile->set_inscription_sid(inscription);

      // User might be a smartass and try to enter a page of text.  Hard redraw.
      Game& game = Game::instance();
      MapPtr current_map = Game::instance().get_current_map();

      manager.clear_if_necessary();
      game.update_display(creature, current_map, creature->get_decision_strategy()->get_fov_map(), true);
      acv = get_action_cost_value(creature);
    }
  }

  return acv;
}

void InscribeAction::add_inscription_super_type_message(const TileSuperType tst) const
{
  auto ts_it = inscription_messages.find(tst);

  if (ts_it != inscription_messages.end())
  {
    string ts_sid = ts_it->second;

    IMessageManager& manager = MMF::instance();
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

