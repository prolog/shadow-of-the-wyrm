#pragma once
#include "SpellShapeProcessor.hpp"
#include "SpellTypes.hpp"

// A class responsible for creating the appropriate ISpellShapeProcessor
// based on the spell shape provided.
class SpellShapeProcessorFactory
{
  public:
    static SpellShapeProcessorPtr create_processor(const SpellShape spell_shape);

  protected:
    SpellShapeProcessorFactory();
    ~SpellShapeProcessorFactory();
};
