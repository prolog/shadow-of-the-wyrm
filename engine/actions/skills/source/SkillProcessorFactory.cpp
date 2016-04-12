#include "SkillProcessorFactory.hpp"
#include "SkillProcessors.hpp"

SkillProcessorFactory::SkillProcessorFactory()
{
}

SkillProcessorFactory::~SkillProcessorFactory()
{
}

ISkillProcessorPtr SkillProcessorFactory::create(const SkillType st)
{
  ISkillProcessorPtr sp = std::make_shared<DefaultSkillProcessor>();
  return sp;
}

