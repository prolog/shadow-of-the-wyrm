#pragma once
#include "SkillProcessor.hpp"

class DefaultSkillProcessor : public SkillProcessor
{
  public:
    DefaultSkillProcessor(const std::string& new_message_sid, const bool new_implemented = true);

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;
    virtual bool is_skill_implemented() const override;

  protected:
    std::string message_sid;
    bool implemented;
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