#pragma once
#include "Effect.hpp"
#include "Map.hpp"


class GlowEffect : public Effect
{
  public:
    virtual ~GlowEffect() = default;

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool glow(std::shared_ptr<Creature> creature, ActionManager * const am, const bool glow_enabled);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;

    void add_artifact_message(std::shared_ptr<Creature> creature);
    void glow_item(std::shared_ptr<Creature> creature, ItemPtr item, const bool glow_on);
};

