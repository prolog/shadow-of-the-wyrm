#include "CombatConstants.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "WeaponDifficultyCalculator.hpp"

using std::dynamic_pointer_cast;

const int WeaponDifficultyCalculator::BASE_DUAL_DIFFICULTY = 50;
const int WeaponDifficultyCalculator::SKILLED_BASE_DUAL_DIFFICULTY = 20;
const int WeaponDifficultyCalculator::MINIMUM_DUAL_DIFFICULTY = 2;
const int WeaponDifficultyCalculator::HEAVY_WEAPON_PENALTY = 25;

int WeaponDifficultyCalculator::calculate_base_difficulty(CreaturePtr creature, const AttackType attack_type)
{
  int difficulty = 0;
  WeaponPtr primary_weapon, secondary_weapon;

  if (creature)
  {
    primary_weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));
    secondary_weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

    switch(attack_type)
    {
      case AttackType::ATTACK_TYPE_RANGED:
      case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
        difficulty = get_difficulty_for_weapon(primary_weapon);
        break;
      case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
        difficulty = get_difficulty_for_weapon(secondary_weapon);
        difficulty += get_difficulty_penalty_for_dual_wield(creature, primary_weapon, secondary_weapon);
        break;
      case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
      case AttackType::ATTACK_TYPE_MAGICAL:
      default:
        difficulty = get_difficulty_for_weapon(primary_weapon);
        break;
    }
  }

  return difficulty;
}

int WeaponDifficultyCalculator::get_difficulty_for_weapon(WeaponPtr weapon)
{
  int difficulty;

  if (weapon)
  {
    difficulty = weapon->get_difficulty();
  }
  else
  {
    difficulty = CombatConstants::BASE_WEAPON_DIFFICULTY;
  }
  
  return difficulty;
}

// Get the "total" difficulty for the weapon.  This is not directly used in
// game, but is useful for players because they can see the character's
// to-hit reflected by the lower difficulty.
int WeaponDifficultyCalculator::calculate_total_difficulty_for_display(CreaturePtr creature, const AttackType attack_type)
{
  ToHitCalculatorPtr th_calculator = ToHitCalculatorFactory::create_to_hit_calculator(creature, attack_type);

  int base_difficulty = calculate_base_difficulty(creature, attack_type);
  // "Total difficulty" as a concept is only used here.
  // The CombatManager uses base_roll + to_hit, instead of "weapon_difficulty - to_hit".
  int total_difficulty = base_difficulty - th_calculator->calculate(creature);

  return total_difficulty;
}

int WeaponDifficultyCalculator::get_difficulty_penalty_for_dual_wield(CreaturePtr creature, WeaponPtr primary, WeaponPtr secondary)
{
  int difficulty = BASE_DUAL_DIFFICULTY;

  if (creature != nullptr)
  {
    int dual_skill = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DUAL_WIELD);

    // If the creature has any training in Dual Wield, the difficulty is
    // sharply reduced.
    if (dual_skill > 0)
    {
      difficulty = SKILLED_BASE_DUAL_DIFFICULTY;
    }

    // For each 5 points of dual wield, reduce the difficulty by 1.
    difficulty -= (dual_skill / 5);

    Weight max_weight = get_max_unpenalized_weapon_weight(creature);

    if (secondary != nullptr)
    {
      Weight secondary_weight = secondary->get_weight();

      if (secondary_weight > max_weight)
      {
        difficulty += HEAVY_WEAPON_PENALTY;
      }
    }
  }

  return difficulty;
}

Weight WeaponDifficultyCalculator::get_max_unpenalized_weapon_weight(CreaturePtr creature)
{
  Weight max_weight(0);

  if (creature != nullptr)
  {
    Statistic str = creature->get_strength();

    // For every five points of strength, a creature can carry a pound of 
    // weight in the off hand without penalty.  Every creature can always
    // carry at least a pound without penalty in their off hand (the
    // dagger rule).
    int max_weight_oz = std::max(16, 16 * (str.get_current() / 5));
    max_weight.set_weight(max_weight_oz);
  }

  return max_weight;
}