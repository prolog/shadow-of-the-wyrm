#pragma once
#include <boost/shared_ptr.hpp>
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "ISerializable.hpp"
#include "KeyboardCommandMap.hpp"
#include "Map.hpp"
#include "ThreatRatings.hpp"

class Map;

// Abstract base class for all other decision strategies.
class DecisionStrategy : public ISerializable
{
  public:
    DecisionStrategy(ControllerPtr new_controller);
    virtual bool operator==(const DecisionStrategy& ds);

    virtual ~DecisionStrategy() {};
    virtual CommandPtr get_decision(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, boost::shared_ptr<Map> view_map = boost::shared_ptr<Map>() /* optional - only used when getting a decision on the main map, and only for non-player characters. */, int* key_p = 0) = 0;
    virtual CommandPtr get_nonmap_decision(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p = 0) = 0;

    virtual uint get_count(const uint max_count) = 0; // For turns to wait, pick up, drop, etc.
    virtual bool get_confirmation() = 0;

    ThreatRatings& get_threats_ref();
    ThreatRatings  get_threats() const;

    void set_fov_map(boost::shared_ptr<Map> new_fov_map);
    boost::shared_ptr<Map> get_fov_map();

    virtual DecisionStrategy* copy() = 0;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    // The FOV map is not serialized - it is recalculated before each creature acts.  Since it is the
    // basis for only that monster's decisions, it's safe.
    boost::shared_ptr<Map> current_fov_map;
    ThreatRatings threat_ratings;
    ControllerPtr controller;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

typedef boost::shared_ptr<DecisionStrategy> DecisionStrategyPtr;
