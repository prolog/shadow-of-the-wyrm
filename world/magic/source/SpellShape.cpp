#include "SpellShape.hpp"

// This constructor shouldn't really be used - it should only be used to construct
// a default object, and the actual SpellShape should be set into the object later.
SpellShape::SpellShape()
: spell_shape_type(SPELL_SHAPE_TARGET_SELF), direction_category(DIRECTION_CATEGORY_NONE)
{
}

SpellShape::SpellShape(const SpellShapeType st, const DirectionCategory dir_cat)
: spell_shape_type(st), direction_category(dir_cat)
{
}

bool SpellShape::operator==(const SpellShape& ss)
{
  bool result = true;

  result = result && (spell_shape_type == ss.spell_shape_type);
  result = result && (direction_category == ss.direction_category);

  return result;
}

SpellShapeType SpellShape::get_spell_shape_type() const
{
  return spell_shape_type;
}

DirectionCategory SpellShape::get_direction_category() const
{
  return direction_category;
}


