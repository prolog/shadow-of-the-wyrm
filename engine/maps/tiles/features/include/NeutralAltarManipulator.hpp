#pragma once
#include "AltarManipulator.hpp"

class NeutralAltarManipulator : public AltarManipulator
{
  public:
    NeutralAltarManipulator(FeaturePtr feature);

    std::string get_creature_action_key() const override;
};

