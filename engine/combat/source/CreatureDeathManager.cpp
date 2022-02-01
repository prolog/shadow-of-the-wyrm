#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "CorpseCalculator.hpp"
#include "CorpseFactory.hpp"
#include "CreationUtils.hpp"
#include "CreatureProperties.hpp"
#include "CreatureDeathManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemDropRateCalculator.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceConstants.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"

using namespace std;

CreatureDeathManager::CreatureDeathManager(CreaturePtr a_creature, CreaturePtr d_creature, MapPtr current_map)
: DeathManager(a_creature, d_creature, current_map)
{
}

CreatureDeathManager::~CreatureDeathManager()
{
}

void CreatureDeathManager::die() const
{
  if (map && dead_creature)
  {
    IInventoryPtr ground = MapUtils::get_tile_for_creature(map, dead_creature)->get_items();

    add_creature_death_messages(attacking_creature, dead_creature);
    run_death_event(dead_creature, attacking_creature, map);
    MapUtils::remove_creature(map, dead_creature);
    remove_creature_equipment_and_drop_inventory_on_tile(map, dead_creature, ground);
    potentially_generate_random_drop(attacking_creature, dead_creature, ground);
    potentially_generate_corpse(attacking_creature, dead_creature, ground);
    potentially_generate_primordial_essence(attacking_creature, dead_creature, ground);
  }
}

// If necessary, add messages about the creature's death.
void CreatureDeathManager::add_creature_death_messages(CreaturePtr attacking_creature, CreaturePtr dead_creature) const
{
  // Add the message about the creature's death.
  //
  // Ensure that this is the first thing done, e.g., prior to actually
  // removing it from the map, so that view map checks work as expected.
  // Otherwise, the creature will already be gone from the other creatures'
  // view maps.
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, dead_creature, GameUtils::is_player_among_creatures(attacking_creature, dead_creature));

  // If the creature was killed by another creature, get a message of the form
  // "the foo is killed!".  Otherwise, if the creature was killed by something
  // other than a creature (poison, falling, etc), use "the foo dies!".
  string death_message;
  string creature_desc = StringTable::get(dead_creature->get_description_sid());

  if (attacking_creature)
  {
    death_message = CombatTextKeys::get_monster_killed_message(creature_desc);
  }
  else
  {
    death_message = CombatTextKeys::get_monster_dies_message(creature_desc);
  }

  manager.add_new_message(death_message);
  manager.send();
}

// Remove the creature's equipment, adding it to the creature's inventory.
// Then, drop all the items on the tile.
void CreatureDeathManager::remove_creature_equipment_and_drop_inventory_on_tile(MapPtr map, CreaturePtr dead_creature, IInventoryPtr ground) const
{
  Game& game = Game::instance();

  bool drop_eq = true;
  string drop_eq_prop = dead_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEAVES_EQUIPMENT);

  if (!drop_eq_prop.empty())
  {
    drop_eq = String::to_bool(drop_eq_prop);
  }

  if (drop_eq)
  {
    // Remove all equipment.
    for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
    {
      EquipmentWornLocation worn_slot = static_cast<EquipmentWornLocation>(e);
      game.actions.remove_item(dead_creature, static_cast<EquipmentWornLocation>(worn_slot));
    }

    // Drop inventory on to the creature's tile.
    IInventoryPtr inv = dead_creature->get_inventory();

    while (!inv->empty())
    {
      ItemPtr current_item = inv->at(0);
      inv->remove(current_item->get_id());
      ground->add_front(current_item);
    }
  }
}

