#include <iterator>
#include <map>
#include <boost/foreach.hpp>
#include "CreatureCalculator.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "RNG.hpp"

using namespace std;

CreatureGenerationManager::CreatureGenerationManager()
{
}

CreatureGenerationMap CreatureGenerationManager::generate_creature_generation_map(const TileType map_terrain_type, const uint danger_level, const Rarity rarity)
{
  CreatureGenerationMap generation_map;

  CreaturePtr generated_creature;
  Game* game = Game::instance();
  
  if (game)
  {
    CreatureMap creatures = game->get_creatures_ref();
    CreatureGenerationValuesMap cgv_map = game->get_creature_generation_values_ref();
    
    // Build the map of creatures available for generation given the danger level and rarity
    for (CreatureMap::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
    {
      string creature_id   = c_it->first;
      CreaturePtr creature = c_it->second;
      CreatureGenerationValues cgvals = cgv_map[creature_id];
      
      if (does_creature_match_generation_criteria(cgvals, map_terrain_type, danger_level, rarity))
      {
        generation_map.insert(make_pair(creature_id, make_pair(creature, cgvals)));
      }
    }
  }
  
  return generation_map;
}

CreaturePtr CreatureGenerationManager::generate_creature(ActionManager& am, CreatureGenerationMap& generation_map)
{
  CreaturePtr generated_creature;
  Game* game = Game::instance();
  
  if (game)
  {
    // Iterate through the generation map, and attempt to generate a creature with probability P,
    // where P = (danger level / danger_level + num_creatures_in_map)
    uint p_denominator = 0;
    
    // Get the denominator for the probabilistic generation by summing the danger level over all creatures
    // in the map.
    for(CreatureGenerationMap::iterator c_it = generation_map.begin(); c_it != generation_map.end(); c_it++)
    {
      CreatureGenerationValues cgv = c_it->second.second;
      p_denominator += cgv.get_danger_level();
    }
    
    float p_denominator_f = static_cast<float>(p_denominator);

    // Determine the creature to generate
    for(CreatureGenerationMap::iterator c_it = generation_map.begin(); c_it != generation_map.end(); c_it++)
    {
      CreatureGenerationValues cgv = c_it->second.second;

      int p_numerator = cgv.get_danger_level();
      int P = static_cast<int>((static_cast<float>(p_numerator) / p_denominator_f) * 100);
      
      // Generate the creature if we hit the percentage, or if we're on the last item in the map
      // and a creature has not yet been generated.
      if (RNG::percent_chance(P) || ((distance(c_it, generation_map.end()) == 1) && !generated_creature))
      {
        string creature_id = c_it->first;
        generated_creature = CreatureFactory::create_by_creature_id(am, creature_id);
        break;
      }
    }
  }
   
  if (generated_creature)
  {
    CreatureCalculator::update_calculated_values(generated_creature);
  }
    
  return generated_creature;
}

bool CreatureGenerationManager::does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const TileType terrain_type, const uint danger_level, const Rarity rarity)
{
  if ( cgv.is_terrain_type_allowed(terrain_type)
    && cgv.get_danger_level() <= danger_level
    && cgv.get_rarity() <= rarity )
  {
    return true;
  }
  
  return false;
}
