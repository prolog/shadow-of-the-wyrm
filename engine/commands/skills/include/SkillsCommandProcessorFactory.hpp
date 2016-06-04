#pragma once
#include "ISkillsCommandProcessor.hpp"
#include "SkillTypes.hpp"

class SkillsCommandProcessorFactory
{
  public:
    static ISkillsCommandProcessorPtr create(const SkillsSelectionType sst);
};

