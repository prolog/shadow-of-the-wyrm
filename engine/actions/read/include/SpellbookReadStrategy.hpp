#pragma once
#include "ReadStrategy.hpp"

class SpellbookReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable);

    // Check to see if the creature has any skill in magic - required to be
    // able to learn spells from spellbooks.
    bool check_magic_skill(CreaturePtr creature);

    // Add a message about the creature not having any knowledge of the Old
    // Runic language.
    void add_no_magic_skill_message();

  protected:
    ActionCostValue get_action_cost_value() const;
};

