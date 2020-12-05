#pragma once
#include "SkillProcessor.hpp"
#include "Spellbook.hpp"

class GeneralMagicSkillProcessor : public SkillProcessor
{
  public:
    GeneralMagicSkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    ActionCostValue incinerate_spellbook(CreaturePtr creature, SpellbookPtr book, const int book_ap);

    virtual ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
    static const int PCT_CHANCE_BACKFIRE;
};

