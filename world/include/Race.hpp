#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "AgeInfo.hpp"
#include "BoolStatistic.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"
#include "CreatureFeatures.hpp"
#include "Resistances.hpp"
#include "SettlementTypes.hpp"
#include "StatisticsModifier.hpp"
#include "tiles.hpp"

class Race
{
  public:
    Race();
    ~Race();
    bool operator< (const Race& race);

    void set_race_id(const std::string& race_id);
    std::string get_race_id() const;

    void set_parent_race_id(const std::string& parent_race_id);
    std::string get_parent_race_id() const;

    void set_user_playable(const bool playable);
    bool get_user_playable() const;
    
    void set_settlement_type(const SettlementType new_settlement_type);
    SettlementType get_settlement_type() const;
    
    void set_settlement_tile_subtype(const TileType new_settlement_tile_subtype);
    TileType get_settlement_tile_subtype() const;

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

    void set_hungerless(const bool new_hungerless);
    bool get_hungerless() const;
    
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

    void set_statistics_modifier(const StatisticsModifier& new_statistics_modifier);
    StatisticsModifier get_statistics_modifier() const;

    void set_starting_speed(const Statistic& new_starting_speed);
    Statistic get_starting_speed() const;

    void set_corporeal(const BoolStatistic& new_corporeal);
    BoolStatistic get_corporeal() const;

    void set_flying(const BoolStatistic& new_flying);
    BoolStatistic get_flying() const;

    void set_experience_multiplier(const float new_experience_multiplier);
    float get_experience_multiplier() const;
    
    void set_initial_deity_ids(const std::vector<std::string>& new_initial_deity_ids);
    std::vector<std::string> get_initial_deity_ids() const;

    void set_resistances(const Resistances& new_resistances);
    Resistances get_resistances() const;

    void set_skills(const Skills& skills);
    Skills get_skills() const;

    void set_level_script(const std::string& new_level_script);
    std::string get_level_script() const;

    std::string str() const;

  protected:
    std::string race_id;
    std::string parent_race_id;
    bool user_playable;
    SettlementType settlement_type;
    TileType settlement_tile_subtype;

    // Name & vitals
    std::string race_name_sid;
    std::string race_short_description_sid;
    std::string race_description_sid;
    std::string race_abbreviation_sid;
    CreatureSize size;
    bool hungerless;
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
    StatisticsModifier statistics_modifier; 
    Statistic starting_speed; // starting speed is set by race.

    BoolStatistic corporeal; // Most races are corporeal; spirits aren't.

    BoolStatistic flying; // Birds can fly - the rest aren't so lucky.
    
    // Available deities on creation
    std::vector<std::string> initial_deity_ids;

    // Resistances
    Resistances resistances;

    // Skills
    Skills skills;

    // Level info
    float experience_multiplier;

    // Level script, used to populate Lua functions that run every time the
    // creature gains a level.
    std::string level_script;
};

typedef std::shared_ptr<Race> RacePtr;
typedef std::map<std::string, RacePtr> RaceMap;
