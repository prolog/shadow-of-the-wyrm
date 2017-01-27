#include <iterator>
#include "AmmunitionCalculator.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "GenerationProperties.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "RNG.hpp"

using namespace std;

ItemGenerationManager::ItemGenerationManager()
{
  rarity_chances = { { Rarity::RARITY_COMMON,   { { Rarity::RARITY_COMMON, 100 } } },
                     { Rarity::RARITY_UNCOMMON, { { Rarity::RARITY_UNCOMMON, 60 }, { Rarity::RARITY_COMMON, 100 } } },
                     { Rarity::RARITY_RARE,     { { Rarity::RARITY_RARE, 60 }, { Rarity::RARITY_UNCOMMON, 60 }, { Rarity::RARITY_COMMON, 100 } } } };
}

// Generate an item generation map for the given danger level and rarity.
ItemGenerationVec ItemGenerationManager::generate_item_generation_vec(const ItemGenerationConstraints& igc)
{
  int min_danger = max(igc.get_min_danger_level(), 1);
  ItemGenerationVec generation_vec;

  ItemPtr generated_creature;
  Game& game = Game::instance();
  
  ItemMap items = game.get_items_ref();
  GenerationValuesMap igv_map = game.get_item_generation_values_ref();

  while (generation_vec.empty() && min_danger > 0)
  {
    // Build the map of creatures available for generation given the danger level and rarity
    for (ItemMap::iterator i_it = items.begin(); i_it != items.end(); i_it++)
    {
      string item_id = i_it->first;
      ItemPtr item = i_it->second;
      GenerationValues igvals = igv_map[item_id];

      // JCD TODO: INCORPORATE VALUE
      if (does_item_match_generation_criteria(igvals, min_danger, igc.get_max_danger_level(), igc.get_rarity(), igc.get_item_type_restrictions()))
      {
        generation_vec[igvals.get_rarity()].push_back(make_pair(item_id, make_pair(item, igvals)));
      }
    }

    min_danger /= 2;
  }
  
  return generation_vec;
}

// Get an item rarity.  This will be based on a general generational rarity.
// Common items can only be generated for common rarities.  Uncommon items
// have a good chance to generate an uncommon item, or else generate a
// common item, and with a rare rarity, there's a good chance of either a
// rare or uncommon item.
Rarity ItemGenerationManager::get_item_rarity(const Rarity generation_rarity) const
{
  Rarity rarity = Rarity::RARITY_COMMON;

  auto r_it = rarity_chances.find(generation_rarity);

  if (r_it != rarity_chances.end())
  {
    vector<pair<Rarity, int>> rarity_chances = r_it->second;

    for (const auto& rarity_pair : rarity_chances)
    {
      if (RNG::percent_chance(rarity_pair.second))
      {
        rarity = rarity_pair.first;
        break;
      }
    }
  }

  return rarity;
}

ItemPtr ItemGenerationManager::generate_item(ActionManager& am, ItemGenerationVec& generation_vec, const Rarity rarity, const int enchant_points)
{
  ItemPtr generated_item;
  AmmunitionCalculator ac;

  // The map already contains appropriate items filtered by danger level,
  // so pick one at random.
  if (!generation_vec.empty())
  {
    Rarity item_rarity = get_item_rarity(rarity);
    vector<ItemGenerationPair> rarity_vec;

    while (rarity_vec.empty())
    {
      rarity_vec = generation_vec[item_rarity];

      if (rarity_vec.empty())
      {
        if (item_rarity == Rarity::RARITY_COMMON)
        {
          return generated_item;
        }
        else
        {
          item_rarity = Rarity::RARITY_COMMON;
        }
      }
    }

    ItemGenerationPair rand_item = rarity_vec.at(RNG::range(0, rarity_vec.size()-1));
    string item_id = rand_item.first;

    generated_item = ItemManager::create_item(item_id);

    // Generate stacks appropriately.
    ItemType type = generated_item->get_type();

    if (type == ItemType::ITEM_TYPE_CURRENCY)
    {
      generated_item->set_quantity(RNG::range(3, 20));
    }
    else if (type == ItemType::ITEM_TYPE_AMMUNITION)
    {
      pair<int, int> stack_size = ac.calculate_stack_size(generated_item);
      generated_item->set_quantity(RNG::range(stack_size.first, stack_size.second));
    }

    if (enchant_points > 0)
    {
      bool enchant_all_at_once = RNG::percent_chance(50);
      ItemEnchantmentCalculator iec;
      int pct_chance_brand = 0;

      if (enchant_all_at_once)
      {
        pct_chance_brand = iec.calculate_pct_chance_brand(1.0, generated_item);
        generated_item->enchant(pct_chance_brand, enchant_points);
      }
      else
      {
        for (int i = 0; i < enchant_points; i++)
        {
          pct_chance_brand = iec.calculate_pct_chance_brand(1.0, generated_item);
          generated_item->enchant(pct_chance_brand, 1);
        }
      }
    }
  }

  return generated_item;
}

// Check to see if the item matches the given danger level and rarity.
bool ItemGenerationManager::does_item_match_generation_criteria(const GenerationValues& cgv, const int min_danger_level, const int max_danger_level, const Rarity rarity, const vector<ItemType>& item_type_restrictions)
{
  ItemType itype = ItemType::ITEM_TYPE_NULL;
  string prop_itype = cgv.get_property(GenerationProperties::GENERATION_PROPERTIES_ITEM_TYPE);

  if (!prop_itype.empty())
  {
    itype = static_cast<ItemType>(String::to_int(prop_itype));
  }

  int cgv_danger_level = cgv.get_danger_level();

  if ( cgv_danger_level >= 0 /* Exclude danger level of -1, which means "don't generate" */
    && cgv_danger_level >= min_danger_level
    && cgv_danger_level <= max_danger_level
    // If the item type restrictions vector is empty - no restrictions
    // Otherwise, the item type has to be found within the container.
    && (item_type_restrictions.empty() || (std::find(item_type_restrictions.begin(), item_type_restrictions.end(), itype) != item_type_restrictions.end()))
    && cgv.get_rarity() <= rarity )
  {
    return true;
  }
  
  return false;
}
