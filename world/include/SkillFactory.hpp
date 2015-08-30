#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Skills.hpp"

using SkillSerializationMap = std::map<ClassIdentifier, SkillPtr>;

class SkillFactory
{
  public:
    static SkillPtr create_skill(const ClassIdentifier ci);

  protected:
    SkillFactory();
    ~SkillFactory();

    static void initialize_skill_map();

    static SkillSerializationMap skill_map;
};

