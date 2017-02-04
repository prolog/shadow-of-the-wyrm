#pragma once
#include <memory>
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
    virtual bool operator==(const DecisionStrategy& ds) const;

    virtual ~DecisionStrategy() {};
    virtual CommandPtr get_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, std::shared_ptr<Map> view_map = nullptr /* optional - only used when getting a decision on the main map, and only for non-player characters. */, int* key_p = 0) = 0;
    virtual CommandPtr get_nonmap_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p = 0) = 0;

    virtual uint get_count(const uint max_count) = 0; // For turns to wait, pick up, drop, etc.
    virtual bool get_confirmation(const bool confirmation_default_value = false) = 0;

    ThreatRatings& get_threats_ref();
    ThreatRatings  get_threats() const;

    // Overridden because in some cases, creatures will want to do things based
    // on the content of the newly-set map.  For instance, shopkeepers will get
    // angry at creatures carrying unpaid merchandise.
    virtual void set_fov_map(std::shared_ptr<Map> new_fov_map);
    std::shared_ptr<Map> get_fov_map();

    virtual ControllerPtr get_controller();

    virtual bool can_move() const;

    void set_property(const std::string& prop, const std::string& val);
    std::string get_property(const std::string& prop) const;
    void set_properties(const std::map<std::string, std::string>& new_props);
    std::map<std::string, std::string>& get_properties_ref();
    std::map<std::string, std::string> get_properties() const;

    virtual DecisionStrategy* copy() = 0;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    // The FOV map is not serialized - it is recalculated before each creature acts.  Since it is the
    // basis for only that monster's decisions, it's safe.
    std::shared_ptr<Map> current_fov_map;
    ThreatRatings threat_ratings;
    ControllerPtr controller;
    std::map<std::string, std::string> properties;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

using DecisionStrategyPtr = std::shared_ptr<DecisionStrategy>;
