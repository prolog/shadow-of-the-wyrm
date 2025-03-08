#pragma once
#include "Effect.hpp"
#include "Map.hpp"

class TeleportEffect : public Effect
{
  public:
    TeleportEffect();
    virtual ~TeleportEffect() = default;
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual void read_properties(const std::map<std::string, std::string>& properties) override;

    // Creatures get angry when wrenched randomly around maps.
    virtual bool is_negative_effect() const override;

    virtual Effect* clone() override;

  protected:
    virtual bool teleport(std::shared_ptr<Creature> creature);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;

    // Teleport anywhere on the map
    virtual bool teleport(std::shared_ptr<Creature> creature, std::shared_ptr<Map> current_map, TilePtr old_tile);

    // Teleport within the creature's view map
    virtual bool blink(std::shared_ptr<Creature> creature, std::shared_ptr<Map> current_map, TilePtr old_tile);
    
    // Get the appropriate keys based on whether a preset teleport location is
    // required.
    std::vector<std::string> get_appropriate_keys(MapPtr map, const std::pair<bool, Coordinate>& teleport_loc);
    
    bool blink_effect;
    std::pair<bool, Coordinate> teleport_location;
    static const std::string TELEPORT_BLINK;
};

