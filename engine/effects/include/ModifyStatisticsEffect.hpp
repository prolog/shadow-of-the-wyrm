#pragma once
#include "Effect.hpp"
#include "Modifier.hpp"

class ModifyStatisticsEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

    void set_modifier(const Modifier& new_m);
    Modifier get_modifier() const;

    void set_spell_id(const std::string& new_spell_id);
    std::string get_spell_id() const;

  protected:
    friend class SL_Engine_Effects_ModifyStatisticsEffect;

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;

    virtual Modifier adjust_negative_modifiers(std::shared_ptr<Creature> creature, const Modifier& m) const;
    virtual bool apply_modifiers(std::shared_ptr<Creature>, const Modifier& m) const;

    virtual int get_primary_statistic_modifier(int stat_score, int stat_modifier) const;

    Modifier m;
    std::string spell_id;
};

