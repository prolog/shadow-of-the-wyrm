#pragma once
#include "CreatureFeatures.hpp"
#include "EntranceState.hpp"
#include "Feature.hpp"

class Entrance : public Feature
{
  public:
    Entrance();
    Entrance(LockPtr new_lock, const EntranceState& new_state);
    virtual bool operator==(const Entrance& door);

    virtual void set_state(const EntranceState& new_state);
    virtual EntranceState get_state() const;
    virtual EntranceState& get_state_ref();
    
    virtual void set_maximum_size(const CreatureSize new_maximum_size);
    virtual CreatureSize get_maximum_size() const;

    virtual bool can_handle(const bool feature_tile_occupied) const;
    virtual bool can_open() const;
    virtual bool can_lock() const;
    virtual bool open();
    virtual bool close();
    
    // Returns a value based on the current state of the entrance -
    // if the entrance is open, a message about opening the door; if
    // the entrance is closed, a message about closing the door (etc).
    virtual std::string get_handle_message_sid() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    EntranceState state;
    CreatureSize maximum_size; // The maximum creature size for the entrance.  Dragons can't go in Hobbit holes.

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};
