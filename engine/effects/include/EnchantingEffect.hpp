#pragma once
#include "Effect.hpp"
#include "ItemTypes.hpp"

class EnchantingEffect : public Effect
{
  public:
    EnchantingEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;

    virtual bool enchant(std::shared_ptr<Creature> creature, ActionManager * const am, const ItemStatus item_status);
    virtual void add_player_no_items_message();
    virtual void add_player_enchant_artifact_message();
    std::map<ItemStatus, float> item_status_multipliers;
};

