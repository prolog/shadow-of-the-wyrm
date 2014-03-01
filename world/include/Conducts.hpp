#pragma once
#include <array>
#include "ISerializable.hpp"

enum ConductType
{
  CONDUCT_TYPE_FOODLESS = 0,
  CONDUCT_TYPE_AGNOSTIC = 1,
  CONDUCT_TYPE_ILLITERATE = 2,
  CONDUCT_TYPE_WEAPONLESS = 3,
  CONDUCT_SIZE = 4
};

// Creature conducts - the engine will track these in case the player wants
// to try to stick to particular conducts.
class Conducts : public ISerializable
{
  public:
    Conducts();
    bool operator==(const Conducts& cond) const;

    void break_conduct(const ConductType conduct);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::array<bool, CONDUCT_SIZE> cond;
    ClassIdentifier internal_class_identifier() const override;
};

