#pragma once
#include <map>
#include <string>
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "ISerializable.hpp"

typedef std::multimap<ActionCost, std::string> CreatureActionMultimap;

class ActionCoordinator
{
  public:
    void set(const std::map<std::string, CreaturePtr>& creatures);
    void add(const ActionCost& action_cost, const std::string& creature_id);
    void clear();

    ActionCost get_next_action_cost() const;
    std::string get_next_creature_id_and_update_actions();
    
    bool has_actions() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    void update_actions();
    std::string get_next_creature_id() const;

    CreatureActionMultimap creature_action_order;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef std::multimap<ActionCost, std::string>::iterator ActionOrderIterator;
typedef std::multimap<ActionCost, std::string>::const_iterator ActionOrderConstIterator;
