#include "SpellConstants.hpp"
#include "SpellShape.hpp"

// This constructor shouldn't really be used - it should only be used to construct
// a default object, and the actual SpellShape should be set into the object later.
SpellShape::SpellShape()
: spell_shape_type(SpellShapeType::SPELL_SHAPE_TARGET_SELF), direction_category(DirectionCategory::DIRECTION_CATEGORY_NONE), radius(SpellConstants::DEFAULT_BEAM_RADIUS)
{
}

SpellShape::SpellShape(const SpellShapeType st, const DirectionCategory dir_cat, const uint new_radius)
: spell_shape_type(st), direction_category(dir_cat), radius(new_radius)
{
}

bool SpellShape::operator==(const SpellShape& ss) const
{
  bool result = true;

  result = result && (spell_shape_type == ss.spell_shape_type);
  result = result && (direction_category == ss.direction_category);
  result = result && (radius == ss.radius);

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

uint SpellShape::get_radius() const
{
  return radius;
}

