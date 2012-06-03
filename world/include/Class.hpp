#pragma once
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include "common.hpp"
#include "Resistances.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"

class Class
{
  public:
    Class();
    ~Class();

    void set_class_id(const std::string& id);
    std::string get_class_id() const;

    void set_class_name_sid(const std::string& new_class_name_sid);
    std::string get_class_name_sid() const;

    void set_class_description_sid(const std::string& new_class_description_sid);
    std::string get_class_description_sid() const;

    void set_class_abbreviation_sid(const std::string& new_class_abbreviation_sid);
    std::string get_class_abbreviation_sid() const;

    void set_starting_valour(const Statistic& new_valour);
    Statistic get_starting_valour() const;

    void set_starting_spirit(const Statistic& new_spirit);
    Statistic get_starting_spirit() const;

    void set_strength_modifier(const int new_strength_modifier);
    int  get_strength_modifier() const;

    void set_dexterity_modifier(const int new_dexterity_modifier);
    int  get_dexterity_modifier() const;

    void set_agility_modifier(const int new_agility_modifier);
    int  get_agility_modifier() const;

    void set_health_modifier(const int new_health_modifier);
    int  get_health_modifier() const;

    void set_intelligence_modifier(const int new_intelligence_modifier);
    int  get_intelligence_modifier() const;

    void set_willpower_modifier(const int new_willpower_modifier);
    int  get_willpower_modifier() const;

    void set_charisma_modifier(const int new_charisma_modifier);
    int  get_charisma_modifier() const;

    void set_resistances(const Resistances& resistances);
    Resistances get_resistances() const;

    void set_skills(const Skills& skills);
    Skills get_skills() const;

    void set_user_playable(const bool playable);
    bool get_user_playable() const;

    void set_experience_multiplier(const float new_multiplier);
    float get_experience_multiplier() const;

    // Hit and AP dice.
    void set_hit_dice(const uint new_hit_dice);
    uint get_hit_dice() const;

    void set_ap_dice(const uint new_ap_dice);
    uint get_ap_dice() const;

    std::string str() const;

  protected:
    std::string class_id;

    std::string class_name_sid;
    std::string class_description_sid;
    std::string class_abbreviation_sid;

    Statistic starting_valour;
    Statistic starting_spirit;

    int strength_modifier;
    int dexterity_modifier;
    int agility_modifier;
    int health_modifier;
    int intelligence_modifier;
    int willpower_modifier;
    int charisma_modifier;

    Resistances resistances;
    Skills skills;

    bool user_playable;
    float experience_multiplier;
    
    // The dice to use each level for a creature's HP and AP
    uint hit_dice;
    uint ap_dice;
};

typedef boost::shared_ptr<Class> ClassPtr;
typedef std::map<std::string, ClassPtr> ClassMap;
