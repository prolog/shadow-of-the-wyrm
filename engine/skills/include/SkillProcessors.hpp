#pragma once
#include "ISkillProcessor.hpp"

class DefaultSkillProcessor : public ISkillProcessor
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