#pragma once
#include "Effect.hpp"

enum struct MappingType
{
  MAPPING_TYPE_FORGET = 0,
  MAPPING_TYPE_MAP = 1,
  MAPPING_TYPE_MAP_ALL = 2
};

class MappingEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;
      
  protected:
    virtual void map(std::shared_ptr<Creature> creature, MapPtr map, const MappingType mt);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile) override;
    
    std::string mapping_msg;
};

