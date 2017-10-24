#pragma once
#include "AltarManipulator.hpp"

class GoodAltarManipulator : public AltarManipulator
{
  public:
    GoodAltarManipulator(FeaturePtr feature);

    std::string get_creature_action_key() const override;
};

