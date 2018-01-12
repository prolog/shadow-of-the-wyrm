#pragma once
#include "Effect.hpp"

class IncreaseMaxHPAPEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const = 0;
    virtual Effect* clone() = 0;

  protected:
    // The check statistic is the effect that needs to be checked to see if
    // the creature can increase max HP/AP.  Ie, a creature can't farm golden
    // apples and get like 10k HP - the creature can only use the effect once
    // per point of Health/Willpower.
    virtual Statistic& get_check_statistic(std::shared_ptr<Creature> creature) = 0;

    // The statistic (HP or AP) to be increased.
    virtual Statistic& get_increase_statistic(std::shared_ptr<Creature> creature) = 0;

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    
    virtual bool increase(std::shared_ptr<Creature> creature, const int incr_amount);

    virtual std::string get_check_property() const = 0;

    static const int INCR_AMOUNT_BLESSED;
    static const int INCR_AMOUNT_UNCURSED;
    static const int INCR_AMOUNT_CURSED;
};

class IncreaseMaxHPEffect : public IncreaseMaxHPAPEffect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual Statistic& get_check_statistic(std::shared_ptr<Creature> creature) override;
    virtual Statistic& get_increase_statistic(std::shared_ptr<Creature> creature) override;

    virtual std::string get_check_property() const override;
};

// Basically, a type of healing effect, but instead of healing HP, heals
// AP.
class IncreaseMaxAPEffect : public IncreaseMaxHPAPEffect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual Statistic& get_check_statistic(std::shared_ptr<Creature> creature) override;
    virtual Statistic& get_increase_statistic(std::shared_ptr<Creature> creature) override;

    virtual std::string get_check_property() const override;
};
