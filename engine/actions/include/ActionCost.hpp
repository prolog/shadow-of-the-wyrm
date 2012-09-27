#pragma once
#include <string>
#include "common.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

typedef int ActionCostValue;

class ActionCost
{
  public:
    // Default constructor sets the cost to 0, disallowing a turn.
    // The ActionManager is responsible for the construction of a
    // "real" ActionCost - see the protected constructor.
    explicit ActionCost();
    
    bool operator==(const ActionCost& rhs) const;
    bool operator!=(const ActionCost& rhs) const;
    bool operator< (const ActionCost& rhs) const;
    bool operator> (const ActionCost& rhs) const;
    bool operator<=(const ActionCost& rhs) const;
    bool operator>=(const ActionCost& rhs) const;

    void set_cost(const ActionCostValue new_cost);
    ActionCostValue get_cost() const;

    bool get_turn_advanced() const;
   
    std::string str() const;
   
  protected:
    friend class ActionManager;
    
    explicit ActionCost(const ActionCostValue new_cost);

    ActionCostValue cost;
    bool turn_advanced;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & cost & turn_advanced;
    }
};
