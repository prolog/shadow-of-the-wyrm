#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "AgeInfo.hpp"
#include "BoolStatistic.hpp"
#include "CreatureFeatures.hpp"
#include "DropParameters.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"
#include "CreatureFeatures.hpp"
#include "Resistances.hpp"
#include "SettlementTypes.hpp"
#include "Modifier.hpp"
#include "tiles.hpp"

// Race IDs referenced directly in the engine.
class RaceID
{
  public:
    static const std::string RACE_ID_UNKNOWN;

  protected:
    RaceID();
    ~RaceID();
};

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

    void set_user_playable(const bool new_playable);
    bool get_user_playable() const;

    void set_umbrella_race(const bool new_umbrella_race);
    bool get_umbrella_race() const;

    void set_sex(const CreatureSex sex);
    CreatureSex get_sex() const;

    void set_pack_multiplier(const int new_pack_multiplier);
    int get_pack_multiplier() const;

    void set_slayable(const bool slayable);
    bool get_slayable() const;

    void set_leaves_corpse(const bool new_leaves_corpse);
    bool get_leaves_corpse() const;

    void set_corpse_poisoned(const bool new_corpse_poisoned);
    bool get_corpse_poisoned() const;

    // Pacifiable via Music
    void set_pacifiable(const bool new_pacifiable);
    bool get_pacifiable() const;

    // Tameable via Beastmastery
    void set_tameable(const bool new_tameable);
    bool get_tameable() const;

    void set_splits(const bool new_splits);
    bool get_splits() const;

    void set_pct_flee(const int new_pct_flee);
    int get_pct_flee() const;

    void set_has_pockets(const bool new_has_pockets);
    bool get_has_pockets() const;

    void set_has_voice(const bool new_has_voice);
    bool get_has_voice() const;

    void set_has_hair(const bool new_has_hair);
    bool get_has_hair() const;

    void set_natural(const bool new_natural);
    bool get_natural() const;

    void set_can_kick(const bool new_can_kick);
    bool get_can_kick() const;

    void set_mindless(const bool new_mindless);
    bool get_mindless() const;

    void set_drops(const std::map<std::string, DropParameters>& new_drops);
    std::map<std::string, DropParameters> get_drops() const;

    void set_has_random_villages(const bool rand_villages);
    bool get_has_random_villages() const;
    
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

    void set_race_settlement_sid(const std::string& race_settle_sid);
    std::string get_race_settlement_sid() const;

    void set_size(const CreatureSize new_size);
    CreatureSize get_size() const;

    void set_hungerless(const bool new_hungerless);
    bool get_hungerless() const;
    
    void set_age_info(const AgeInfo& age);
    AgeInfo get_age_info() const;
    bool is_valid_starting_age(const int age) const;

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

    void set_modifier(const Modifier& new_modifier);
    Modifier get_modifier() const;

    void set_starting_speed(const Statistic& new_starting_speed);
    Statistic get_starting_speed() const;

    void set_corporeal(const BoolStatistic& new_corporeal);
    BoolStatistic get_corporeal() const;

    void set_undead(const BoolStatistic& new_undead);
    BoolStatistic get_undead() const;

    void set_flying(const BoolStatistic& new_flying);
    BoolStatistic get_flying() const;

    void set_water_breathing(const BoolStatistic& new_water_breathing);
    BoolStatistic get_water_breathing() const;

    void set_experience_multiplier(const float new_experience_multiplier);
    float get_experience_multiplier() const;

    void set_hp_regen_multiplier(const float new_hp_regen_multiplier);
    float get_hp_regen_multiplier() const;

    void set_ap_regen_multiplier(const float new_ap_regen_multiplier);
    float get_ap_regen_multiplier() const;

    void set_skill_points(const int new_skill_points);
    int get_skill_points() const;
    
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
    bool umbrella;
    CreatureSex sex;
    int pack_multiplier;
    bool slayable;
    bool leaves_corpse;
    bool corpse_poisoned;
    bool pacifiable;
    bool tameable;
    bool splits;
    int pct_flee;
    bool has_pockets;
    bool has_voice;
    bool has_hair;
    bool natural;
    bool can_kick;
    bool mindless;
    std::map<std::string, DropParameters> drops;
    bool has_random_villages;
    SettlementType settlement_type;
    TileType settlement_tile_subtype;

    // Name & vitals
    std::string race_name_sid;
    std::string race_short_description_sid;
    std::string race_description_sid;
    std::string race_abbreviation_sid;
    std::string race_settlement_sid;
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
    Modifier modifier; 
    Statistic starting_speed; // starting speed is set by race.

    BoolStatistic corporeal; // Most races are corporeal; spirits aren't.
    BoolStatistic undead; // Good and neutral gods don't think zombies are good eating
    BoolStatistic flying; // Birds can fly - the rest aren't so lucky.
    
    // Most races cannot breathe water.  The Elysians normally build air, but
    // have a permanent enchantment on them that allows them to also breathe
    // water.
    BoolStatistic water_breathing;
    
    // Available deities on creation
    std::vector<std::string> initial_deity_ids;

    // Resistances
    Resistances resistances;

    // Skills
    Skills skills;

    // Level info
    float experience_multiplier;

    // How much does the race affect HP/AP per tick?
    float hp_regen_multiplier;
    float ap_regen_multiplier;

    // How many skill points per level?
    int skill_points;

    // Level script, used to populate Lua functions that run every time the
    // creature gains a level.
    std::string level_script;
};

using RacePtr = std::unique_ptr<Race>;
using RaceMap = std::map<std::string, RacePtr>;
