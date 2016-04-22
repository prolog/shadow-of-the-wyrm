#pragma once
#include "SkillProcessor.hpp"

class DefaultSkillProcessor : public SkillProcessor
{
  public:
    DefaultSkillProcessor(const std::string& new_message_sid);

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map);

  protected:
    std::string message_sid;
};

class WeaponSkillProcessor : public DefaultSkillProcessor
{
  public:
    WeaponSkillProcessor();
};

class MagicSkillProcessor : public DefaultSkillProcessor
{
  public:
    MagicSkillProcessor();
};