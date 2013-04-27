#include "SpellShapeFactory.hpp"
#include "SpellShape.hpp"

SpellShapeFactory::SpellShapeFactory()
{
}

// Create a spell shape with the appropriate properties, based on the
// spell shape type.
SpellShape SpellShapeFactory::create_spell_shape(const SpellShapeType st)
{
  SpellShape directional_shape(st, DIRECTION_CATEGORY_CARDINALORDINAL);
  SpellShape cone_shape(st, DIRECTION_CATEGORY_CARDINAL);
  SpellShape selfcentered_shape(st, DIRECTION_CATEGORY_NONE);

  switch(st)
  {
    case SPELL_SHAPE_CONE:
      return cone_shape;
    case SPELL_SHAPE_BEAM:
    case SPELL_SHAPE_REFLECTIVE_BEAM:
      return directional_shape;
    case SPELL_SHAPE_TARGET_SELF:
    case SPELL_SHAPE_BALL:
    default:
      return selfcentered_shape;
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/SpellShapeFactory_test.cpp"
#endif