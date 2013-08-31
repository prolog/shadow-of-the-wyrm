#pragma once
#include "Effect.hpp"
#include "Wand.hpp"

class RechargingEffect : public Effect
{
  public:
    RechargingEffect();
    
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    // Check to see if the creature has any rechargable items (i.e., wands).
    virtual bool has_rechargables(boost::shared_ptr<Creature> creature);
    virtual bool recharge(CreaturePtr creature, ActionManager * const am, const ItemStatus item_status);

    virtual bool effect_blessed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature, ActionManager * const am);

    virtual std::pair<int, int> get_charges_range(const ItemStatus item_status);

    void add_player_no_wands_message();
    void add_recharge_message(boost::shared_ptr<Creature> creature, WandPtr wand);
    void add_recharge_already_full_message(boost::shared_ptr<Creature> creature, WandPtr wand);
};

