#pragma once
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <vector>
#include "AgeInfo.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"
#include "CreatureFeatures.hpp"
#include "Resistances.hpp"

class Race
{
  public:
    Race();
    ~Race();
    bool operator< (const Race& race);

    void set_race_id(const std::string& race_id);
    std::string get_race_id() const;

    void set_user_playable(const bool playable);
    bool get_user_playable() const;

    void set_race_name_sid(const std::string& race_sid);
    std::string get_race_name_sid() const;

    void set_race_short_description_sid(const std::string& race_short_desc_sid);
    std::string get_race_short_description_sid() const;

    void set_race_description_sid(const std::string& race_desc_sid);
    std::string get_race_description_sid() const;

    void set_race_abbreviation_sid(const std::string& race_abrv_sid);
    std::string get_race_abbreviation_sid() const;

    void set_size(const CreatureSize new_size);
    CreatureSize get_size() const;
    
    void set_age_info(const AgeInfo& age);
    AgeInfo get_age_info() const;

    void set_starting_strength(const Statistic& new_starting_strength);
    Statistic get_starting_strength() const;

    void set_starting_dexterity(const Statistic& new_starting_dexterity);
    Statistic get_starting_dexterity() const;

    void set_starting_agility(const Statistic& new_starting_agility);
    Statistic get_starting_agility() const;

    void set_starting_health(const Statistic& new_starting_health);
    Statistic get_starting_health() const;

    void set_starting_intelligence(const Statistic& new_starting_intelligence);
    Statistic get_starting_intelligence() const;

    void set_starting_willpower(const Statistic& new_starting_willpower);
    Statistic get_starting_willpower() const;

    void set_starting_charisma(const Statistic& new_starting_charisma);
    Statistic get_starting_charisma() const;

    void set_valour_modifier(const int new_valour_modifier);
    int get_valour_modifier() const;

    void set_spirit_modifier(const int new_spirit_modifier);
    int get_spirit_modifier() const;

    void set_starting_speed(const Statistic& new_starting_speed);
    Statistic get_starting_speed() const;

    void set_experience_multiplier(const float new_experience_multiplier);
    float get_experience_multiplier() const;
    
    void set_initial_deity_ids(const std::vector<std::string>& new_initial_deity_ids);
    std::vector<std::string> get_initial_deity_ids() const;

    void set_resistances(const Resistances& new_resistances);
    Resistances get_resistances() const;

    void set_skills(const Skills& skills);
    Skills get_skills() const;

    std::string str() const;

  protected:
    std::string race_id;
    bool user_playable;

    // Name & vitals
    std::string race_name_sid;
    std::string race_short_description_sid;
    std::string race_description_sid;
    std::string race_abbreviation_sid;
    CreatureSize size;
    AgeInfo age_info;

    // Initial primary statistics
    Statistic starting_strength;
    Statistic starting_dexterity;
    Statistic starting_agility;
    Statistic starting_health;
    Statistic starting_intelligence;
    Statistic starting_willpower;
    Statistic starting_charisma;

    // Initial secondary statistics or their modifiers
    int valour_modifier;
    int spirit_modifier;
    Statistic starting_speed;
    
    // Available deities on creation
    std::vector<std::string> initial_deity_ids;

    // Resistances
    Resistances resistances;

    // Skills
    Skills skills;

    // Level info
    float experience_multiplier;
    // LevelInfo level_info;
};

typedef boost::shared_ptr<Race> RacePtr;
typedef std::map<std::string, RacePtr> RaceMap;
