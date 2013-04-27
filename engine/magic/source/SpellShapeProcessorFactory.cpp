#include <boost/make_shared.hpp>
#include "BallShapeProcessor.hpp"
#include "BeamShapeProcessor.hpp"
#include "ConeShapeProcessor.hpp"
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
      spell_processor = boost::make_shared<TargetSelfShapeProcessor>();
      break;
    case SPELL_SHAPE_BEAM:
      spell_processor = boost::make_shared<BeamShapeProcessor>();
      break;
    case SPELL_SHAPE_REFLECTIVE_BEAM:
      spell_processor = boost::make_shared<ReflectiveBeamShapeProcessor>();
      break;
    case SPELL_SHAPE_CONE:
      spell_processor = boost::make_shared<ConeShapeProcessor>();
      break;
    case SPELL_SHAPE_BALL:
    default:
      spell_processor = boost::make_shared<BallShapeProcessor>();
      break;
  }

  return spell_processor;
}
