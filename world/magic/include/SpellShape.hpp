#pragma once
#include "SpellTypes.hpp"

// A class used to get properties about a spell's shape - the raw type,
// whether casting the spell requires prompting for direction, etc.
class SpellShape
{
  public:
    SpellShape();
    SpellShape(const SpellShapeType st, const bool req_direction);
    bool operator==(const SpellShape& ss);

    SpellShapeType get_spell_shape_type() const;
    bool get_requires_direction() const;

  protected:
    SpellShapeType spell_shape_type;
    bool requires_direction;
};

