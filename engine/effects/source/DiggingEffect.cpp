#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Creature.hpp"
#include "DigAction.hpp"
#include "DiggingEffect.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

DiggingEffect::DiggingEffect()
: add_messages(true)
{
}

string DiggingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;
  CreaturePtr msg_creature = creature;
  bool originator_is_player = false;

  if (creature)
  {
    if (originator != nullptr)
    {
      originator_is_player = true;
    }

    effect_msg = EffectTextKeys::get_digging_effect_message(msg_creature->get_description_sid(), originator_is_player);
  }

  return effect_msg;
}

Effect* DiggingEffect::clone()
{
  return new DiggingEffect(*this);
}

bool DiggingEffect::effect_blessed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& affected_coordinate, TilePtr /*affected_tile*/)
{
  return dig(creature, affected_coordinate);
}

bool DiggingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& affected_coordinate, TilePtr /*affected_tile*/)
{
  return dig(creature, affected_coordinate);
}

bool DiggingEffect::effect_cursed(CreaturePtr creature, ActionManager * /*am*/, const Coordinate& affected_coordinate, TilePtr /*affected_tile*/)
{
  return dig(creature, affected_coordinate);
}

bool DiggingEffect::dig(CreaturePtr /*creature*/, const Coordinate& affected_coord)
{
  bool dug = false;

  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (map == nullptr)
  {
    return false;
  }

  // Get the creature's current tile and whether or not the map prevents digging
  TilePtr cur_tile = map->at(affected_coord);  
  string map_cannot_dig = map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG);
  CreaturePtr source_creature = map->get_creature(source_id);

  if (map_cannot_dig.empty() || (String::to_bool(map_cannot_dig) == false))
  {
    if (map != nullptr)
    {
      TilePtr affected_tile = map->at(affected_coord);

      if (affected_tile != nullptr)
      {
        string tile_cannot_dig = affected_tile->get_additional_property(TileProperties::TILE_PROPERTY_CANNOT_DIG);

        if (tile_cannot_dig.empty() || String::to_bool(tile_cannot_dig) == false)
        {
          DigAction da;
          da.dig_through(source_id, nullptr, map, affected_tile, affected_coord, add_messages, false);

          dug = true;
        }
      }
    }
  }
  else
  {
    if (add_messages && source_creature && source_creature->get_is_player())
    {
      IMessageManager& manager = MMF::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG));
      manager.send();

      dug = true; // for ID purposes
    }
  }

  // After the first dig (or non-dig), turn off messages so that the user
  // doesn't get repeated messages.
  add_messages = false;
  return dug;
}
