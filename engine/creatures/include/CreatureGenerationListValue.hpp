#pragma once
#include <string>
#include "Creature.hpp"
#include "CreatureGenerationValues.hpp"

// Describes an item in a creature generation list (vector).  Contains the
// creature's base ID, a pointer (possibly null) to the template creature,
// and the associated creature generation values.
class CreatureGenerationListValue
{
  public:
    CreatureGenerationListValue(const std::string& new_creature_base_id, CreaturePtr new_creature, const CreatureGenerationValues new_cgv);
    bool operator==(const CreatureGenerationListValue& cglv2) const;

    std::string get_creature_base_id() const;
    CreaturePtr get_creature() const;
    CreatureGenerationValues get_creature_generation_values() const;

  protected:
    std::string creature_base_id;
    CreaturePtr creature;
    CreatureGenerationValues cgv;
};
