#pragma once
#include "DamageCalculator.hpp"

class PhysicalDamageCalculator : public DamageCalculator
{
  public:
    PhysicalDamageCalculator(const AttackType new_attack_type, const PhaseOfMoonType new_pom);
    virtual ~PhysicalDamageCalculator() = default;
    
    virtual int calculate(CreaturePtr defending_creature, const bool sneak_attack, const bool slays_creatures_race, const Damage& damage, const int base_damage, const float soak_multiplier) override;
    virtual Damage calculate_base_damage_object(CreaturePtr attacking_creature) override;
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature) override;
    virtual int get_statistic_based_damage_modifier(CreaturePtr attacking_creature);
    virtual int get_skill_based_damage_modifier(CreaturePtr attacking_creature);
    virtual Damage calculate_default_damage_for_improvised_weapon(ItemPtr item);

    virtual SkillType get_general_combat_skill() const;
    
  protected:
    virtual void set_item_status_based_damage_modifiers(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage);
    virtual void set_skill_based_statuses(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage);
    virtual void set_skill_based_damage_flags(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage);
    virtual void set_skill_based_damage_modifiers(CreaturePtr attacking_creature, const AttackType attack_type, Damage& damage);

    static const int DAMAGE_STAT_BASELINE;
    static const int DAMAGE_STAT_DIVISOR;
    static const int DAMAGE_SKILL_DIVISOR;
    static const int DAMAGE_GENERAL_SKILL_DIVISOR;
    static const int DAMAGE_GENERAL_DUAL_WIELD_DIVISOR;
    static const float INCORPOREAL_SOAK_MULTIPLIER;
};
