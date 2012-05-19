#include "CombatConstants.hpp"
#include "CombatManager.hpp"
#include "DamageCalculatorFactory.hpp"
#include "Game.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "RNG.hpp"
#include "WeaponManager.hpp"

using std::string;

CombatManager::CombatManager()
{
}

// Attempt to attack.
//
// An attack is successful if:
//
// The generated to-hit value is 100 (ignore Soak, 2x max damage, any resistance is min 100%)
// The generated to-hit value is >= 96 (ignore Soak, max damage, any resistance is min 100%)
// The generated to-hit value is >= the target number (regular damage)
bool CombatManager::attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  WeaponManager wm;
  AttackType FIXME_ATTACK_TYPE = ATTACK_TYPE_MELEE_PRIMARY;
  
  // JCD FIXME add support for other types later.
  ToHitCalculatorPtr th_calculator = ToHitCalculatorFactory::create_to_hit_calculator(attacking_creature, FIXME_ATTACK_TYPE);
  CombatTargetNumberCalculatorPtr ctn_calculator = CombatTargetNumberCalculatorFactory::create_target_number_calculator(FIXME_ATTACK_TYPE);
  
  if (th_calculator && ctn_calculator)
  {
    int d100_roll = RNG::range(1, 100);
    int to_hit_value = th_calculator->calculate(attacking_creature);
    int total_roll = d100_roll + to_hit_value;
    int target_number_value = ctn_calculator->calculate(attacking_creature, attacked_creature);
    Damage damage = wm.get_damage(attacking_creature, FIXME_ATTACK_TYPE);
    
    // Automatic miss is checked first
    if (is_automatic_miss(d100_roll))
    {
      miss(attacking_creature, attacked_creature);
    }
    // Hit
    else if (is_hit(total_roll, target_number_value))
    {
      hit(attacking_creature, attacked_creature, d100_roll, damage, FIXME_ATTACK_TYPE);
    }
    // Close miss (flavour text only.)
    else if (is_close_miss(total_roll, target_number_value))
    {
      close_miss(attacking_creature, attacked_creature);
    }
    // Miss
    else if (is_miss(total_roll, target_number_value))
    {
      miss(attacking_creature, attacked_creature);
    }    
  }
  
  send_combat_messages();
  
  return true;
}

bool CombatManager::hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage_info, const AttackType attack_type)
{
  DamageType damage_type = damage_info.get_damage_type();
  int base_damage = 0;
  float soak_multiplier = 1.0;
  
  string combat_message = CombatTextKeys::get_hit_message(attacking_creature->get_is_player(), damage_type, StringTable::get(attacking_creature->get_description_sid()), StringTable::get(attacked_creature->get_description_sid()));

  // Critical hit: 2x damage, no soak.
  if (is_critical_hit(d100_roll))
  {
    combat_message += " " + StringTable::get(CombatTextKeys::COMBAT_CRITICAL_HIT_MESSAGE);
    base_damage = 2 * (damage_info.max());
    soak_multiplier = 0.0;
  }
  // Mighty blow: full damage, half soak.
  else if (is_mighty_blow(d100_roll))
  {
    combat_message += " " + StringTable::get(CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE);
    base_damage = damage_info.max();
    soak_multiplier = 0.5;
  }
  else // Regular, vanilla hit.  Roll damage, full soak.
  {
    base_damage = RNG::dice(damage_info);
  }
  
  // Deal damage.  JCD FIXME HANDLE MIGHTY BLOWS AND CRITICALS
  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type);
  int damage_dealt = damage_calc->calculate(attacked_creature, damage_info, base_damage, soak_multiplier);

  // Add the text so far.
  add_combat_message(combat_message);
  add_any_necessary_damage_messages(damage_dealt);

  // Deal the damage, handling death if necessary.
  deal_damage(attacked_creature, damage_dealt);

  return true;
}

