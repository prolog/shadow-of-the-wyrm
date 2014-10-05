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
                                    const std::pair<std::string, Colour>& strength,
                                    const std::pair<std::string, Colour>& dexterity,
                                    const std::pair<std::string, Colour>& agility,
                                    const std::pair<std::string, Colour>& health,
                                    const std::pair<std::string, Colour>& intelligence,
                                    const std::pair<std::string, Colour>& willpower,
                                    const std::pair<std::string, Colour>& charisma,
                                    const std::string& speed,
                                    const std::string& level,
                                    const std::string& defence,
                                    const std::pair<std::string, Colour>& alignment,
                                    const std::string& hit_points,
                                    const std::string& arcana_points,
                                    const std::string& map_depth,
                                    const std::vector<std::pair<std::string, Colour>>& status_ailments
                                    );

    std::string get_name() const;
    std::string get_synopsis() const;

    std::pair<std::string, Colour> get_strength() const;
    std::pair<std::string, Colour> get_dexterity() const;
    std::pair<std::string, Colour> get_agility() const;
    std::pair<std::string, Colour> get_health() const;
    std::pair<std::string, Colour> get_intelligence() const;
    std::pair<std::string, Colour> get_willpower() const;
    std::pair<std::string, Colour> get_charisma() const;

    std::string get_speed() const;
    std::string get_level() const;
    std::string get_defence() const;

    std::pair<std::string, Colour> get_alignment() const;

    std::string get_hit_points() const;
    std::string get_arcana_points() const;

    std::string get_map_depth() const;

    std::vector<std::pair<std::string, Colour>> get_status_ailments() const;

  protected:
    friend class CreatureTranslator;
    DisplayStatistics();

    void set_name(const std::string& new_name);
    void set_synopsis(const std::string& new_synopsis);

    void set_strength(const std::pair<std::string, Colour>& new_strength);
    void set_dexterity(const std::pair<std::string, Colour>& new_dexterity);
    void set_agility(const std::pair<std::string, Colour>& new_agility);
    void set_health(const std::pair<std::string, Colour>& new_health);
    void set_intelligence(const std::pair<std::string, Colour>& new_intelligence);
    void set_willpower(const std::pair<std::string, Colour>& new_willpower);
    void set_charisma(const std::pair<std::string, Colour>& new_charisma);

    void set_speed(const std::string& new_speed);
    void set_level(const std::string& new_level);
    void set_defence(const std::string& new_defense);

    void set_alignment(const std::pair<std::string, Colour>& new_alignment);

    void set_hit_points(const std::string& new_hit_points);
    void set_arcana_points(const std::string& new_arcana_points);

    void set_map_depth(const std::string& new_map_depth);

    void set_status_ailments(const std::vector<std::pair<std::string, Colour>>& new_status_ailments);

    std::string name;
    std::string synopsis;

    std::pair<std::string, Colour> strength;
    std::pair<std::string, Colour> dexterity;
    std::pair<std::string, Colour> agility;
    std::pair<std::string, Colour> health;
    std::pair<std::string, Colour> intelligence;
    std::pair<std::string, Colour> willpower;
    std::pair<std::string, Colour> charisma;

    std::string speed;
    std::string level;
    std::string defence; // Combination of evade and soak statistics

    std::pair<std::string, Colour> alignment;

    std::string hit_points;
    std::string arcana_points;

    std::string map_depth;

    std::vector<std::pair<std::string, Colour>> status_ailments;
};
