#pragma once
#include "IDescriber.hpp"
#include "Creature.hpp"

class CreatureDescriber : public IDescriber
{
  public:
    CreatureDescriber(CreaturePtr new_creature);

    std::string describe() const;

  protected:
    CreaturePtr creature;
};
