#pragma once
#include "Effect.hpp"
#include "StatusEffect.hpp"

class HasteEffect : public Effect
{
  public:
    virtual ~HasteEffect() = default;

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

    virtual std::string get_status_id() const override;

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;

    virtual void apply_haste(CreaturePtr creature, StatusEffectPtr haste);
};

