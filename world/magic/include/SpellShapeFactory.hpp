#pragma once
#include "SpellTypes.hpp"

class SpellShape;

// A factory class responsible for creating and configuring spell shapes
// properly.
class SpellShapeFactory
{
  public:
    static SpellShape create_spell_shape(const SpellShapeType st);

  protected:
    SpellShapeFactory();
};
