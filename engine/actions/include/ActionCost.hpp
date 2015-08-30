#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

using ActionCostValue = int;

class ActionCost : public ISerializable
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

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
   
  protected:
    friend class ActionManager;
    friend class SL_Engine_Actions_ActionCostFixture;
    
    explicit ActionCost(const ActionCostValue new_cost);

    ActionCostValue cost;
    bool turn_advanced;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
