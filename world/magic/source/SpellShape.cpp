#include "SpellShape.hpp"

// This constructor shouldn't really be used - it should only be used to construct
// a default object, and the actual SpellShape should be set into the object later.
SpellShape::SpellShape()
: spell_shape_type(SPELL_SHAPE_TARGET_SELF), requires_direction(false)
{
}

SpellShape::SpellShape(const SpellShapeType st, const bool req_dir)
: spell_shape_type(st), requires_direction(req_dir)
{
}

bool SpellShape::operator==(const SpellShape& ss)
{
  bool result = true;

  result = result && (spell_shape_type == ss.spell_shape_type);
  result = result && (requires_direction == ss.requires_direction);

  return result;
}

SpellShapeType SpellShape::get_spell_shape_type() const
{
  return spell_shape_type;
}

bool SpellShape::get_requires_direction() const
{
  return requires_direction;
}


