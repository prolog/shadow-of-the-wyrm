#pragma once
#include "ISkillProcessor.hpp"

class SkillProcessorFactory
{
  public:
    static ISkillProcessorPtr create(const SkillType st);

  protected:
    SkillProcessorFactory();
    ~SkillProcessorFactory();
};

