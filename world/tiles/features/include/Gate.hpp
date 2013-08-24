#pragma once
#include "Entrance.hpp"

class Gate : public Entrance
{
  public:
    Gate();
    Gate(LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone();

    virtual bool handle();
    virtual bool kick();
    virtual bool get_is_blocking() const;
    virtual uchar get_symbol() const;

  protected:
    virtual std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};
