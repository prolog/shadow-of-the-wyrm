#pragma once
#include "ReadStrategy.hpp"

// TextReadStrategy is used when scrolls/books have text, but no spells.
// In this case, the text is displayed to the player.
class TextReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable);

  protected:
    virtual std::pair<std::string, std::string> get_player_and_monster_read_sids() const;
    ActionCostValue get_action_cost_value() const;
};
