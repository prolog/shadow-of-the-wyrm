#include <cmath>
#include "CombatConstants.hpp"
#include "PhysicalDamageCalculator.hpp"
#include "RNG.hpp"
#include "StatusEffectFactory.hpp"
#include "WeaponManager.hpp"

using namespace std;

// Always check to see if a stat is > 10 before considering it for a damage bonus.
const int PhysicalDamageCalculator::DAMAGE_STAT_BASELINE = 10;

// A creature gets +1 damage for every 5 points over 10 in the appropriate statistic (strength for physical,
// dex for ranged, etc).
const int PhysicalDamageCalculator::DAMAGE_STAT_DIVISOR = 5;

// A creature gets +1 damage for every 10 points in the relevant weapon skill.
const int PhysicalDamageCalculator::DAMAGE_SKILL_DIVISOR = 10;

// A creature gets +1 damage for every 20 points in Combat or Archery.
const int PhysicalDamageCalculator::DAMAGE_GENERAL_SKILL_DIVISOR = 20;

// A creature gets +1 damage for every point of Dual Wield when the attack
// is secondary.
const int PhysicalDamageCalculator::DAMAGE_GENERAL_DUAL_WIELD_DIVISOR = 10;

// When an attack is incorporeal, it allows only a fraction of the available
// soak.
const float PhysicalDamageCalculator::INCORPOREAL_SOAK_MULTIPLIER = 0.25f;

PhysicalDamageCalculator::PhysicalDamageCalculator(const AttackType new_attack_type, const PhaseOfMoonType new_pom)
: DamageCalculator(new_attack_type, new_pom)
{
}

// Physical Damage =
// (Rolled damage * Resistance to that damage type)
// * 2, if sneak attack
// * 2, if the weapon slays the creature's race.
// - Soak
int PhysicalDamageCalculator::calculate(CreaturePtr defending_creature, const bool sneak_attack, const bool slays_creatures_race, const Damage& physical_damage, const int base_damage, const float soak_multiplier)
{
  int damage = 0;
  float soak_mult = soak_multiplier;

  if (defending_creature)
  {
    DamageType damage_type = physical_damage.get_damage_type();
    
    double resistance_multiplier = defending_creature->get_resistances().get_resistance_value(damage_type);
    double pom_multiplier = get_phase_of_moon_multiplier(damage_type, pom_type);
    double sneak_multiplier = get_sneak_attack_multiplier(sneak_attack);

    double resisted_damage = base_damage * std::max(resistance_multiplier, 0.0) * pom_multiplier * sneak_multiplier;
    
    if (resisted_damage > 0)
    {
      if (physical_damage.get_piercing())
      {
        soak_mult = 0;
      }
      else if (physical_damage.get_incorporeal())
      {
        soak_mult = INCORPOREAL_SOAK_MULTIPLIER;
      }

      // Apply soak if damage is not negative.
      // Negative damage is permitted in extreme cases - it allows things like gaining HP from
      // fire damage, etc.
      double total_soak = static_cast<double>(defending_creature->get_soak().get_current()) * soak_mult;

      if (slays_creatures_race)
      {
        resisted_damage *= CombatConstants::RACE_SLAY_MULTIPLIER;
      }
      
      damage = static_cast<int>(ceil(std::max<double>(0, resisted_damage - total_soak)));
    }
    else
    {
      // If the damage is negative (healing), ignore soak.
      damage = static_cast<int>(resisted_damage);
    }
  }

  return damage;
}

// Get the base damage.
Damage PhysicalDamageCalculator::calculate_base_damage_object(CreaturePtr attacking_creature)
{
  WeaponManager wm;
  return wm.get_damage(attacking_creature, attack_type);
}

// Physical damage gets +1 for every 5 points of Strength over 10, plus
// the creature's base additional damage.  If the attacking creature is
// enraged, there's a further bonus of +1/level.
Damage PhysicalDamageCalculator::calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature)
{
  Damage base_damage = calculate_base_damage_object(attacking_creature);
  
  if (attacking_creature)
  {
    int current_modifier = base_damage.get_modifier() + attacking_creature->get_addl_damage().get_current();
    int bac_modifier = static_cast<int>(attacking_creature->get_blood().get_blood_alcohol_content() * 100) / 2;
    int rage_modifier = 0;
    
    if (attacking_creature->has_status(StatusIdentifiers::STATUS_ID_RAGE))
    {
      rage_modifier = attacking_creature->get_level().get_current() * 2;
    } 

    current_modifier += get_statistic_based_damage_modifier(attacking_creature);
    current_modifier += get_skill_based_damage_modifier(attacking_creature);
    current_modifier += bac_modifier;
    current_modifier += rage_modifier;
    
    base_damage.set_modifier(current_modifier);

    set_skill_based_statuses(attacking_creature, attack_type, base_damage);
    set_skill_based_damage_flags(attacking_creature, attack_type, base_damage);
    set_skill_based_damage_modifiers(attacking_creature, attack_type, base_damage);
  }
  
  return base_damage;
}

