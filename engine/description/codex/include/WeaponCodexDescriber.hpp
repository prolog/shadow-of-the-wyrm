#pragma once
#include "WearableCodexDescriber.hpp"
#include "Weapon.hpp"

class WeaponCodexDescriber : public WearableCodexDescriber
{
  public: 
    WeaponCodexDescriber(WeaponPtr weapon);
    virtual ~WeaponCodexDescriber() = default;

    std::string describe_for_synopsis_line() const override;
    std::string describe_details() const;

  protected:
    WeaponPtr weapon;
};

