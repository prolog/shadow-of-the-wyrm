#pragma once
#include "Directions.hpp"
#include "SpellTypes.hpp"

// A class used to get properties about a spell's shape - the raw type,
// whether casting the spell requires prompting for direction, etc.
class SpellShape
{
  public:
    SpellShape();
    SpellShape(const SpellShapeType st, const DirectionCategory dir_cat);
    bool operator==(const SpellShape& ss) const;

    SpellShapeType get_spell_shape_type() const;
    DirectionCategory get_direction_category() const;

  protected:
    SpellShapeType spell_shape_type;
    DirectionCategory direction_category;
};

