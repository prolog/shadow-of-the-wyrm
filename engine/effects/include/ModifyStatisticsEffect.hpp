#pragma once
#include "Effect.hpp"
#include "StatisticsModifier.hpp"

class ModifyStatisticsEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

    void set_statistics_modifier(const StatisticsModifier& new_sm);
    StatisticsModifier get_statistics_modifier() const;

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;

    virtual bool apply_statistics_modifiers(std::shared_ptr<Creature>, const StatisticsModifier& sm) const;

    StatisticsModifier sm;
};

