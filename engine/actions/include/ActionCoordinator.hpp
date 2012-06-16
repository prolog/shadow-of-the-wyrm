#pragma once
#include <map>
#include <string>
#include "ActionCost.hpp"
#include "Creature.hpp"

class ActionCoordinator
{
  public:
    void set(const std::map<std::string, CreaturePtr>& creatures);
    void add(const ActionCost& action_cost, const std::string& creature_id);
    std::string get_next_creature_id_and_update_actions();
    
    bool has_actions() const;

  protected:
    void update_actions();
    std::string get_next_creature_id() const;

    std::multimap<ActionCost, std::string> creature_action_order;
};

typedef std::multimap<ActionCost, std::string>::iterator ActionOrderIterator;
typedef std::multimap<ActionCost, std::string>::const_iterator ActionOrderConstIterator;
