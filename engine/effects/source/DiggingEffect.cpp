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
{
}

string DiggingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    effect_msg = EffectTextKeys::get_digging_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* DiggingEffect::clone()
{
  return new DiggingEffect(*this);
}

bool DiggingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return dig(creature, affected_coordinate);
}

bool DiggingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return dig(creature, affected_coordinate);
}

bool DiggingEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return dig(creature, affected_coordinate);
}

bool DiggingEffect::dig(CreaturePtr creature, const Coordinate& affected_coord)
{
  bool dug = false;

  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  // Get the creature's current tile and whether or not the map prevents digging
  TilePtr cur_tile = map->at(map->get_location(creature->get_id()));  
  string map_cannot_dig = map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_DIG);

  if (map_cannot_dig.empty() || (String::to_bool(map_cannot_dig) == false))
  {
    if (map != nullptr)
    {
      TilePtr affected_tile = map->at(affected_coord);

      if (affected_tile != nullptr)
      {
        DigAction da;
        da.dig_through(creature, nullptr, map, affected_tile, affected_coord);

        dug = true;
      }
    }
  }
  else
  {
    if (creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_CANNOT_DIG));
      manager.send();

      dug = true; // for ID purposes
    }
  }

  return dug;
}
