#pragma once
#include <map>
#include <vector>
#include "ISerializable.hpp"
#include "Resistances.hpp"

// When adding new values to this class, be sure to update the constructor
// and get_raw_values() function!
class Modifier : public ISerializable
{
  public:
    Modifier();
    Modifier(const int new_strength_modifier, const int new_dexterity_modifier, const int new_agility_modifier, const int new_health_modifier, const int new_intelligence_modifier, const int new_willpower_modifier, const int new_charisma_modifier);
    Modifier(const std::vector<int>& args);
    bool operator==(const Modifier& m) const;

    void set_strength_modifier(const int new_strength_modifier);
    int get_strength_modifier() const;

    void set_dexterity_modifier(const int new_dexterity_modifier);
    int get_dexterity_modifier() const;

    void set_agility_modifier(const int new_agility_modifier);
    int get_agility_modifier() const;

    void set_health_modifier(const int new_health_modifier);
    int get_health_modifier() const;

    void set_intelligence_modifier(const int new_intelligence_modifier);
    int get_intelligence_modifier() const;

    void set_willpower_modifier(const int new_willpower_modifier);
    int get_willpower_modifier() const;

    void set_charisma_modifier(const int new_charisma_modifier);
    int get_charisma_modifier() const;

    void set_evade_modifier(const int new_evade_modifier);
    int get_evade_modifier() const;

    void set_soak_modifier(const int new_soak_modifier);
    int get_soak_modifier() const;

    void set_to_hit_modifier(const int new_to_hit_modifier);
    int get_to_hit_modifier() const;

    void set_resistances(const Resistances& new_resistances);
    Resistances get_resistances() const;

    // Is this, overall, a negative modifier?
    bool is_negative() const;

    void set_status(const std::string& status_id, const bool value, const int danger_level = 1);
    bool has_status(const std::string& status_id) const;
    std::pair<bool, int> get_status(const std::string& status_id) const;

    // returns all statuses whose value is true, along with their danger level
    std::vector<std::pair<std::string, int>> get_affected_statuses() const; 

    std::vector<int> get_raw_values() const;

    void set_delete(const bool new_delete);
    bool get_delete() const;

    void set_permanent(const bool new_permanent);
    bool get_permanent() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    bool is_statistics_part_negative() const;
    bool is_resistances_part_negative() const;

    int strength_modifier;
    int dexterity_modifier;
    int agility_modifier;
    int health_modifier;
    int intelligence_modifier;
    int willpower_modifier;
    int charisma_modifier;

    int evade_modifier;
    int soak_modifier;

    int to_hit_modifier;

    Resistances resistances;

    std::map<std::string, std::pair<bool, int>> statuses;

    bool mark_delete;
    bool permanent;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
