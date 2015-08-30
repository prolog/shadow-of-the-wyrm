#pragma once
#include <map>
#include "ISerializable.hpp"
#include "ITimeObserver.hpp"

using TimeObserverMap = std::map<std::string, ITimeObserverPtr>;
using WorldTimeKeeperObserverMap = std::map<uint, TimeObserverMap>;

// The subject in the subject/observer pattern.
class WorldTimeKeeper : public ISerializable
{
  public:
    WorldTimeKeeper();
    
    void register_observer(const uint minutes_key, ITimeObserverPtr new_observer);
    void deregister_observer(const uint minutes_key, ITimeObserverPtr old_observer);
    void reset();

    void tick(const double seconds);

    bool serialize(std::ostream& stream) const override;
    bool serialize_observers(std::ostream& stream) const;
    bool deserialize(std::istream& stream) override;
    bool deserialize_observers(std::istream& stream);
    
  protected:
    double seconds_counter;
    double total_seconds_counter;
    
    WorldTimeKeeperObserverMap observers;

   private:
     ClassIdentifier internal_class_identifier() const override;
};
