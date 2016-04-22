#pragma once
#include "SkillProcessor.hpp"

class SkillProcessorFactory
{
  public:
    static SkillProcessorPtr create(const SkillType st);

  protected:
    SkillProcessorFactory();
    ~SkillProcessorFactory();

    static void populate_skill_map();

    static std::map<SkillType, std::string> skill_map;
};

