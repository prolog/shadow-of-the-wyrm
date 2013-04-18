#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Damage.hpp"
#include "EffectTypes.hpp"
#include "SkillTypes.hpp"
#include "SpellTypes.hpp"
#include "SpellShape.hpp"

class Spell
{
  public:
    Spell();
    bool operator==(const Spell& sp);

    void set_spell_id(const std::string& new_spell_id);
    std::string get_spell_id() const;

    void set_spell_name_sid(const std::string& new_spell_name_sid);
    std::string get_spell_name_sid() const;

    void set_magic_category(const SkillType new_skill_type);
    SkillType get_magic_category() const;

    void set_ap_cost(const uint new_ap_cost);
    uint get_ap_cost() const;

    void set_speed(const int new_speed);
    int get_speed() const;

    void set_range(const uint new_range);
    uint get_range() const;

    void set_shape(const SpellShape& new_shape);
    SpellShape get_shape() const;

    void set_has_damage(const bool new_has_damage);
    bool get_has_damage() const;

    void set_damage(const Damage& new_damage);
    Damage get_damage() const;

    void set_effect(const EffectType new_effect);
    EffectType get_effect() const;

  protected:
    std::string spell_id;
    std::string spell_name_sid;
    SkillType magic_category;
    uint ap_cost;
    int speed;
    uint range;
    SpellShape shape;
    EffectType effect;

    // If the spell has damage associated with it, and what that damage is.
    bool has_damage;
    Damage damage;
};

typedef std::map<std::string, Spell> SpellMap;