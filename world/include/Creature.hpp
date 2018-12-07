#pragma once
#include <string>
#include <memory>
#include "Alignment.hpp"
#include "AutomaticMovement.hpp"
#include "Blood.hpp"
#include "BoolStatistic.hpp"
#include "common.hpp"
#include "Colours.hpp"
#include "Conducts.hpp"
#include "Controller.hpp"
#include "CreatureFeatures.hpp"
#include "Damage.hpp"
#include "DecisionStrategy.hpp"
#include "Equipment.hpp"
#include "HungerClock.hpp"
#include "Inventory.hpp"
#include "ISerializable.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "ISerializable.hpp"
#include "Memberships.hpp"
#include "Mortuary.hpp"
#include "MovementAccumulation.hpp"
#include "Religion.hpp"
#include "Resistances.hpp"
#include "ScriptDetails.hpp"
#include "Skills.hpp"
#include "SpellKnowledge.hpp"
#include "Statistic.hpp"
#include "StatisticTypes.hpp"
#include "Status.hpp"
#include "StatusTypes.hpp"

// Forward declarations.
class DecisionStrategy;

using TargetMap = std::map<std::string, std::pair<std::string, Coordinate>>;
using CreatureStatusMap = std::map<std::string, Status>;

class Creature : public ISerializable
{
  public:
    Creature();
    Creature(const Creature& cr);
    Creature& operator=(const Creature& cr);
    bool operator==(const Creature& cr) const;

    // A unique identifier for every creature.
    void set_id(const std::string& new_id);
    std::string get_id() const;

    // A categorical identifier - all creatures of a certain "type" will
    // have the same value, and this aids in tracking kills, etc.
    void set_original_id(const std::string& new_original_id);
    std::string get_original_id() const;

    void set_is_player(const bool player, ControllerPtr decision_strategy_controller);
    bool get_is_player() const;
    bool is(std::shared_ptr<Creature> creature) const;

    // Set/Get basic vitals
    void set_name(const std::string& new_name);
    std::string get_name() const;
    bool has_name() const;
    
    // Used for display information and messages, particularly when no name
    // is present.
    void set_short_description_sid(const std::string& new_short_description_sid);
    std::string get_short_description_sid() const;
    
    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;

    void set_text_details_sid(const std::string& new_text_details_sid);
    std::string get_text_details_sid() const;

    void set_sex(const CreatureSex new_sex);
    CreatureSex get_sex() const;

    void set_age(const Statistic& new_age);
    Statistic get_age() const;

    void set_size(const CreatureSize& new_size);
    CreatureSize get_size() const;
    
    void set_eye_colour(const EyeColour new_eye_colour);
    EyeColour get_eye_colour() const;
    
    void set_hair_colour(const HairColour new_hair_colour);
    HairColour get_hair_colour() const;
    
    void set_handedness(const Handedness new_handedness);
    Handedness get_handedness() const;
    Handedness get_off_handedness() const;
    
    void set_breathes(const BreatheType new_breathes);
    BreatheType get_base_breathes() const;

    // Get everything that the creature can currently breathe - include water 
    // if the creature has the water breathing status.
    std::vector<BreatheType> get_breathes() const; 
    bool can_breathe(const BreatheType btype) const;

    void set_blood(const Blood& new_blood);
    Blood get_blood() const;
    Blood& get_blood_ref();

    void decrement_grams_unabsorbed_alcohol(const float delta_grams_unabsorbed_alcohol);
    void increment_grams_unabsorbed_alcohol(const float additional_grams_unabsorbed_alcohol);
    void set_grams_unabsorbed_alcohol(const float new_grams_unabsorbed_alcohol);
    float get_grams_unabsorbed_alcohol() const;

    void set_alignment(const Alignment& new_alignment);
    Alignment get_alignment() const;
    Alignment& get_alignment_ref();

    // Set/Get race and class identifiers
    void set_race_id(const std::string& new_race_id);
    std::string get_race_id() const;

    void set_class_id(const std::string& new_class_id);
    std::string get_class_id() const;

