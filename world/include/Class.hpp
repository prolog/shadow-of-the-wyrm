#pragma once
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include "common.hpp"
#include "InitialItem.hpp"
#include "Resistances.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"
#include "StatisticsModifier.hpp"

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
    
    void set_statistics_modifier(const StatisticsModifier& new_modifier);
    StatisticsModifier get_statistics_modifier() const;

    void set_resistances(const Resistances& resistances);
    Resistances get_resistances() const;
    
    void set_piety_cost_multiplier(const float new_piety_cost);
    float get_piety_cost_multiplier() const;
    
    void set_piety_regen_bonus(const int new_piety_regen_bonus);
    int get_piety_regen_bonus() const;

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
    
    // Initial equipment/inventory - this is used when generating a new character, and
    // is ignored thereafter.
    void set_initial_equipment(const std::map<EquipmentWornLocation, InitialItem>& new_initial_equipment);
    std::map<EquipmentWornLocation, InitialItem> get_initial_equipment() const;
    
    void set_initial_inventory(const std::vector<InitialItem>& new_initial_inventory);
    std::vector<InitialItem> get_initial_inventory() const;

    std::string str() const;

  protected:
    std::string class_id;

    std::string class_name_sid;
    std::string class_description_sid;
    std::string class_abbreviation_sid;

    Statistic starting_valour;
    Statistic starting_spirit;

    StatisticsModifier statistics_modifier;

    Resistances resistances;
    Skills skills;
    
    float piety_cost_multiplier;
    int piety_regen_bonus;

    bool user_playable;
    float experience_multiplier;
    
    // The dice to use each level for a creature's HP and AP
    uint hit_dice;
    uint ap_dice;
    
    // The initial equipment/inventory, used in character generation.
    std::map<EquipmentWornLocation, InitialItem> initial_equipment;
    std::vector<InitialItem> initial_inventory;
};

typedef boost::shared_ptr<Class> ClassPtr;
typedef std::map<std::string, ClassPtr> ClassMap;
