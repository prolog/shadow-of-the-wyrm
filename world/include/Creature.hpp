#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Colours.hpp"
#include "CreatureFeatures.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "Resistances.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"

class Creature
{
  public:
    Creature();

    // Quick hack.  Later on, this'll be some sort of Strategy, where the Player strategy sends commands
    // via keyboard/mouse/etc input.
    void set_is_player(const bool player);
    bool get_is_player() const;

    // Set/Get basic vitals
    void set_name(const std::string& new_name);
    std::string get_name() const;

    void set_age(const Statistic& new_age);
    Statistic get_age() const;

    void set_size(const CreatureSize& new_size);
    CreatureSize get_size() const;


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

    void set_piety(const Statistic& new_piety);
    Statistic get_piety() const;

    void set_speed(const Statistic& new_speed);
    Statistic get_speed() const;

    void set_resistance_value(const ResistanceType type, double value);
    void set_resistances(const Resistances& resistances);
    Resistances& get_resistances();

    void set_skills(const Skills& new_skills);
    Skills& get_skills();

    // Set/get point-based statistics

    void set_hit_points(const Statistic& new_hit_points);
    void increment_hit_points(int amount);
    void decrement_hit_points(int amount);
    Statistic get_hit_points() const;

    void set_arcana_points(const Statistic& new_arcana_points);
    void increment_arcana_points(int amount);
    void decrement_arcana_points(int amount);
    Statistic get_arcana_points() const;


    // Set/get protective statistics

    void set_evade(const Statistic& new_evade);
    Statistic get_evade() const;

    void set_soak(const Statistic& new_soak);
    Statistic get_soak() const;

    // Basic display info
    void set_symbol(const uchar new_symbol);
    uchar get_symbol() const;

    void set_colour(const Colour new_colour);
    Colour get_colour() const;

  protected:
    bool is_player;

    // Basic vitals
    std::string name;
    Statistic age;
    CreatureSize size;

    // Race and class.  Maybe make this an ID instead?
    RacePtr race;
    ClassPtr character_class;

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

    // Not shown directly to the user - this is a hidden statistic that ranks the creature's standing with
    // his or her deity.
    Statistic piety;

    // Resistances/vulns.  These act as a damage multiplier.  A value of 1.0 indicates no resistance or vulnerability.
    // 0.50 indicates half damage, 2.0 indicates double damage.
    Resistances resistances;

    // The creature's various skills.
    Skills skills;

    // Point-based statistics
    Statistic hit_points;
    Statistic arcana_points;

    // Used for evading attacks (protective statistics)
    Statistic evade;
    Statistic soak;

    // Basic creature info used for the display
    uchar symbol;
    Colour colour;
};

typedef boost::shared_ptr<Creature> CreaturePtr;