    // Set/Get physical stats.
    Statistic& get_statistic_ref(const PrimaryStatisticType pr_stat);

    void set_strength(const Statistic& new_strength);
    Statistic get_strength() const;
    Statistic& get_strength_ref();

    void set_dexterity(const Statistic& new_dexterity);
    Statistic get_dexterity() const;
    Statistic& get_dexterity_ref();

    void set_agility(const Statistic& new_agility);
    Statistic get_agility() const;
    Statistic& get_agility_ref();

    void set_health(const Statistic& new_health);
    Statistic get_health() const;
    Statistic& get_health_ref();

    void set_intelligence(const Statistic& new_intelligence);
    Statistic get_intelligence() const;
    Statistic& get_intelligence_ref();

    void set_willpower(const Statistic& new_willpower);
    Statistic get_willpower() const;
    Statistic& get_willpower_ref();

    void set_charisma(const Statistic& new_charisma);
    Statistic get_charisma() const;
    Statistic& get_charisma_ref();


    // Set/get secondary statistics
    void set_speed(const Statistic& new_speed);
    Statistic get_speed() const;

    void set_resistance_value(const DamageType type, double value);
    void set_resistances(const Resistances& resistances);
    Resistances& get_resistances();

    void set_intrinsic_resistances(const Resistances& new_intrinsic_resistances);
    Resistances& get_intrinsic_resistances_ref();
    Resistances get_intrinsic_resistances() const;

    void set_skills(const Skills& new_skills);
    Skills& get_skills();
    
    void set_movement_accumulation(const MovementAccumulation& new_accumulation);
    MovementAccumulation& get_movement_accumulation_ref();
    
    void set_base_damage(const Damage& new_base_damage);
    Damage get_base_damage() const;
    
    Equipment& get_equipment();
    int get_hands_available() const;
    IInventoryPtr get_inventory();
    
    // Get the weight carried, in oz
    uint get_weight_carried() const;

    // Does the creature have any equipped or worn items?  Are any unpaid?
    bool has_items() const;
    bool has_unpaid_items() const;
    uint count_items() const;
    uint get_unpaid_amount() const;
    void set_items_paid();
    void restack_items();
    
    // Set/get point-based statistics

    void set_hit_points(const Statistic& new_hit_points);
    int increment_hit_points(int amount);
    int decrement_hit_points(int amount);
    Statistic get_hit_points() const;
    Statistic& get_hit_points_ref();
    bool is_hp_full() const;
    bool is_ap_full() const;
    bool is_dead() const;

    void set_arcana_points(const Statistic& new_arcana_points);
    int increment_arcana_points(int amount);
    int decrement_arcana_points(int amount);
    Statistic get_arcana_points() const;
    Statistic& get_arcana_points_ref();

    // Set/get protective statistics.  The "base_evade" and "base_soak" are
    // stored (not calculated) values that exist regardless of any armour worn.
    void set_base_evade(const Statistic& new_base_evade);
    Statistic get_base_evade() const;
    
    void set_base_soak(const Statistic& new_base_soak);
    Statistic get_base_soak() const;

    void set_evade(const Statistic& new_evade);
    Statistic get_evade() const;

    void set_soak(const Statistic& new_soak);
    Statistic get_soak() const;

    // Set/get attacking statistics.
    void set_to_hit(const Statistic& new_to_hit);
    Statistic get_to_hit() const;

    void set_addl_damage(const Statistic& new_addl_damage);
    Statistic get_addl_damage() const;

    // Basic display info
    void set_symbol(const uchar new_symbol);
    uchar get_symbol() const;

    void set_colour(const Colour new_colour);
    Colour get_colour() const;

    // Level info
    void set_level(const Statistic& level);
    Statistic get_level() const;

    // Strategy info
    void set_decision_strategy(const std::shared_ptr<DecisionStrategy> strategy);
    std::shared_ptr<DecisionStrategy> get_decision_strategy() const;
    
    // Is the creature hostile towards a given creature's ID?
    bool hostile_to(const std::string& creature_id);
    
