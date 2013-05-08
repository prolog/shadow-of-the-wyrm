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

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  private:
    ClassIdentifier internal_class_identifier() const;

  protected:
    uint castings;
    Statistic bonus;
};
