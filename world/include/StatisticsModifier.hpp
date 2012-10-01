#pragma once

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class StatisticsModifier
{
  public:
    StatisticsModifier();
    StatisticsModifier(const int new_strength_modifier, const int new_dexterity_modifier, const int new_agility_modifier, const int new_health_modifier, const int new_intelligence_modifier, const int new_willpower_modifier, const int new_charisma_modifier, const int new_valour_modifier, const int new_spirit_modifier);

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

    void set_valour_modifier(const int new_valour_modifier);
    int get_valour_modifier() const;

    void set_spirit_modifier(const int new_spirit_modifier);
    int get_spirit_modifier() const;

  protected:
    int strength_modifier;
    int dexterity_modifier;
    int agility_modifier;
    int health_modifier;
    int intelligence_modifier;
    int willpower_modifier;
    int charisma_modifier;

    int valour_modifier;
    int spirit_modifier;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & strength_modifier & dexterity_modifier & agility_modifier & health_modifier;
      ar & intelligence_modifier & willpower_modifier & charisma_modifier;
      ar & valour_modifier & spirit_modifier;
    }
};
