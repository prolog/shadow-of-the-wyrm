#pragma once
#include "Effect.hpp"

class SummonMonstersEffect : public Effect
{
  public:
    SummonMonstersEffect();
    virtual ~SummonMonstersEffect() = default;

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;
      
  protected:
    virtual bool summon(CreaturePtr creature, MapPtr map, const int num_monsters, bool make_followers);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    
    std::string summon_msg;
    static const int SUMMON_DANGER_OFFSET;
};

