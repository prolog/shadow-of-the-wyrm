#include "ActionManager.hpp"
#include "CoordUtils.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "SummonTrapsEffect.hpp"
#include "RNG.hpp"

using namespace std;

SummonTrapsEffect::SummonTrapsEffect()
{
  summon_msg = StringTable::get(EffectTextKeys::EFFECT_SUMMON_TRAPS);
}

string SummonTrapsEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  return summon_msg;
}

Effect* SummonTrapsEffect::clone()
{
  return new SummonTrapsEffect(*this);
}

bool SummonTrapsEffect::summon(CreaturePtr creature, MapPtr map, const int num_traps)
{
  bool effect_id = false;

  if (creature != nullptr && map != nullptr)
  {
    Game& game = Game::instance();
    Coordinate creature_coord = map->get_location(creature->get_id());
    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coord.first, creature_coord.second);
    vector<TrapPtr> traps = game.get_trap_info_ref();
    std::shuffle(adjacent_coords.begin(), adjacent_coords.end(), RNG::get_engine());

    // Traps only go on ground tiles that creatures can move on and which don't
    // already have a feature present.
    adjacent_coords.erase(std::remove_if(adjacent_coords.begin(), 
                                         adjacent_coords.end(), 
                                         [&](Coordinate c) 
                                         { 
                                           TilePtr tile = map->at(c);
                                           return (tile && 
                                                    (tile->get_tile_super_type() != TileSuperType::TILE_SUPER_TYPE_GROUND ||
                                                     tile->get_is_blocking(nullptr) ||
                                                     tile->has_feature()));
                                         }), adjacent_coords.end());

    for (int i = 0; i < num_traps; i++)
    {
      if (!adjacent_coords.empty())
      {
        int idx = RNG::range(0, adjacent_coords.size()-1);
        Coordinate coords = adjacent_coords.at(idx);
        TilePtr tile = map->at(coords);

        if (tile != nullptr)
        {
          GeneratorUtils::generate_trap(map, coords.first, coords.second, traps);
          effect_id = true;
        }
      }
    }
  }

  if (effect_id)
  {
    Game::instance().get_sound(creature)->play(SoundEffectID::MAP_EFFECT);
  }
  return effect_id;
}

bool SummonTrapsEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  bool id = false;

  if (creature)
  {
    MapPtr current_map = Game::instance().get_current_map();
    id = summon(creature, current_map, 4);
  }
  
  return id;
}

bool SummonTrapsEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  bool id = false;

  if (creature)
  {
    MapPtr current_map = Game::instance().get_current_map();
    id = summon(creature, current_map, 6);
  }
  
  return id;
}

bool SummonTrapsEffect::effect_cursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  bool id = false;

  if (creature)
  {
    MapPtr current_map = Game::instance().get_current_map();
    id = summon(creature, current_map, 8);
  }
  
  return id;
}
