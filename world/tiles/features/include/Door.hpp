#pragma once
#include "Entrance.hpp"

// Doors are Features, but like Windows, will be re-used outside the
// dungeon environment.
class Door : public Entrance
{
  public:
    Door();
    Door(LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone();

    virtual ~Door() {};

    virtual bool handle();
    virtual bool kick();
    virtual bool get_is_blocking() const;
    virtual uchar get_symbol()  const;
    virtual std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
 };
