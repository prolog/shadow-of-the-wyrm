#pragma once
#include <map>
#include <string>
#include "ActionCost.hpp"
#include "Creature.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class ActionCoordinator
{
  public:
    void set(const std::map<std::string, CreaturePtr>& creatures);
    void add(const ActionCost& action_cost, const std::string& creature_id);
    void clear();

    ActionCost get_next_action_cost() const;
    std::string get_next_creature_id_and_update_actions();
    
    bool has_actions() const;

  protected:
    void update_actions();
    std::string get_next_creature_id() const;

    std::multimap<ActionCost, std::string> creature_action_order;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & creature_action_order;
    }
};

typedef std::multimap<ActionCost, std::string>::iterator ActionOrderIterator;
typedef std::multimap<ActionCost, std::string>::const_iterator ActionOrderConstIterator;