    // Religion info
    void set_religion(const Religion& new_religion);
    Religion get_religion() const;
    Religion& get_religion_ref();
    DeityStatus& get_active_deity_status_ref();
    
    // Experience value when killed
    void set_experience_value(const uint new_experience_value);
    uint get_experience_value() const;
    
    // Creature's current experience
    void set_experience_points(const uint new_experience_points);
    uint get_experience_points() const;

    // Current number of skill points
    void set_skill_points(const int new_skill_points);
    void increment_skill_points(const int incr_amount);
    int get_skill_points() const;
        
    // The number of turns a creature has taken.
    void increment_turns();
    ulonglong get_turns() const;
    
    void set_target_map(const TargetMap& new_previous_target);
    TargetMap get_target_map() const;
    TargetMap& get_target_map_ref();
    
    void set_hunger_clock(const HungerClock& new_hunger_clock);
    HungerClock get_hunger_clock() const;
    HungerClock& get_hunger_clock_ref();

    // Set/check if the creature poisoned, etc
    void set_status(const std::string& status_id, const Status& status);
    void remove_status(const std::string& status_id);
    bool has_status(const std::string& status_id) const;
    bool has_status() const;
    Status get_status(const std::string& status_id) const;
    void set_statuses(const CreatureStatusMap& new_statuses);
    CreatureStatusMap get_statuses() const;
    CreatureStatusMap& get_statuses_ref();

    void clear_event_scripts();
    void set_event_scripts(const EventScriptsMap& esm);
    EventScriptsMap get_event_scripts() const;
    EventScriptsMap& get_event_scripts_ref();
    void add_event_script(const std::string& event_name, const ScriptDetails& sd);
    bool has_event_script(const std::string& event_name);
    ScriptDetails get_event_script(const std::string& event_name) const;

    // The generic "chat" text a creature uses.  Not all creatures will have chat
    // text.
    void set_speech_text_sid(const std::string& speech_text_sid);
    std::string get_speech_text_sid() const;

    // A creature's auto-move details.
    void set_automatic_movement(const AutomaticMovement& new_auto);
    AutomaticMovement& get_automatic_movement_ref();

    void set_modifiers(const std::map<double, std::vector<std::pair<std::string, Modifier>>>& new_modifiers);
    std::map<double, std::vector<std::pair<std::string, Modifier>>> get_active_modifiers() const; // get all modifiers not marked for deletion
    std::map<double, std::vector<std::pair<std::string, Modifier>>> get_modifiers() const; // get all modifiers, including those marked for deletion
    std::map<double, std::vector<std::pair<std::string, Modifier>>>& get_modifiers_ref(); // get all modifiers, including those marked for deletion
    bool is_affected_by_modifier_spell(const std::string& spell_id) const;

    void set_memberships(const Memberships& new_memberships);
    Memberships get_memberships() const;
    Memberships& get_memberships_ref();

    // Which win conditions have been satisfied?
    std::vector<CreatureWin> get_satisfied_win_conditions() const;

    // Additional traits not all creatures will have, so a bit of space is saved
    // by using a map.
    bool has_additional_property(const std::string& property_name) const;
    void set_additional_property(const std::string& property_name, const std::string& property_value);
    void remove_additional_property(const std::string& property_name);
    std::string get_additional_property(const std::string& property_name) const;
    void set_additional_properties_map(const std::map<std::string, std::string>& additional_properties_map);
    std::map<std::string, std::string> get_additional_properties_map() const;

    Mortuary& get_mortuary_ref();

    Conducts& get_conducts_ref();

    void set_spell_knowledge(const SpellKnowledge& new_spell_knowledge);
    SpellKnowledge& get_spell_knowledge_ref();
    SpellKnowledge get_spell_knowledge() const;

    void set_free_hidden_actions(const int new_actions);
    int get_free_hidden_actions() const;
    int increment_free_hidden_actions();
    int decrement_free_hidden_actions();

    bool has_creature_in_view(const std::string& creature_id) const;

