#pragma once
#include <string>
#include "common.hpp"

typedef unsigned int ActionCostValue;

class ActionCost
{
  public:   
    bool operator==(const ActionCost& rhs);
    bool operator!=(const ActionCost& rhs);
    bool operator< (const ActionCost& rhs);
    bool operator> (const ActionCost& rhs);
    bool operator<=(const ActionCost& rhs);
    bool operator>=(const ActionCost& rhs);

    ActionCostValue get_cost() const;
    bool get_turn_advanced() const;
   
    std::string str() const;
   
  protected:
    friend class ActionManager;
    
    ActionCost(const ActionCostValue new_cost);

    ActionCostValue cost;
    bool turn_advanced;
};
