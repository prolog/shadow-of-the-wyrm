#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "SkillTypes.hpp"

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

  protected:
    std::string spell_id;
    std::string spell_name_sid;
    SkillType magic_category;
    uint ap_cost;
    int speed;
};

typedef std::map<std::string, Spell> SpellMap;