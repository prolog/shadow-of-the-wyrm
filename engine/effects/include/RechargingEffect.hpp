#pragma once
#include "Effect.hpp"
#include "Wand.hpp"

class RechargingEffect : public Effect
{
  public:
    RechargingEffect();
    virtual ~RechargingEffect() = default;
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    // Check to see if the creature has any rechargable items (i.e., wands).
    virtual bool has_rechargables(std::shared_ptr<Creature> creature);
    virtual bool recharge(CreaturePtr creature, ActionManager * const am, const ItemStatus item_status);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;

    void add_player_no_wands_message();
    void add_recharge_message(std::shared_ptr<Creature> creature, WandPtr wand);
    void add_recharge_already_full_message(std::shared_ptr<Creature> creature, WandPtr wand);
};

