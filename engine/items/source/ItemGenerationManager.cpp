#include <iterator>
#include "Game.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"

using namespace std;

ItemGenerationManager::ItemGenerationManager()
{
}

// Generate an item generation map for the given danger level and rarity.
ItemGenerationMap ItemGenerationManager::generate_item_generation_map(const int danger_level, const Rarity rarity)
{
  ItemGenerationMap generation_map;

  ItemPtr generated_creature;
  Game& game = Game::instance();
  
  ItemMap items = game.get_items_ref();
  GenerationValuesMap igv_map = game.get_item_generation_values_ref();
    
  // Build the map of creatures available for generation given the danger level and rarity
  for (ItemMap::iterator i_it = items.begin(); i_it != items.end(); i_it++)
  {
    string item_id          = i_it->first;
    ItemPtr item            = i_it->second;
    GenerationValues igvals = igv_map[item_id];
      
    if (does_item_match_generation_criteria(igvals, danger_level, rarity))
    {
      generation_map.insert(make_pair(item_id, make_pair(item, igvals)));
    }
  }
  
  return generation_map;
}

ItemPtr ItemGenerationManager::generate_item(ActionManager& am, ItemGenerationMap& generation_map)
{
  ItemPtr generated_item;
  Game& game = Game::instance();
  
  // Iterate through the generation map, and attempt to generate an item with probability P,
  // where P = (danger level / danger_level + num_items_in_map)
  int p_denominator = 0;
    
  // Get the denominator for the probabilistic generation by summing the danger level over all creatures
  // in the map.
  for (ItemGenerationMap::iterator i_it = generation_map.begin(); i_it != generation_map.end(); i_it++)
  {
    GenerationValues gv = i_it->second.second;
    p_denominator += gv.get_danger_level();
  }
    
  float p_denominator_f = static_cast<float>(p_denominator);

  // Determine the item to generate
  for (ItemGenerationMap::iterator i_it = generation_map.begin(); i_it != generation_map.end(); i_it++)
  {
    GenerationValues igv = i_it->second.second;

    int p_numerator = igv.get_danger_level();
    int P = static_cast<int>((static_cast<float>(p_numerator) / p_denominator_f) * 100);
      
    // Generate the creature if we hit the percentage, or if we're on the last item in the map
    // and a creature has not yet been generated.
    if (RNG::percent_chance(P) || ((distance(i_it, generation_map.end()) == 1) && !generated_item))
    {
      string item_id = i_it->first;
      generated_item = ItemManager::create_item(item_id);

      // JCD FIXME: Do something with quantity later so that stacks of ammunition,
      // currency, etc., can be generated.
      break;
    }
  }
   
  return generated_item;
}

// Check to see if the item matches the given danger level and rarity.
bool ItemGenerationManager::does_item_match_generation_criteria(const GenerationValues& cgv, const int danger_level, const Rarity rarity)
{
  if ( cgv.get_danger_level() >= 0 /* Exclude danger level of -1, which means "don't generate" */
    && cgv.get_danger_level() <= danger_level
    && cgv.get_rarity() <= rarity )
  {
    return true;
  }
  
  return false;
}