// With some probability, create a random item drop when the creature dies.
void CreatureDeathManager::potentially_generate_random_drop(CreaturePtr attacking_creature, CreaturePtr dead_creature, IInventoryPtr ground) const
{
  Game& game = Game::instance();
  vector<ItemPtr> generated_items;
  ItemGenerationManager igm;
  ItemManager im;
  RaceManager rm;
  ItemDropRateCalculator idrc;
  bool consider_random_drop = true;

  if (dead_creature)
  {
    string consider_random_drop_prop = dead_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_ALLOWS_RANDOM_DROPS);

    if (!consider_random_drop_prop.empty())
    {
      consider_random_drop = String::to_bool(consider_random_drop_prop);
    }

    if (consider_random_drop)
    {
      // Go through all the drops for the creature's race and parent races.
      // See if any items should be generated.
      RaceManager rm;
      std::map<string, DropParameters> items = rm.get_all_drops(dead_creature->get_race_id());

      for (const auto& item_gen_pair : items)
      {
        string item_base_id = item_gen_pair.first;
        DropParameters dp = item_gen_pair.second;
        int item_base_chance = dp.get_percent_chance();

        if (RNG::percent_chance(idrc.calculate_pct_chance_item_drop(attacking_creature, item_base_chance)))
        {
          ItemPtr racial_item = ItemManager::create_item(item_base_id, RNG::dice(dp.get_min(), dp.get_max()));

          if (racial_item != nullptr)
          {
            generated_items.push_back(racial_item);
          }
        }
      }
    }
  }

  // When a creature in general dies, there is a small chance it will drop 
  // a randomly generated item that is not part of a set of pre-specified
  // racial items.
  if (consider_random_drop && RNG::percent_chance(idrc.calculate_pct_chance_item_drop(attacking_creature)))
  {
    Rarity rarity = CreationUtils::generate_rarity();
    int danger_level = dead_creature->get_level().get_current();
    vector<ItemType> i_restr = {};
    ItemGenerationMap generation_map = igm.generate_item_generation_map({1, danger_level, rarity, i_restr, ItemValues::DEFAULT_MIN_GENERATION_VALUE});

    int enchant_points = RNG::range(0, (danger_level / 2));
    ItemPtr generated_item = igm.generate_item(game.get_action_manager_ref(), generation_map, rarity, i_restr, enchant_points);

    if (generated_item != nullptr)
    {
      generated_items.push_back(generated_item);
    }
  }

  for (const ItemPtr i : generated_items)
  {
    if (i != nullptr)
    {
      ground->add_front(i);
    }
  }
}

// With some probability, create a creature corpse.
void CreatureDeathManager::potentially_generate_corpse(CreaturePtr attacking_creature, CreaturePtr dead_creature, IInventoryPtr ground) const
{
  bool leaves_corpse = false;
  bool corpse_poisoned = false;

  if (dead_creature)
  {
    RaceManager rm;
    Race* race = rm.get_race(dead_creature->get_race_id());

    if (race)
    {
      leaves_corpse = race->get_leaves_corpse();
      corpse_poisoned = (dead_creature->get_base_damage().get_damage_type() == DamageType::DAMAGE_TYPE_POISON || race->get_corpse_poisoned());
    }

    string leaves_corpse_prop = dead_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEAVES_CORPSE);

    if (!leaves_corpse_prop.empty())
    {
      leaves_corpse = leaves_corpse && String::to_bool(leaves_corpse_prop);
    }
  }

  // Potentially generate a corpse as well.
  CorpseCalculator cc;
  if (RNG::percent_chance(cc.calculate_chance_corpse(attacking_creature)) && leaves_corpse)
  {
    CorpseFactory cf;
    ItemPtr corpse = cf.create_corpse(attacking_creature, dead_creature);

    if (corpse != nullptr)
    {
      // Train the attacker's Hunting.
      if (attacking_creature != nullptr)
      {
        attacking_creature->get_skills().mark(SkillType::SKILL_GENERAL_HUNTING);
      }

      // Poison it if applicable
      ConsumablePtr consum = std::dynamic_pointer_cast<Consumable>(corpse);

      if (consum != nullptr && corpse_poisoned)
      {
        consum->set_poisoned(true);
      }

      ground->add_front(corpse);
    }
  }
}

// Creatures with primordial attacks might leave primordial essence.
void CreatureDeathManager::potentially_generate_primordial_essence(CreaturePtr attacking_creature, CreaturePtr attacked_creature, IInventoryPtr ground) const
{
  if (attacked_creature != nullptr && ground != nullptr)
  {
    CorpseCalculator cc;

    if (RNG::percent_chance(cc.calculate_chance_primordial_essence(attacking_creature, attacked_creature)))
    {
      ItemPtr essence = ItemManager::create_item(ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE);

      if (essence != nullptr)
      {
        ground->merge_or_add(essence, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
      }
    }
  }
}