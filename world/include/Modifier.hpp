#pragma once
#include <vector>
#include "ISerializable.hpp"

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

    std::vector<int> get_raw_values() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    int strength_modifier;
    int dexterity_modifier;
    int agility_modifier;
    int health_modifier;
    int intelligence_modifier;
    int willpower_modifier;
    int charisma_modifier;

    int evade_modifier;
    int soak_modifier;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
