#pragma once
#include <string>

class DisplayStatistics
{
  public:
    DisplayStatistics(); // FIXME remove this later.

    static DisplayStatistics create(const std::string& name,
                                    const std::string& strength,
                                    const std::string& dexterity,
                                    const std::string& agility,
                                    const std::string& health,
                                    const std::string& intelligence,
                                    const std::string& willpower,
                                    const std::string& charisma
                                    );

    std::string get_name() const;
    std::string get_strength() const;
    std::string get_dexterity() const;
    std::string get_agility() const;
    std::string get_health() const;
    std::string get_intelligence() const;
    std::string get_willpower() const;
    std::string get_charisma() const;

  protected:
    void set_name(const std::string& new_name);
    void set_strength(const std::string& new_strength);
    void set_dexterity(const std::string& new_dexterity);
    void set_agility(const std::string& new_agility);
    void set_health(const std::string& new_health);
    void set_intelligence(const std::string& new_intelligence);
    void set_willpower(const std::string& new_willpower);
    void set_charisma(const std::string& new_charisma);

    std::string name;
    std::string strength;
    std::string dexterity;
    std::string agility;
    std::string health;
    std::string intelligence;
    std::string willpower;
    std::string charisma;
};
