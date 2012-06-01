#pragma once
#include <map>
#include <set>
#include <string>
#include "common.hpp"
#include "Dice.hpp"
#include "RarityTypes.hpp"
#include "tiles.hpp"

// Values that are used to generate a creature, without being a necessary
// part of the creature itself.  Prevents values that only need a single
// instance from being duplicated on every creature.
class CreatureGenerationValues
{
  public:
    CreatureGenerationValues();
    ~CreatureGenerationValues();

    void add_allowable_terrain_type(const TileType additional_terrain_type);
    void clear_allowable_terrain_types();
    void set_allowable_terrain_types(const std::set<TileType>& new_allowable_terrain_types);
    std::set<TileType> get_allowable_terrain_types() const;
    bool is_terrain_type_allowed(const TileType terrain_type) const;

    void set_danger_level(const uint new_danger_level);
    uint get_danger_level() const;
    
    void set_rarity(const Rarity new_rarity);
    Rarity get_rarity() const;
    
    void set_initial_hit_points(const Dice& new_initial_hit_points);
    Dice get_initial_hit_points() const;
    
    void set_base_experience_value(const uint new_base_experience_value);
    uint get_base_experience_value() const;

  protected:
    // The terrain types in which the creature can be generated
    std::set<TileType> allowable_terrain_types;

    // The "danger level" at which the creature may start appearing,
    // if it is not out of depth/danger-depth.
    uint danger_level;

    // The more rare a creature is, the less chance of it getting generated in a given spawn.
    Rarity rarity;
    
    // A range used to randomly generate a creature's hit points every time an instance
    // is created from the template.
    Dice initial_hit_points;
    
    // The base experience value.  Stored here so that a slightly different value can
    // be generated for each creature.
    uint base_experience_value;
};

typedef std::map<std::string, CreatureGenerationValues> CreatureGenerationValuesMap;
