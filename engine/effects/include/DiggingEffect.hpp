#pragma once
#include "Effect.hpp"

class DiggingEffect : public Effect
{
  public:
    DiggingEffect();
    virtual ~DiggingEffect() = default;

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;
      
  protected:
    virtual bool dig(CreaturePtr creature, const Coordinate& c);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;

    // The first time the effect instance is invoked, messages should be added.
    // After that, messages shouldn't be added.  This prevents text like,
    // "You dig. You dig. You dig."  This is a roguelike game, not a beat
    // poetry reading.
    bool add_messages;
};

