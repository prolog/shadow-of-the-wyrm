#pragma once
#include "common.hpp"
#include "ISerializable.hpp"
#include "Statistic.hpp"

class IndividualSpellKnowledge : public ISerializable
{
  public:
    IndividualSpellKnowledge();
    bool operator==(const IndividualSpellKnowledge& isk) const;

    void set_castings(const uint new_castings);
    uint get_castings() const;

    void set_bonus(const Statistic& new_bonus);
    Statistic get_bonus() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  private:
    ClassIdentifier internal_class_identifier() const override;

  protected:
    uint castings;
    Statistic bonus;
};
