#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Colours.hpp"

class DisplayStatistics
{
  public:
    static DisplayStatistics create(const std::string& name,
                                    const std::string& synopsis,
                                    const std::string& strength,
                                    const std::string& dexterity,
                                    const std::string& agility,
                                    const std::string& health,
                                    const std::string& intelligence,
                                    const std::string& willpower,
                                    const std::string& charisma,
                                    const std::string& valour,
                                    const std::string& spirit,
                                    const std::string& speed,
                                    const std::string& level,
                                    const std::string& defence,
                                    const std::string& hit_points,
                                    const std::string& arcana_points,
                                    const std::string& map_depth,
                                    const std::vector<std::pair<std::string, Colour>>& status_ailments
                                    );

    std::string get_name() const;
    std::string get_synopsis() const;

    std::string get_strength() const;
    std::string get_dexterity() const;
    std::string get_agility() const;
    std::string get_health() const;
    std::string get_intelligence() const;
    std::string get_willpower() const;
    std::string get_charisma() const;

    std::string get_valour() const;
    std::string get_spirit() const;
    std::string get_speed() const;

    std::string get_level() const;
    std::string get_defence() const;

    std::string get_hit_points() const;
    std::string get_arcana_points() const;

    std::string get_map_depth() const;

    std::vector<std::pair<std::string, Colour>> get_status_ailments() const;

  protected:
    friend class CreatureTranslator;
    DisplayStatistics();

    void set_name(const std::string& new_name);
    void set_synopsis(const std::string& new_synopsis);

    void set_strength(const std::string& new_strength);
    void set_dexterity(const std::string& new_dexterity);
    void set_agility(const std::string& new_agility);
    void set_health(const std::string& new_health);
    void set_intelligence(const std::string& new_intelligence);
    void set_willpower(const std::string& new_willpower);
    void set_charisma(const std::string& new_charisma);

    void set_valour(const std::string& new_valour);
    void set_spirit(const std::string& new_spirit);
    void set_speed(const std::string& new_speed);

    void set_level(const std::string& new_level);
    void set_defence(const std::string& new_defense);

    void set_hit_points(const std::string& new_hit_points);
    void set_arcana_points(const std::string& new_arcana_points);

    void set_map_depth(const std::string& new_map_depth);

    void set_status_ailments(const std::vector<std::pair<std::string, Colour>>& new_status_ailments);

    std::string name;
    std::string synopsis;

    std::string strength;
    std::string dexterity;
    std::string agility;
    std::string health;
    std::string intelligence;
    std::string willpower;
    std::string charisma;

    std::string valour;
    std::string spirit;
    std::string speed;

    std::string level;
    std::string defence; // Combination of evade and soak statistics

    std::string hit_points;
    std::string arcana_points;

    std::string map_depth;

    std::vector<std::pair<std::string, Colour>> status_ailments;
};
