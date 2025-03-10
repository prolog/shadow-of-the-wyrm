#pragma once
#include "IDescriber.hpp"
#include "Creature.hpp"

class CreatureDescriber : public IDescriber
{
  public:
    CreatureDescriber(CreaturePtr viewing_creature, CreaturePtr new_creature);
    CreatureDescriber(CreaturePtr viewing_creature, CreaturePtr new_creature, bool short_description);
    virtual ~CreatureDescriber() = default;

    std::string describe() const override;
    std::string describe_for_tile_selection() const;
    std::string describe_for_save_file() const;

  protected:
    std::string describe_statuses() const;
    std::string describe_race_and_class() const;

    CreaturePtr viewing_creature;
    CreaturePtr creature;
    bool short_description;
};
