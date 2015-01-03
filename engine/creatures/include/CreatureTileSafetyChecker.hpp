#pragma once
#include "ITileSafetyCondition.hpp"

typedef std::map<TileType, std::vector<ITileSafetyConditionPtr>> TileTypeSafetyConditionsMap;
typedef std::map<TileSuperType, std::vector<ITileSafetyConditionPtr>> TileSuperTypeSafetyConditionsMap;

// A class used to check tile safety conditions to determine whether it is
// safe for a creature to move there.  For example, moving on to water is
// not safe unless the creature has a boat; moving on to lava is not safe
// unless the creature is flying.
class CreatureTileSafetyChecker
{
  public:
    CreatureTileSafetyChecker();

    bool is_tile_safe_for_creature(CreaturePtr creature, TilePtr tile);

  protected:
    bool are_safety_conditions_satisfied(CreaturePtr creature, TilePtr tile, const std::vector<ITileSafetyConditionPtr>& safety_conditions);

    std::vector<ITileSafetyConditionPtr> get_safety_conditions(const TileType tile_type);
    std::vector<ITileSafetyConditionPtr> get_safety_conditions(const TileSuperType tile_super_type);

    void initialize_tile_safety_conditions();
    void initialize_tile_type_safety_conditions();
    void initialize_tile_super_type_safety_conditions();

    TileTypeSafetyConditionsMap tile_type_safety_conditions;
    TileSuperTypeSafetyConditionsMap tile_super_type_safety_conditions;
};

