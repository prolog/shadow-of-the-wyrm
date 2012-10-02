#pragma once
#include "Entrance.hpp"

class Gate : public Entrance
{
  public:
    Gate();
    Gate(LockPtr new_lock, const EntranceState& new_state);

    virtual bool handle();
    virtual bool kick();
    virtual bool get_is_blocking() const;
    virtual uchar get_symbol() const;
    virtual std::string get_description_sid() const;

  protected:
};
