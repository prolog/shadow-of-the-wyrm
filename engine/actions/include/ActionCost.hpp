#pragma once
#include <string>
#include "common.hpp"

class ActionCost
{
  public:   
    bool operator==(const ActionCost& rhs);
    bool operator!=(const ActionCost& rhs);
    bool operator< (const ActionCost& rhs);
    bool operator> (const ActionCost& rhs);
    bool operator<=(const ActionCost& rhs);
    bool operator>=(const ActionCost& rhs);

    std::string get_action_creature_id() const;
    uint get_cost() const;
    bool get_turn_advanced() const;
   
    std::string str() const;
   
  protected:
    friend class IActionManager;
    
    ActionCost(const std::string& new_id, const uint new_cost);

    std::string id;
    int cost;
    bool turn_advanced;
};
