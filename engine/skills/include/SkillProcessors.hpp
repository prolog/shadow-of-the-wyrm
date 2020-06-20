#pragma once
#include "SkillProcessor.hpp"

class DefaultSkillProcessor : public SkillProcessor
{
  public:
    DefaultSkillProcessor(const std::string& new_message_sid);

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    std::string message_sid;
};

class WeaponSkillProcessor : public DefaultSkillProcessor
{
  public:
    WeaponSkillProcessor();

    virtual SkillProcessorPtr clone() override;
};

class MagicSkillProcessor : public DefaultSkillProcessor
{
  public:
    MagicSkillProcessor();

    virtual SkillProcessorPtr clone() override;
};