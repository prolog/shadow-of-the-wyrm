#pragma once
#include <boost/serialization/base_object.hpp>
#include "CreatureFeatures.hpp"
#include "EntranceState.hpp"
#include "Feature.hpp"
#include "ILockable.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class Entrance : public Feature, public ILockable
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
    
  protected:
    LockPtr lock;
    EntranceState state;
    CreatureSize maximum_size; // The maximum creature size for the entrance.  Dragons can't go in Hobbit holes.

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Feature>(*this);
      ar & boost::serialization::base_object<ILockable>(*this);
      ar & lock & state & maximum_size;
    }
};