// Deal damage to the creature, or heal it, depending on whether the damage dealt is
// positive or negative.
//
// Healing is for extreme resistance cases, like casting fireball on a fire elemental.
void CombatManager::deal_damage(CreaturePtr attacked_creature, const int damage_dealt)
{
  Game* game = Game::instance();
  MapPtr map = game->get_current_map();
  
  if (!damage_dealt)
  {
    // JCD FIXME: Message here.
  }
  else if (game && map && attacked_creature)
  {
    Statistic hp   = attacked_creature->get_hit_points();
    int current_hp = hp.get_current();
    current_hp    -= damage_dealt;
    hp.set_current(current_hp);
    attacked_creature->set_hit_points(hp);
    
    if (current_hp <= CombatConstants::DEATH_THRESHOLD)
    {
      // Remove the creature from the tile.
      TilePtr attacked_tile = MapUtils::get_tile_for_creature(map, attacked_creature);
      attacked_tile->remove_creature();
      map->remove_creature(attacked_creature->get_id());

      // Remove all equipment.
      for (int worn_slot = EQUIPMENT_WORN_HEAD; worn_slot < EQUIPMENT_WORN_LAST; worn_slot++)
      {
        game->actions.remove_item(attacked_creature, static_cast<EquipmentWornLocation>(worn_slot));
      }

      // Drop inventory on to the creature's tile.
      Inventory inv = attacked_creature->get_inventory();
      Inventory& ground = attacked_tile->get_items();
      while (!inv.empty())
      {
        ItemPtr current_item = inv.at(0);
        inv.remove(current_item->get_id());
        ground.add_front(current_item);
      }
      
      bool is_player = attacked_creature->get_is_player();
      string death_message;
      
      if (is_player)
      {
        // Display death message with -- more --
        death_message = TextMessages::get_death_message(attacked_creature->get_name());
        add_combat_message(death_message);
        
        // JCD FIXME: need functionality to add -- more --...
        
        // Signal to the game that it is time to quit.
        game->quit();
      }
      else
      {
        death_message = CombatTextKeys::get_monster_death_message(StringTable::get(attacked_creature->get_description_sid()));
        add_combat_message(death_message);
      }
    }
    
    // JCD FIXME handle death here.
  }
}

bool CombatManager::miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  string combat_message = CombatTextKeys::get_miss_message(attacking_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), StringTable::get(attacked_creature->get_description_sid()));
  add_combat_message(combat_message);

  return true;
}

bool CombatManager::close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  string combat_message = CombatTextKeys::get_close_miss_message(attacking_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), StringTable::get(attacked_creature->get_description_sid()));
  add_combat_message(combat_message);

  return true;
}

// Add messages if the damage dealt is 0 (unharmed), or negative
// (heals).
// 
// JCD FIXME Need to have the usual player vs. monster checks here
// so that these are only added when the target is not the player.
void CombatManager::add_any_necessary_damage_messages(const int damage)
{
  string additional_message;
  
  if (damage == 0)
  {
    // ...
  }
  else if (damage < 0)
  {
    // ...
  }
  
  if (!additional_message.empty())
  {
    add_combat_message(additional_message);
  }
}

void CombatManager::add_combat_message(const string& combat_message)
{
  // Display combat information.
  // Right now, everything is displayed.  Will need to do LOS checking later.
  MessageManager* manager = MessageManager::instance();
  if (manager)
  {
    manager->add_new_message(combat_message);
  }  
}

void CombatManager::send_combat_messages()
{
  MessageManager* manager = MessageManager::instance();
  if (manager)
  {
    manager->send();
  }
}

// Functions to check hit/miss/critical/etc statuses.
bool CombatManager::is_critical_hit(const int d100_roll)
{
  return (d100_roll == CombatConstants::CRITICAL_DIFFICULTY);
}

bool CombatManager::is_mighty_blow(const int d100_roll)
{
  return (d100_roll >= CombatConstants::MIGHTY_BLOW_DIFFICULTY);
}

bool CombatManager::is_hit(const int total_roll, const int target_number_value)
{
  return (total_roll > target_number_value);
}

bool CombatManager::is_miss(const int total_roll, const int target_number_value)
{
  return (total_roll <= target_number_value);
}

bool CombatManager::is_close_miss(const int total_roll, const int target_number_value)
{
  return (is_miss(total_roll, target_number_value) && ((target_number_value - total_roll) > CombatConstants::CLOSE_MISS_THRESHOLD));
}

bool CombatManager::is_automatic_miss(const int d100_roll)
{
  return (d100_roll <= CombatConstants::AUTOMATIC_MISS_THRESHOLD);
}

#ifdef UNIT_TESTS
#include "unit_tests/CombatManager_test.cpp"
#endif
