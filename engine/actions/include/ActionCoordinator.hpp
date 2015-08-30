#pragma once
#include <map>
#include <string>
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "ISerializable.hpp"

using CreatureActionMultimap = std::multimap<ActionCost, std::string>;

class ActionCoordinator : public ISerializable
{
  public:
    bool operator==(const ActionCoordinator& ac) const;

    void set(const std::map<std::string, CreaturePtr>& creatures);
    void add(const ActionCost& action_cost, const std::string& creature_id);
    void clear();

    bool reset_if_necessary(const bool map_is_permanent, const std::string& new_map_guid, const std::map<std::string, CreaturePtr>& new_map_creatures);

    ActionCost get_current_action_cost() const;
    std::string get_next_creature_id_and_update_actions();
    std::string get_next_creature_id() const;
    void update_actions();
    
    virtual std::string get_current_map_id() const;

    bool has_actions() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    friend class SL_Engine_Actions_ActionCoordinatorFixture; // test fixture

    CreatureActionMultimap creature_action_order;
    std::string current_map_id;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using ActionOrderIterator = std::multimap<ActionCost, std::string>::iterator;
using ActionOrderConstIterator = std::multimap<ActionCost, std::string>::const_iterator;
