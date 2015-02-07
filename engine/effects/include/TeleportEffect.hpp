#pragma once
#include "Effect.hpp"

class TeleportEffect : public Effect
{
  public:
    TeleportEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual void read_properties(const std::map<std::string, std::string>& properties) override;

    virtual Effect* clone() override;

  protected:
    virtual bool teleport(std::shared_ptr<Creature> creature);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;

    // Teleport anywhere on the map
    virtual bool teleport(std::shared_ptr<Creature> creature, std::shared_ptr<Map> current_map, TilePtr old_tile);

    // Teleport within the creature's view map
    virtual bool blink(std::shared_ptr<Creature> creature, std::shared_ptr<Map> current_map, TilePtr old_tile);

    bool blink_effect;
    static const std::string TELEPORT_BLINK;
};

