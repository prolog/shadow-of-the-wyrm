#include <iterator>
#include "AmmunitionCalculator.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "Game.hpp"
#include "GenerationProperties.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "RNG.hpp"
#include "Setting.hpp"

using namespace std;

ItemGenerationManager::ItemGenerationManager()
: spellbook_squelch_pct(0)
{
  rarity_chances = { { Rarity::RARITY_COMMON,   { { Rarity::RARITY_COMMON, 100 } } },
                     { Rarity::RARITY_UNCOMMON, { { Rarity::RARITY_UNCOMMON, 60 }, { Rarity::RARITY_COMMON, 100 } } },
                     { Rarity::RARITY_RARE,     { { Rarity::RARITY_RARE, 60 }, { Rarity::RARITY_UNCOMMON, 60 }, { Rarity::RARITY_COMMON, 100 } } },
                     { Rarity::RARITY_VERY_RARE,{ { Rarity::RARITY_VERY_RARE, 40 }, { Rarity::RARITY_RARE, 80 }, { Rarity::RARITY_UNCOMMON, 90 }, { Rarity::RARITY_COMMON, 100 } } } };

  initialize_spellbook_squelch_pct();
}

void ItemGenerationManager::initialize_spellbook_squelch_pct()
{
  Game& game = Game::instance();
  int squelch_pct = String::to_int(game.get_settings_ref().get_setting(Setting::SPELLCASTER_UNUSABLE_SPELLBOOK_SQUELCH_PCT));

  if (squelch_pct >= 0 && squelch_pct <= 100)
  {
    spellbook_squelch_pct = squelch_pct;
  }
}

// Item types have the following chances to be generated at random:
//
// Plant: 0%
// Staff: 0%
// Boat: 1%
// Currency: 2%
// Amulet: 2%
// Misc: 2%
// Tool: 3%
// Spellbook: 5%
// Ring: 5%
// Wand: 6%
// Ammunition: 8%
// Weapon: 10%
// Armour: 10%
// Potion: 15%
// Scroll: 15%
// Food: 16%
ItemType ItemGenerationManager::generate_item_type() const
{
  int val = RNG::range(1, 100);
  return generate_item_type_by_val(val);
}

ItemType ItemGenerationManager::generate_item_type_by_val(const int val) const
{
  ItemType itype = ItemType::ITEM_TYPE_NULL;

  if (val <= 1)
  {
    itype = ItemType::ITEM_TYPE_BOAT;
  }
  else if (val <= 3)
  {
    itype = ItemType::ITEM_TYPE_CURRENCY;
  }
  else if (val <= 5)
  {
    itype = ItemType::ITEM_TYPE_AMULET;
  }
  else if (val <= 7)
  {
    itype = ItemType::ITEM_TYPE_MISC;
  }
  else if (val <= 10)
  {
    itype = ItemType::ITEM_TYPE_TOOL;
  }
  else if (val <= 15)
  {
    itype = ItemType::ITEM_TYPE_SPELLBOOK;
  }
  else if (val <= 20)
  {
    itype = ItemType::ITEM_TYPE_RING;
  }
  else if (val <= 26)
  {
    itype = ItemType::ITEM_TYPE_WAND;
  }
  else if (val <= 34)
  {
    itype = ItemType::ITEM_TYPE_AMMUNITION;
  }
  else if (val <= 44)
  {
    itype = ItemType::ITEM_TYPE_WEAPON;
  }
  else if (val <= 54)
  {
    itype = ItemType::ITEM_TYPE_ARMOUR;
  }
  else if (val <= 69)
  {
    itype = ItemType::ITEM_TYPE_POTION;
  }
  else if (val <= 84)
  {
    itype = ItemType::ITEM_TYPE_SCROLL;
  }
  else if (val <= 100)
  {
    itype = ItemType::ITEM_TYPE_FOOD;
  }

  return itype;
}

