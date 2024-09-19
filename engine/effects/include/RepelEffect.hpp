#pragma once
#include "Effect.hpp"

class RepelEffect : public Effect
{
  public:
    virtual ~RepelEffect() = default;

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool repel(std::shared_ptr<Creature> creature, const Coordinate& affected_coordinate, const int distance);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;

  static const int DISTANCE_BLESSED;
  static const int DISTANCE_UNCURSED;
  static const int DISTANCE_CURSED;
};

