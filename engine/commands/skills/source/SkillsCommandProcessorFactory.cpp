#include "SkillsCommandProcessorFactory.hpp"
#include "GainSkillsCommandProcessor.hpp"
#include "ShowSkillsCommandProcessor.hpp"

ISkillsCommandProcessorPtr SkillsCommandProcessorFactory::create(const SkillsSelectionType sst)
{
  ISkillsCommandProcessorPtr scp;

  switch(sst)
  {
    case SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL:
      scp = std::make_shared<ShowSkillsCommandProcessor>();
      break;
    case SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL:
    default:
      scp = std::make_shared<GainSkillsCommandProcessor>();
      break;
  }

  return scp;
}

#ifdef UNIT_TESTS
#include "unit_tests/SkillsCommandProcessorFactory_test.cpp"
#endif

