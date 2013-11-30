#pragma once
#include "IDescriber.hpp"
#include "Creature.hpp"

class CreatureDescriber : public IDescriber
{
  public:
    CreatureDescriber(CreaturePtr new_creature);

    std::string describe() const override;
    std::string describe_for_tile_selection() const;
    std::string describe_for_save_file() const;

  protected:
    std::string describe_statuses() const;

    CreaturePtr creature;
};
