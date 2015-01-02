#pragma once
#include <array>
#include <map>
#include "ConductTypes.hpp"
#include "ISerializable.hpp"

// Creature conducts - the engine will track these in case the player wants
// to try to stick to particular conducts.
class Conducts : public ISerializable
{
  public:
    Conducts();
    bool operator==(const Conducts& cond) const;

    std::array<bool, static_cast<size_t>(ConductType::CONDUCT_SIZE)> get_conducts() const;
    void break_conduct(const ConductType conduct);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::array<bool, static_cast<size_t>(ConductType::CONDUCT_SIZE)> cond;
    ClassIdentifier internal_class_identifier() const override;
};

