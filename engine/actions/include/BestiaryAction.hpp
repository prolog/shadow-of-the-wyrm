#pragma once
#include "IActionManager.hpp"

// Displays information about a particular creature.
class BestiaryAction : public IActionManager
{
  public:
    ActionCostValue display_creature_information(CreaturePtr creature, const std::string& creature_search_text) const;
    
  protected:
    friend class ActionManager;
    BestiaryAction();

    // Figure out what creature best matches the search text, if anything
    // matches at all.
    CreaturePtr get_bestiary_creature(const std::string& creature_search_text) const;

    // Display the bestiary details.
    void display_bestiary_information(CreaturePtr beast) const;
    
    ActionCostValue get_action_cost_value() const override;
};

