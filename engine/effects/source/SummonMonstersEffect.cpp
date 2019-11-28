#include "ActionManager.hpp"
#include "CoordUtils.hpp"
#include "Creature.hpp"
#include "CreatureGenerationManager.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "SummonMonstersEffect.hpp"
#include "RNG.hpp"

using namespace std;

const int SummonMonstersEffect::SUMMON_DANGER_OFFSET = 5;

SummonMonstersEffect::SummonMonstersEffect()
{
  summon_msg = StringTable::get(EffectTextKeys::EFFECT_SUMMON_MONSTERS);
}

string SummonMonstersEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  return summon_msg;
}

Effect* SummonMonstersEffect::clone()
{
  return new SummonMonstersEffect(*this);
}

bool SummonMonstersEffect::summon(CreaturePtr creature, MapPtr map, const int num_monsters)
{
  bool effect_id = false;

  if (creature != nullptr && map != nullptr)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();
    CreatureGenerationManager cgm;

    int min_danger_level = map->get_danger();
    int summon_danger_level = ((min_danger_level + SUMMON_DANGER_OFFSET) + creature->get_level().get_current()) / 2;
    CreatureGenerationList generation_list = cgm.generate_creature_generation_map(map->get_terrain_type(), map->get_permanent(), min_danger_level, summon_danger_level, Rarity::RARITY_COMMON, {});

    Coordinate creature_coord = map->get_location(creature->get_id());
    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coord.first, creature_coord.second);
    std::shuffle(adjacent_coords.begin(), adjacent_coords.end(), RNG::get_engine());

    // Remove all tiles that have creatures from consideration for summoning.
    adjacent_coords.erase(std::remove_if(adjacent_coords.begin(), 
                                         adjacent_coords.end(), 
                                         [&](Coordinate c) 
                                         { 
                                           TilePtr tile = map->at(c);
                                           return (tile && tile->has_creature()); 
                                         }), adjacent_coords.end());

    for (int i = 0; i < num_monsters; i++)
    {
      if (!adjacent_coords.empty())
      {
        int idx = RNG::range(0, adjacent_coords.size()-1);
        Coordinate coords = adjacent_coords.at(idx);
        TilePtr tile = map->at(coords);

        if (tile != nullptr)
        {
          CreaturePtr summoned_creature = cgm.generate_creature(am, generation_list, map);

          if (summoned_creature != nullptr)
          {
            GameUtils::add_new_creature_to_map(game, summoned_creature, map, coords);
            effect_id = true;
          }
        }
      }
    }
  }

  return effect_id;
}

bool SummonMonstersEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  bool id = false;

  if (creature)
  {
    MapPtr current_map = Game::instance().get_current_map();
    id = summon(creature, current_map, RNG::dice(1,2));
  }
  
  return id;
}

bool SummonMonstersEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  bool id = false;

  if (creature)
  {
    MapPtr current_map = Game::instance().get_current_map();
    id = summon(creature, current_map, RNG::dice(1, 3));
  }
  
  return id;
}

bool SummonMonstersEffect::effect_cursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  bool id = false;

  if (creature)
  {
    MapPtr current_map = Game::instance().get_current_map();
    id = summon(creature, current_map, RNG::dice(1,6));
  }
  
  return id;
}
