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
ItemGenerationVec ItemGenerationManager::generate_item_generation_vec(const int danger_level, const Rarity rarity)
{
  ItemGenerationVec generation_vec;

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
      generation_vec.push_back(make_pair(item_id, make_pair(item, igvals)));
    }
  }
  
  return generation_vec;
}

ItemPtr ItemGenerationManager::generate_item(ActionManager& am, ItemGenerationVec& generation_vec)
{
  ItemPtr generated_item;
  Game& game = Game::instance();

  // The map already contains appropriate items filtered by danger level,
  // so pick one at random.
  if (!generation_vec.empty())
  {
    uint idx = RNG::range(0, generation_vec.size());

    ItemGenerationPair rand_item = generation_vec[idx];
    string item_id = rand_item.first;

    generated_item = ItemManager::create_item(item_id);

    // If this is currency, generate a random amount based on the d12.
    // If this is ammunition, generate a little less.
    ItemType type = generated_item->get_type();

    if (type == ITEM_TYPE_CURRENCY)
    {
      generated_item->set_quantity(RNG::dice(3, 12));
    }
    else if (type == ITEM_TYPE_AMMUNITION)
    {
      generated_item->set_quantity(RNG::dice(2, 12));
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
