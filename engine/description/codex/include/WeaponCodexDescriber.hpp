#pragma once
#include "WearableCodexDescriber.hpp"

class WeaponCodexDescriber : public WearableCodexDescriber
{
  public: 
    WeaponCodexDescriber(ItemPtr item);

    std::string describe_for_synopsis_line() const override;
    std::string describe_details() const;
};

