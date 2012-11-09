#pragma once
#include "common.hpp"
#include "EntranceTypes.hpp"
#include "ISerializable.hpp"

class EntranceState : public ISerializable
{
  public:
    EntranceState();
    EntranceState(const EntranceStateType new_state);
    
    void set_state(const EntranceStateType new_state);
    EntranceStateType get_state() const;
    
    uchar get_symbol() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);
    
  protected:
    EntranceStateType state;

  private:
    ClassIdentifier internal_class_identifier() const;
};
