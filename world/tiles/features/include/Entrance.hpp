#pragma once
#include "CreatureFeatures.hpp"
#include "EntranceState.hpp"
#include "Feature.hpp"

class Entrance : public Feature
{
  public:
    Entrance();
    Entrance(LockPtr new_lock, const EntranceState& new_state);

    virtual void set_lock(LockPtr new_lock);
    virtual LockPtr get_lock();

    virtual void set_state(const EntranceState& new_state);
    virtual EntranceState get_state() const;
    
    virtual void set_maximum_size(const CreatureSize new_maximum_size);
    virtual CreatureSize get_maximum_size() const;

    virtual bool can_open() const;
    
    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    LockPtr lock;
    EntranceState state;
    CreatureSize maximum_size; // The maximum creature size for the entrance.  Dragons can't go in Hobbit holes.

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};
