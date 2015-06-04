#pragma once
#include <map>
#include <set>
#include <string>
#include "Dice.hpp"
#include "EquipmentTypes.hpp"
#include "GenerationValues.hpp"
#include "InitialItem.hpp"
#include "tiles.hpp"

// Values that are used to generate a creature, without being a necessary
// part of the creature itself.  Prevents values that only need a single
// instance from being duplicated on every creature.
class CreatureGenerationValues : public GenerationValues
{
  public:
    CreatureGenerationValues();
    ~CreatureGenerationValues();
    bool operator==(const CreatureGenerationValues& cgv) const;
    
    void set_race_id(const std::string& new_race_id);
    std::string get_race_id() const;

    void add_allowable_terrain_type(const TileType additional_terrain_type);
    void clear_allowable_terrain_types();
    void set_allowable_terrain_types(const std::set<TileType>& new_allowable_terrain_types);
    std::set<TileType> get_allowable_terrain_types() const;
    bool is_terrain_type_allowed(const TileType terrain_type) const;

    void set_friendly(const bool new_friendly);
    bool get_friendly() const;

    void set_initial_hit_points(const Dice& new_initial_hit_points);
    Dice get_initial_hit_points() const;
    
    void set_base_experience_value(const uint new_base_experience_value);
    uint get_base_experience_value() const;

    void set_initial_equipment(const std::map<EquipmentWornLocation, InitialItem>& new_initial_equipment);
    std::map<EquipmentWornLocation, InitialItem> get_initial_equipment() const;

    void set_initial_inventory(const std::vector<InitialItem>& new_initial_inventory);
    std::vector<InitialItem> get_initial_inventory() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    // The creature's race, used for filtering in certain situations.
    std::string race_id;

    // The terrain types in which the creature can be generated
    std::set<TileType> allowable_terrain_types;

    // Whether the creature is initially generated as hostile.
    // If "friendly" is set, the creature will never be generated
    // hostile towards the player.
    bool friendly;

    // A range used to randomly generate a creature's hit points every time an instance
    // is created from the template.
    Dice initial_hit_points;
    
    // The base experience value.  Stored here so that a slightly different value can
    // be generated for each creature.
    uint base_experience_value;

    // The initial equipment/inventory, used when generating the creature.
    std::map<EquipmentWornLocation, InitialItem> initial_equipment;
    std::vector<InitialItem> initial_inventory;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::map<std::string, CreatureGenerationValues> CreatureGenerationValuesMap;
