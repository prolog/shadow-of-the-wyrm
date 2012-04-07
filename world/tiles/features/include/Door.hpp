#pragma once
#include "Entrance.hpp"

// Doors are Features, but like Windows, will be re-used outside the
// dungeon environment.
class Door : public Entrance
{
  public:
    Door(LockPtr new_lock, const EntranceState& new_state);

    virtual bool handle();
    virtual bool kick();
    virtual bool get_blocking() const;
    virtual uchar get_symbol()  const;
    virtual std::string get_description_sid() const;
    
  protected:
};
