#include "BallShapeProcessor.hpp"
#include "BeamShapeProcessor.hpp"
#include "ConeShapeProcessor.hpp"
#include "CrossShapeProcessor.hpp"
#include "ReflectiveBeamShapeProcessor.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "TargetSelfShapeProcessor.hpp"

SpellShapeProcessorFactory::SpellShapeProcessorFactory()
{
}

SpellShapeProcessorFactory::~SpellShapeProcessorFactory()
{
}

SpellShapeProcessorPtr SpellShapeProcessorFactory::create_processor(const SpellShapeType spell_shape)
{
  SpellShapeProcessorPtr spell_processor;

  switch(spell_shape)
  {
    case SPELL_SHAPE_TARGET_SELF:
      spell_processor = std::make_shared<TargetSelfShapeProcessor>();
      break;
    case SPELL_SHAPE_BEAM:
      spell_processor = std::make_shared<BeamShapeProcessor>();
      break;
    case SPELL_SHAPE_REFLECTIVE_BEAM:
      spell_processor = std::make_shared<ReflectiveBeamShapeProcessor>();
      break;
    case SPELL_SHAPE_CONE:
      spell_processor = std::make_shared<ConeShapeProcessor>();
      break;
    case SPELL_SHAPE_BALL:
      spell_processor = std::make_shared<BallShapeProcessor>();
      break;
    case SPELL_SHAPE_CROSS:
    default:
      spell_processor = std::make_shared<CrossShapeProcessor>();
      break;
  }

  return spell_processor;
}
