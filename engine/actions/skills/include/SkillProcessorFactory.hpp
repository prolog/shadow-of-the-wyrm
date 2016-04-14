#pragma once
#include "ISkillProcessor.hpp"

class SkillProcessorFactory
{
  public:
    static ISkillProcessorPtr create(const SkillType st);

  protected:
    SkillProcessorFactory();
    ~SkillProcessorFactory();

    static void populate_skill_map();

    static std::map<SkillType, std::string> skill_map;
};