// Generate an item generation map for the given danger level and rarity.
ItemGenerationMap ItemGenerationManager::generate_item_generation_map(const ItemGenerationConstraints& igc)
{
  int min_danger = max(igc.get_min_danger_level(), 1);
  ItemGenerationMap generation_map;

  ItemPtr generated_creature;
  Game& game = Game::instance();
  
  ItemMap items = game.get_items_ref();
  GenerationValuesMap igv_map = game.get_item_generation_values_ref();

  CreaturePtr biasing_creature = Game::instance().get_current_player();
  int pct_chance_gen = 100 - spellbook_squelch_pct;

  while (generation_map.empty() && min_danger > 0)
  {
    // Build the map of items available for generation given the danger level and rarity
    for (ItemMap::iterator i_it = items.begin(); i_it != items.end(); i_it++)
    {
      string item_id = i_it->first;
      ItemPtr item = i_it->second;
      GenerationValues igvals = igv_map[item_id];

      if (item && 
          does_item_match_generation_criteria(igvals, min_danger, igc.get_max_danger_level(), igc.get_rarity(), igc.get_item_type_restrictions(), igc.get_min_value()))
      {
        bool item_usable = CreatureUtils::is_item_usable(biasing_creature, item);

        if (item_usable || RNG::percent_chance(pct_chance_gen))
        {
          generation_map[item->get_type()][igvals.get_rarity()].push_back(make_pair(item_id, make_pair(item, igvals)));
        }
      }
    }

    min_danger /= 2;
  }
  
  return generation_map;
}

vector<string> ItemGenerationManager::get_item_ids(const ItemGenerationMap& igm)
{
  vector<string> item_ids;

  for (const auto& igm_pair : igm)
  {
    const map<Rarity, vector<ItemGenerationPair>>& ivec = igm_pair.second;

    for (const auto& iid : ivec)
    {
      for (const auto& items : iid.second)
      {
        item_ids.push_back(items.first);
      }
    }
  }

  return item_ids;
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

ItemPtr ItemGenerationManager::generate_item(ActionManager& am, ItemGenerationMap& generation_map, const Rarity rarity, const vector<ItemType>& item_type_restrictions, const int enchant_points)
{
  ItemPtr generated_item;
  AmmunitionCalculator ac;

  ItemType gen_type = generate_item_type();

  // If the nicely generated type falls outside of what we're supposed
  // to generate, then just pick a type randomly.
  if (!item_type_restrictions.empty())
  {
    if (std::find(item_type_restrictions.begin(), item_type_restrictions.end(), gen_type) == item_type_restrictions.end())
    {
      gen_type = item_type_restrictions.at(RNG::range(0, item_type_restrictions.size() - 1));
    }
  }

  // The map already contains appropriate items filtered by danger level,
  // so pick one at random.
  if (!generation_map.empty())
  {
    Rarity item_rarity = get_item_rarity(rarity);
    vector<ItemGenerationPair> rarity_vec;

    while (rarity_vec.empty())
    {
      auto ig_it = generation_map.find(gen_type);

      if (ig_it != generation_map.end())
      {
        rarity_vec = ig_it->second[item_rarity];
      }

      if (rarity_vec.empty())
      {
        if (item_rarity == Rarity::RARITY_COMMON)
        {
          // Bust out of this loop - nothing can be generated
          return generated_item;
        }
        else
        {
          item_rarity--;
        }
      }
    }

    ItemGenerationPair rand_item = rarity_vec.at(RNG::range(0, rarity_vec.size()-1));
    string item_id = rand_item.first;

    generated_item = ItemManager::create_item(item_id);

    if (generated_item != nullptr)
    {
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
  }

  return generated_item;
}

// Check to see if the item matches the given danger level and rarity.
bool ItemGenerationManager::does_item_match_generation_criteria(const GenerationValues& cgv, const int min_danger_level, const int max_danger_level, const Rarity rarity, const vector<ItemType>& item_type_restrictions, const int min_value)
{
  ItemType itype = ItemType::ITEM_TYPE_NULL;
  string prop_itype = cgv.get_property(GenerationProperties::GENERATION_PROPERTIES_ITEM_TYPE);
  string prop_value = cgv.get_property(GenerationProperties::GENERATION_PROPERTIES_VALUE);
  int cgv_min_val = -1;

  if (!prop_itype.empty())
  {
    itype = static_cast<ItemType>(String::to_int(prop_itype));
  }

  if (!prop_value.empty())
  {
    cgv_min_val = String::to_int(prop_value);
  }

  int cgv_danger_level = cgv.get_danger_level();

  if ( cgv_danger_level >= 0 /* Exclude danger level of -1, which means "don't generate" */
    && cgv_danger_level >= min_danger_level
    && cgv_danger_level <= max_danger_level
    && cgv_min_val >= min_value
    // If the item type restrictions vector is empty - no restrictions
    // Otherwise, the item type has to be found within the container.
    && (item_type_restrictions.empty() || (std::find(item_type_restrictions.begin(), item_type_restrictions.end(), itype) != item_type_restrictions.end()))
    && cgv.get_rarity() <= rarity )
  {
    return true;
  }
  
  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemGenerationManager_test.cpp"
#endif
