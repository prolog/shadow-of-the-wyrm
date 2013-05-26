#pragma once
#include "ReadStrategy.hpp"
#include "Spellbook.hpp"

class ItemIdentifier;

class SpellbookReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable);

  protected:
    void learn_spell_from_spellbook(CreaturePtr creature, SpellbookPtr spellbook, const ItemIdentifier& item_id, const std::string& spell_id, const SkillType magic_category);

    // Check to see if anything bad happens to the creature due to badly
    // bothing the spell learning checks.
    bool handle_fallout_if_necessary(CreaturePtr creature, const int difference);

    // Check to see if the creature has any skill in magic - required to be
    // able to learn spells from spellbooks.
    bool check_magic_skill(CreaturePtr creature);

    // Add a message about the creature not having any knowledge of the Old
    // Runic language.
    void add_no_magic_skill_message();
    
    // Add a message about not being able to learn the spell.
    void add_spell_not_learned_message();

    ActionCostValue get_action_cost_value() const;
};

