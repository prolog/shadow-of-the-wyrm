#pragma once
#include "common.hpp"
#include "EntranceTypes.hpp"
#include "ISerializable.hpp"
#include "Symbol.hpp"

class EntranceState : public ISerializable
{
  public:
    EntranceState();
    EntranceState(const EntranceStateType new_state);
    bool operator==(const EntranceState& st) const;

    void set_state(const EntranceStateType new_state);
    EntranceStateType get_state() const;

    Symbol get_symbol() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    EntranceStateType state;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
