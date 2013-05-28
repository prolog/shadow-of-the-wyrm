#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "SpellConstants.hpp"
#include "SpellbookReadStrategy.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellbookCalculator.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"

using namespace std;

ActionCostValue SpellbookReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  ActionCostValue acv = 0;

  if (creature && readable)
  {
    SpellbookPtr spellbook = boost::dynamic_pointer_cast<Spellbook>(readable);

    if (spellbook)
    {
      if (check_magic_skill(creature))
      {
        string spell_id = spellbook->get_spell_id();
        const SpellMap spell_map = Game::instance().get_spells_ref();
        SkillType magic_category = SKILL_MAGIC_ARCANE;
        SpellMap::const_iterator s_it = spell_map.find(spell_id);

        if (s_it != spell_map.end())
        {
          magic_category = s_it->second.get_magic_category();
        }

        if (confirm_reading_if_necessary(creature, magic_category))
        {
          ItemIdentifier item_id;
          ItemStatus spellbook_status = spellbook->get_status();
          bool spellbook_destroyed = false;

          SpellbookCalculator sc;

          pair<bool, int> learning_result = sc.learn_spell(creature, magic_category, spellbook->get_difficulty());
          bool spell_learned = learning_result.first;
          int difference = learning_result.second;

          if (spell_learned)
          {
            learn_spell_from_spellbook(creature, spellbook, item_id, spell_id, magic_category);

            // Determine whether the spellbook is destroyed afterwards.
            spellbook_destroyed = sc.get_is_spellbook_destroyed(spellbook_status);
          }
          else
          {
            // The creature did not successfully learn the spell.
            // Add a message about reading the (unid'd) spellbook.
            add_read_message(creature, spellbook, item_id);

            // Add a message about this being unsuccessful.
            if (creature->get_is_player())
            {
              add_spell_not_learned_message();
            }

            // Check the difference to see if it falls within the "something
            // bad happens" realm. (spellbook explodes, big unfriendly creatures
            // summoned, etc.)
            handle_fallout_if_necessary(creature, difference);
          }

          if (spellbook_destroyed)
          {
            spellbook->set_quantity(spellbook->get_quantity() - 1);
            if (spellbook->get_quantity() == 0) creature->get_inventory().remove(spellbook->get_id());
          }
        }
      }
    }

    acv = get_action_cost_value();
  }

  return acv;
}

ActionCostValue SpellbookReadStrategy::get_action_cost_value() const
{
  return 1;
}

void SpellbookReadStrategy::learn_spell_from_spellbook(CreaturePtr creature, SpellbookPtr spellbook, const ItemIdentifier& item_id, const string& spell_id, const SkillType magic_category)
{
  SpellbookCalculator sc;

  // The creature successfully learned the spell.
  // Identify the spellbook.
  item_id.set_item_identified(spellbook, spellbook->get_base_id(), true);

  // Add a message about this.
  add_read_message(creature, spellbook, item_id);

  // Update the number of successful castings.
  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);
  int additional_castings = sc.get_num_castings(creature, magic_category, spellbook->get_status(), spellbook->get_difficulty());
  isk.set_castings(isk.get_castings() + additional_castings);
  sk.set_spell_knowledge(spell_id, isk);
}

// Check to see if the creature can actually read the runes on the page.
bool SpellbookReadStrategy::check_magic_skill(CreaturePtr creature)
{
  bool has_magic_skill = true;

  SkillPtr magic_skill = creature->get_skills().get_skill(SKILL_GENERAL_MAGIC);

  if (magic_skill->get_value() <= 0)
  {
    if (creature->get_is_player())
    {
      add_no_magic_skill_message();
    }

    has_magic_skill = false;
  }

  return has_magic_skill;
}

// If the creature is skilled in the spell's category, automatically return
// true.  Otherwise, prompt the creature to continue reading.
bool SpellbookReadStrategy::confirm_reading_if_necessary(CreaturePtr creature, const SkillType spell_category)
{
  bool confirmation = false;

  if (creature)
  {
    int skill_value = creature->get_skills().get_skill(spell_category)->get_value();

    if (skill_value > 0)
    {
      confirmation = true;
    }
    else
    {
      MessageManager& manager = MessageManager::instance();

      if (creature && creature->get_is_player())
      {
        // Redraw the screen, since we will have moved from the inventory
        // back to the main map, and need to redraw before the confirmation.
        Game& game = Game::instance();
        game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
        game.get_display()->redraw();

        manager.add_new_confirmation_message(TextMessages::get_confirmation_message(SpellcastingTextKeys::SPELLCASTING_UNFAMILIAR_CATEGORY));
      }

      confirmation = creature->get_decision_strategy()->get_confirmation();
      
      manager.clear_if_necessary();
    }
  }

  return confirmation;
}

// Check to see if anything bad happens as the result of badly failing a
// spell learning check.
bool SpellbookReadStrategy::handle_fallout_if_necessary(CreaturePtr creature, const int difference)
{
  bool fallout = true;

  // Many very dangerous creatures are summoned.
  if (difference < SpellConstants::SPELL_FAILURE_SUPER_BAD)
  {
    // JCD FIXME
    return fallout;
  }

  // Spellbook vanishes in a puff of flame, dangerous creatures are summoned,
  // etc.
  if (difference < SpellConstants::SPELL_FAILURE_BAD)
  {
    // JCD FIXME
    return fallout;
  }

  // Spellbook ist kaputt (well, vanishes in a puff of smoke).
  if (difference < SpellConstants::SPELL_FAILURE_MILDLY_BAD)
  {
    // JCD FIXME
    return fallout;
  }

  return false;
}

void SpellbookReadStrategy::add_no_magic_skill_message()
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_NO_MAGIC_SKILL));
  manager.send();
}

void SpellbookReadStrategy::add_spell_not_learned_message()
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_SPELL_NOT_LEARNED));
  manager.send();
}