    static bool is_ancient_beast(const std::string& id);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  private:
    void assert_size() const;
    void swap(Creature& c) throw ();

    ClassIdentifier internal_class_identifier() const override;

  protected:

    std::string id;
    std::string original_id;

    bool is_player;

    // Basic vitals
    std::string name;
    CreatureSex sex;
    Statistic age;
    CreatureSize size;
    EyeColour eye_colour;
    HairColour hair_colour;
    Handedness handedness;
    BreatheType breathes;
    Blood blood;
    float grams_unabsorbed_alcohol;
    Alignment alignment;

    std::string short_description_sid;
    std::string description_sid;
    std::string text_details_sid;

    // Race and class.  Maybe make this an ID instead?
    std::string race_id;
    std::string class_id;

    // Physical Statistics
    Statistic strength;
    Statistic dexterity;
    Statistic agility;
    Statistic health;
    Statistic intelligence;
    Statistic willpower;
    Statistic charisma;

    // Secondary statistics
    Statistic speed;

    // The creature's base damage.  Defaults to 1d2 of DAMAGE_TYPE_POUND.
    Damage damage;
    
    // The creature's worn items.
    Equipment equipment;
    
    // The creature's inventory.
    IInventoryPtr inventory;
    
    // Resistances/vulns.  These act as a damage multiplier.  A value of 1.0 indicates no resistance or vulnerability.
    // 0.50 indicates half damage, 2.0 indicates double damage.
    Resistances resistances;

    // Intrinsic resistances.  These are used internally in calculating a
    // creature's actual resistances, forming a component (along with race,
    // class, and equipment) of a creature's overall resistances.  Intrinsic
    // resistances are typically gained by eating monster corpses.
    Resistances intrinsic_resistances;

    // The creature's various skills.
    Skills skills;
    
    // Movement accumulation information.
    MovementAccumulation movement_accumulation;

    // Point-based statistics
    Statistic hit_points;
    Statistic arcana_points;

    // Used for evading attacks (protective statistics)
    Statistic base_evade;
    Statistic base_soak;
    Statistic evade;
    Statistic soak;

    // Used for hitting and damaging (base should be 0, with bonuses provided
    // by eqiupment).
    Statistic to_hit;
    Statistic addl_damage;

    // Various flags

    // Basic creature info used for the display
    uchar symbol;
    Colour colour;

    // Level information
    Statistic level;

    // Decision making strategy
    std::shared_ptr<DecisionStrategy> decision_strategy;
    
    // Religious data
    Religion religion;
    
    // Experience gained by attacker when this creature is killed.
    uint experience_value;
    
    // The creature's overall experience
    uint experience_points;

    // The current number of skill points.
    int skill_points;
    
    // The number of actions the creature has taken.
    ulonglong turns;
    
    // Previous targets for ranged/magical combat.  The value is structured
    // so that:
    // - string is a creature ID, possible empty
    // - Coordinate is the coordinate that the creature was previously at
    TargetMap targets;

    // The creature's hunger details
    HungerClock hunger;

    // Whether the creature is poisoned, silenced, etc.
    CreatureStatusMap statuses;

    // Event scripts - used to look up engine or user-defined Lua scripts
    // that should run when the event occurs.
    EventScriptsMap event_scripts;

    // Automatic movement details.
    AutomaticMovement auto_move;

    // Additional properties - properties a creature can have that are
    // not common to all creatures (speech, etc).
    std::map<std::string, std::string> additional_properties;

    // The creature's kills.
    Mortuary mortuary;

    // The creature's conducts: foodless, agnostic, etc
    Conducts conducts;

    // The creature's magical knowledge.
    SpellKnowledge spell_knowledge;

    // The list of statistics modifiers currently in place (e.g., as a result of spells)
    std::map<double, std::vector<std::pair<std::string, Modifier>>> modifiers;

    // Any guilds, trade organizations, etc., that the creature belongs to.
    Memberships memberships;
};

using CreaturePtr = std::shared_ptr<Creature>;
using CreatureMap = std::map<std::string, CreaturePtr>;
