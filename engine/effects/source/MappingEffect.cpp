#include "ActionManager.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MappingEffect.hpp"
#include "RNG.hpp"

using namespace std;

string MappingEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  return mapping_msg;
}

Effect* MappingEffect::clone()
{
  return new MappingEffect(*this);
}

void MappingEffect::map(MapPtr map, const MappingType mt)
{
  if (map != nullptr)
  {
    TilesContainer tc = map->get_tiles();
    bool explored = (mt != MappingType::MAPPING_TYPE_FORGET);
    int chance_map = (mt == MappingType::MAPPING_TYPE_MAP_ALL) ? 100 : 30;

    for (const auto& tile_pair : tc)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr)
      {
        if (RNG::percent_chance(chance_map))
        {
          tile->set_explored(explored);
          tile->set_viewed(explored);
        }
      }

      // Indicate that a full redraw is needed.
      Game::instance().get_loaded_map_details_ref().update_spell_cast(true);
    }
  }
}

bool MappingEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) 
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    map(current_map, MappingType::MAPPING_TYPE_MAP_ALL);

    mapping_msg = StringTable::get(EffectTextKeys::EFFECT_MAPPING);
  }
  
  return true;
}

bool MappingEffect::effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    map(current_map, MappingType::MAPPING_TYPE_MAP);

    mapping_msg = StringTable::get(EffectTextKeys::EFFECT_MAPPING);
  }
  
  return true;
}

bool MappingEffect::effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    map(current_map, MappingType::MAPPING_TYPE_FORGET);

    mapping_msg = StringTable::get(EffectTextKeys::EFFECT_MAPPING_FORGET);
  }
  
  return true;
}

