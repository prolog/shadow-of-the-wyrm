#pragma once
#include <array>
#include "ConductTypes.hpp"
#include "Creature.hpp"
#include "ISerializable.hpp"
#include "Equipment.hpp"

// Utility class for checking the jewelryless conduct, since it needs to be
// done in a few places.
class JewelrylessConduct
{
  public:
    bool breaks_conduct(const Equipment& eq) const;
    bool breaks_conduct(ItemPtr i) const;
};

// Creature conducts - the engine will track these in case the player wants
// to try to stick to particular conducts.
class Conducts : public ISerializable
{
  public:
    Conducts();
    bool operator==(const Conducts& cond) const;

    std::array<bool, static_cast<size_t>(ConductType::CONDUCT_SIZE)> get_conducts() const;
    void break_conduct(const ConductType conduct);

    int get_num_broken_conducts() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::array<bool, static_cast<size_t>(ConductType::CONDUCT_SIZE)> cond;
    ClassIdentifier internal_class_identifier() const override;
};

