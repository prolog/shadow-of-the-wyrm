#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Colours.hpp"
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
#include "MovementAccumulation.hpp"
#include "Religion.hpp"
#include "Resistances.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"

// Forward declarations.
class DecisionStrategy;

typedef std::map<std::string, std::pair<std::string, Coordinate> > TargetMap;
typedef std::map<std::string, std::string> EventFunctionMap;

class Creature : public ISerializable
{
  public:
    Creature();
    Creature(const Creature& cr);
    Creature& operator=(const Creature& cr);
    bool operator==(const Creature& cr);

    void set_id(const std::string& new_id);
    std::string get_id() const;

    // Quick hack.  Later on, this'll be some sort of Strategy, where the Player strategy sends commands
    // via keyboard/mouse/etc input.
    // JCD FIXME: Rename this later.
    void set_is_player(const bool player, ControllerPtr decision_strategy_controller);
    bool get_is_player() const;

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
    
    // Set/Get race and class identifiers
    void set_race_id(const std::string& new_race_id);
    std::string get_race_id() const;

    void set_class_id(const std::string& new_class_id);
    std::string get_class_id() const;

    // Set/Get physical stats.
    // JCD FIXME: THESE WILL NEED TO BE UPDATED TO RETURN REFERENCES SO WE CAN UPDATE
    // EITHER THE BASE OR THE CURRENT VALUE.

    void set_strength(const Statistic& new_strength);
    Statistic get_strength() const;

    void set_dexterity(const Statistic& new_dexterity);
    Statistic get_dexterity() const;

    void set_agility(const Statistic& new_agility);
    Statistic get_agility() const;

    void set_health(const Statistic& new_health);
    Statistic get_health() const;

    void set_intelligence(const Statistic& new_intelligence);
    Statistic get_intelligence() const;

    void set_willpower(const Statistic& new_willpower);
    Statistic get_willpower() const;

    void set_charisma(const Statistic& new_charisma);
    Statistic get_charisma() const;


    // Set/get secondary statistics

    void set_valour(const Statistic& new_valour);
    Statistic get_valour() const;

    void set_spirit(const Statistic& new_spirit);
    Statistic get_spirit() const;

    void set_speed(const Statistic& new_speed);
    Statistic get_speed() const;

    void set_resistance_value(const DamageType type, double value);
    void set_resistances(const Resistances& resistances);
    Resistances& get_resistances();

    void set_skills(const Skills& new_skills);
    Skills& get_skills();
    
    void set_movement_accumulation(const MovementAccumulation& new_accumulation);
    MovementAccumulation& get_movement_accumulation_ref();
    
    void set_base_damage(const Damage& new_base_damage);
    Damage get_base_damage() const;
    
    Equipment& get_equipment();
    Inventory& get_inventory();
    
    // Set/get point-based statistics

    void set_hit_points(const Statistic& new_hit_points);
    int increment_hit_points(int amount);
    int decrement_hit_points(int amount);
    Statistic get_hit_points() const;
    bool is_hp_full() const;
    bool is_ap_full() const;

    void set_arcana_points(const Statistic& new_arcana_points);
    void increment_arcana_points(int amount);
    void decrement_arcana_points(int amount);
    Statistic get_arcana_points() const;


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

    // Basic display info
    void set_symbol(const uchar new_symbol);
    uchar get_symbol() const;

    void set_colour(const Colour new_colour);
    Colour get_colour() const;

    // Level info
    void set_level(const Statistic& level);
    Statistic get_level() const;

    // Strategy info
    void set_decision_strategy(const boost::shared_ptr<DecisionStrategy> strategy);
    boost::shared_ptr<DecisionStrategy> get_decision_strategy() const;
    
    // Is the creature hostile towards a given creature's ID?
    bool hostile_to(const std::string& creature_id);
    
    // Religion info
    void set_religion(const Religion& new_religion);
    Religion get_religion() const;
    Religion& get_religion_ref();
    
    // Experience value when killed
    void set_experience_value(const uint new_experience_value);
    uint get_experience_value() const;
    
    // Creature's current experience
    void set_experience_points(const uint new_experience_points);
    uint get_experience_points() const;
    
    // The number of turns a creature has taken.
    void increment_turns();
    ulonglong get_turns() const;
    
    void set_target_map(const TargetMap& new_previous_target);
    TargetMap get_target_map() const;
    TargetMap& get_target_map_ref();
    
    void set_hunger_clock(const HungerClock& new_hunger_clock);
    HungerClock get_hunger_clock() const;
    HungerClock& get_hunger_clock_ref();

    void clear_event_functions();
    void add_event_function(const std::string& event_name, const std::string& function_name);
    bool has_event_function(const std::string& event_name);
    std::string get_event_function(const std::string& event_name) const;

    // The generic "chat" text a creature uses.  Not all creatures will have chat
    // text.
    void set_speech_text_sid(const std::string& speech_text_sid);
    std::string get_speech_text_sid() const;

    // Additional traits not all creatures will have, so a bit of space is saved
    // by using a map.
    bool has_additional_property(const std::string& property_name) const;
    void set_additional_property(const std::string& property_name, const std::string& property_value);
    std::string get_additional_property(const std::string& property_name) const;
    void set_additional_properties_map(const std::map<std::string, std::string>& additional_properties_map);
    std::map<std::string, std::string> get_additional_properties_map() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  private:
    void assert_size() const;
    void swap(Creature& c) throw ();

    ClassIdentifier internal_class_identifier() const;

  protected:

    std::string id;

    bool is_player;

    // Basic vitals
    std::string name;
    CreatureSex sex;
    Statistic age;
    CreatureSize size;
    EyeColour eye_colour;
    HairColour hair_colour;
    Handedness handedness;
    
    std::string short_description_sid;
    std::string description_sid;

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
    Statistic valour;
    Statistic spirit;
    Statistic speed;

    // The creature's base damage.  Defaults to 1d2 of DAMAGE_TYPE_POUND.
    Damage damage;
    
    // The creature's worn items.
    Equipment equipment;
    
    // The creature's inventory.
    Inventory inventory;
    
    // Resistances/vulns.  These act as a damage multiplier.  A value of 1.0 indicates no resistance or vulnerability.
    // 0.50 indicates half damage, 2.0 indicates double damage.
    Resistances resistances;

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

    // Basic creature info used for the display
    uchar symbol;
    Colour colour;

    // Level information
    Statistic level;

    // Decision making strategy
    boost::shared_ptr<DecisionStrategy> decision_strategy;
    
    // Religious data
    Religion religion;
    
    // Experience gained by attacker when this creature is killed.
    uint experience_value;
    
    // The creature's overall experience
    uint experience_points;
    
    // The number of actions the creature has taken.
    ulonglong turns;
    
    // Previous targets for ranged/magical combat.  The value is structured
    // so that:
    // - string is a creature ID, possible empty
    // - Coordinate is the coordinate that the creature was previously at
    TargetMap targets;

    // The creature's hunger details
    HungerClock hunger;

    // Event functions - used to look up engine or user-defined functions
    // when the event occurs.
    EventFunctionMap event_functions;

    // Additional properties - properties a creature can have that are
    // not common to all creatures (speech, etc).
    std::map<std::string, std::string> additional_properties;
};

typedef boost::shared_ptr<Creature> CreaturePtr;
typedef std::map<std::string, CreaturePtr> CreatureMap;
