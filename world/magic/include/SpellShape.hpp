#pragma once
#include "common.hpp"
#include "Directions.hpp"
#include "SpellTypes.hpp"

// A class used to get properties about a spell's shape - the raw type,
// whether casting the spell requires prompting for direction, etc.
class SpellShape
{
  public:
    SpellShape();
    SpellShape(const SpellShapeType st, const DirectionCategory dir_cat, const uint new_radius);
    bool operator==(const SpellShape& ss) const;

    SpellShapeType get_spell_shape_type() const;
    DirectionCategory get_direction_category() const;
    uint get_radius() const;

    // Does the spell affect the external world? (ie, beam, bolt, ball...)
    // Or is it internal? (targets the self)
    SpellSituationType get_spell_situation() const;

  protected:
    SpellShapeType spell_shape_type;
    DirectionCategory direction_category;
    uint radius;
};