// For physical damage (not ranged), Str is the stat used to calculate the damage bonus.
// +1 damage for every 5 points of str > 10.
int PhysicalDamageCalculator::get_statistic_based_damage_modifier(CreaturePtr attacking_creature)
{
  int modifier = 0;
  
  if (attacking_creature)
  {
    int current_strength = attacking_creature->get_strength().get_current();

    if (current_strength > DAMAGE_STAT_BASELINE)
    {
      current_strength -= DAMAGE_STAT_BASELINE;
      modifier = current_strength / DAMAGE_STAT_DIVISOR;
    }    
  }
  
  return modifier;
}

// Get the damage modifier that is calculated based on combat/archery, and the
// applicable melee or ranged weapon, plus the dual wield bonus if this is
// a secondary weapon.  The dual wield bonus is to encourage the use of the
// skill rather than e.g. a shield.
int PhysicalDamageCalculator::get_skill_based_damage_modifier(CreaturePtr attacking_creature)
{
  int modifier = 0;

  if (attacking_creature)
  {
    Skills& skills = attacking_creature->get_skills();

    int dual_val = 0;
    if (attack_type == AttackType::ATTACK_TYPE_MELEE_SECONDARY)
    {
      dual_val = skills.get_value(SkillType::SKILL_GENERAL_DUAL_WIELD);
    }

    WeaponManager wm;
    SkillType skill = wm.get_skill_type(attacking_creature, attack_type);
    int val = skills.get_value(skill);

    SkillType general_skill = get_general_combat_skill();
    int general_val = skills.get_value(general_skill);

    modifier += (dual_val / DAMAGE_GENERAL_DUAL_WIELD_DIVISOR);
    modifier += (val / DAMAGE_SKILL_DIVISOR);
    modifier += (general_val / DAMAGE_GENERAL_SKILL_DIVISOR);

    if (general_skill == SkillType::SKILL_GENERAL_ARCHERY && val == 100)
    {
      modifier += attacking_creature->get_level().get_current() / 2;
    }
    else if (general_skill == SkillType::SKILL_GENERAL_COMBAT && 
             (skill == SkillType::SKILL_MELEE_UNARMED || skill == SkillType::SKILL_MELEE_WHIPS) && 
             val == 100)
    {
      modifier += 10;
    }
  }

  return modifier;
}

// Improvised weapons do 1d2 damage plus a bonus based on their weight.
Damage PhysicalDamageCalculator::calculate_default_damage_for_improvised_weapon(ItemPtr item)
{
  Damage dmg;

  if (item != nullptr)
  {
    dmg.set_num_dice(1);
    dmg.set_dice_sides(2);
    dmg.set_damage_type(DamageType::DAMAGE_TYPE_POUND);

    // For every additional 10 lbs, add +1 dmg
    Weight weight = item->get_weight();
    int mod = static_cast<int>(weight.get_weight_in_lbs()) / 10;

    dmg.set_modifier(mod);
  }
  
  return dmg;
}

SkillType PhysicalDamageCalculator::get_general_combat_skill() const
{
  return SkillType::SKILL_GENERAL_COMBAT;
}

void PhysicalDamageCalculator::set_skill_based_statuses(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage)
{
  if (attacking_creature != nullptr)
  {
    WeaponManager wm;
    Skills& skills = attacking_creature->get_skills();
    SkillType skill = wm.get_skill_type(attacking_creature, attack_type);
    int val = skills.get_value(skill);

    SkillType general_skill = get_general_combat_skill();

    if (general_skill == SkillType::SKILL_GENERAL_COMBAT &&
        skill == SkillType::SKILL_MELEE_WHIPS &&
        val == 100)
    {
      StatusAilments sa = damage.get_status_ailments();
      set<string>& ailments = sa.get_ailments_ref();

      sa.set_override_defaults(true);
      ailments.insert(StatusEffectFactory::get_status_identifier_for_damage_type(damage.get_damage_type()));
      ailments.insert(StatusIdentifiers::STATUS_ID_BLOODIED);
      ailments.insert(StatusIdentifiers::STATUS_ID_EXPOSED);

      damage.set_status_ailments(sa);
    }
  }
}

void PhysicalDamageCalculator::set_skill_based_damage_flags(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage)
{
  if (attacking_creature != nullptr)
  {
    WeaponManager wm;
    Skills& skills = attacking_creature->get_skills();
    SkillType skill = wm.get_skill_type(attacking_creature, attack_type);
    int val = skills.get_value(skill);

    SkillType general_skill = get_general_combat_skill();

    if (general_skill == SkillType::SKILL_GENERAL_COMBAT &&
        skill == SkillType::SKILL_MELEE_SPEARS &&
        val == 100)
    {
      damage.set_piercing(true);
    }
  }
}

void PhysicalDamageCalculator::set_skill_based_damage_modifiers(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage)
{
  if (attacking_creature != nullptr)
  {
    WeaponManager wm;
    Skills& skills = attacking_creature->get_skills();
    SkillType skill = wm.get_skill_type(attacking_creature, attack_type);
    int val = skills.get_value(skill);

    SkillType general_skill = get_general_combat_skill();

    if (general_skill == SkillType::SKILL_GENERAL_COMBAT &&
        (skill == SkillType::SKILL_MELEE_BLUDGEONS || skill == SkillType::SKILL_MELEE_EXOTIC) &&
        val == 100)
    {
      damage.set_effect_bonus(damage.get_effect_bonus() + 50);
    }
  }
}


#ifdef UNIT_TESTS
#include "unit_tests/PhysicalDamageCalculator_test.cpp"
#endif

