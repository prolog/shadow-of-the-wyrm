#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Skills.hpp"

typedef std::map<ClassIdentifier, SkillPtr> SkillSerializationMap;

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

