#pragma once
#include "Effect.hpp"

enum struct DetectTrapsEffectType
{
  DETECT_TRAPS_HIDE_TRAPS = 0,
  DETECT_TRAPS_SHOW_LOCAL_TRAPS = 1,
  DETECT_TRAPS_SHOW_ALL_TRAPS = 2
};

class DetectTrapsEffect : public Effect
{
  public:
    DetectTrapsEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool detect_traps(std::shared_ptr<Creature> creature, const DetectTrapsEffectType dtet);
    virtual void show_or_hide_traps(MapPtr trap_map, const DetectTrapsEffectType dtet);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
};

