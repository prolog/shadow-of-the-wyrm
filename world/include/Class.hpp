#pragma once
#include <memory>
#include <map>
#include <string>
#include "common.hpp"
#include "EquipmentTypes.hpp"
#include "InitialItem.hpp"
#include "Resistances.hpp"
#include "Skills.hpp"
#include "Statistic.hpp"
#include "Modifier.hpp"
#include "Symbol.hpp"

class Class
{
  public:
    Class();
    virtual ~Class();

    Class(const Class& cl);
    Class& operator=(const Class& cl);
    bool operator==(const Class& cl) const;

    void set_class_id(const std::string& id);
    std::string get_class_id() const;

    void set_class_name_sid(const std::string& new_class_name_sid);
    std::string get_class_name_sid() const;

    void set_class_short_description_sid(const std::string& new_class_short_description_sid);
    std::string get_class_short_description_sid() const;

    void set_class_description_sid(const std::string& new_class_description_sid);
    std::string get_class_description_sid() const;

    void set_class_abbreviation_sid(const std::string& new_class_abbreviation_sid);
    std::string get_class_abbreviation_sid() const;

    // Basic display info
    void set_symbol(const Symbol& new_symbol);
    Symbol* get_symbol();

    void set_modifier(const Modifier& new_modifier);
    Modifier get_modifier() const;

    void set_resistances(const Resistances& resistances);
    Resistances get_resistances() const;
    
    void set_crowning_gifts(const std::vector<std::string>& new_crowning_gifts);
    std::vector<std::string> get_crowning_gifts() const;

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

    void set_hp_regen_multiplier(const float new_hp_regen_multiplier);
    float get_hp_regen_multiplier() const;

    void set_ap_regen_multiplier(const float new_ap_regen_multiplier);
    float get_ap_regen_multiplier() const;

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

    void set_level_script(const std::string& new_level_script);
    std::string get_level_script() const;

    void set_kill_script(const std::string& new_kill_script);
    std::string get_kill_script() const;

    void set_titles(const std::map<int, std::string>& new_titles);
    std::map<int, std::string> get_titles() const;

    void set_deity_dislike_multipliers(const std::map<std::string, float>& new_deity_dislike_multipliers);
    std::map<std::string, float> get_deity_dislike_multipliers() const;

    void set_starting_pet_ids(const std::vector<std::string>& new_starting_pet_ids);
    std::vector<std::string> get_starting_pet_ids() const;

    std::string str() const;

  protected:
    std::string class_id;

    std::string class_name_sid;
    std::string class_short_description_sid;
    std::string class_description_sid;
    std::string class_abbreviation_sid;

    std::unique_ptr<Symbol> symbol;
    Modifier modifier;
    Resistances resistances;
    Skills skills;
    std::vector<std::string> crowning_gifts;

    float piety_cost_multiplier;
    int piety_regen_bonus;

    bool user_playable;
    float experience_multiplier;

    // How much does the class affect HP/AP regen per tick?
    float hp_regen_multiplier;
    float ap_regen_multiplier;
    
    // The dice to use each level for a creature's HP and AP
    uint hit_dice;
    uint ap_dice;
    
    // The initial equipment/inventory, used in character generation.
    std::map<EquipmentWornLocation, InitialItem> initial_equipment;
    std::vector<InitialItem> initial_inventory;

    // The script to run when levelling.  Allows user-defined classes
    // to be somewhat interesting, rather than just a collection of
    // stats.
    std::string level_script;

    // Ditto for when a creature is killed.  Do certain things happen
    // when they kill creatures?  Is more experience granted in certain
    // cases?
    std::string kill_script;

    // A map of levels to titles.
    std::map<int, std::string> titles;

    // Deity dislike multipliers.  If a value exists for a given
    // key (action name), then the multiplier is used; otherwise
    // the default multiplier of 1 is used.
    std::map<std::string, float> deity_dislike_multipliers;

    // Some classes can start with pets.  An ID is selected
    // at random from the starting list.
    std::vector<std::string> starting_pet_ids;

  private:
    void swap(Class& cl) throw ();

};

using ClassPtr = std::unique_ptr<Class>;
using ClassMap = std::map<std::string, ClassPtr>;
using InitialEquipmentMap = std::map<EquipmentWornLocation, InitialItem>;
