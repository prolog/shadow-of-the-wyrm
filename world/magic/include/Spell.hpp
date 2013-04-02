#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "SkillTypes.hpp"

class Spell
{
  public:
    Spell();
    Spell(const std::string& spell_id, const std::string& spell_name, const SkillType skill_type);
    bool operator==(const Spell& sp);

    void set_spell_id(const std::string& new_spell_id);
    std::string get_spell_id() const;

    void set_spell_name_sid(const std::string& new_spell_name_sid);
    std::string get_spell_name_sid() const;

    void set_magic_category(const SkillType new_skill_type);
    SkillType get_magic_category() const;

  protected:
    std::string spell_id;
    std::string spell_name_sid;
    SkillType magic_category;
};

typedef std::map<std::string, Spell> SpellMap;