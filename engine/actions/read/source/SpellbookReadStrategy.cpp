#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "SpellConstants.hpp"
#include "SpellFailureConsequencesCoordinator.hpp"
#include "SpellbookReadStrategy.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellbookCalculator.hpp"
#include "StatisticsMarker.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"

using namespace std;

ActionCostValue SpellbookReadStrategy::read(CreaturePtr creature, ReadablePtr readable)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature && readable)
  {
    SpellbookPtr spellbook = std::dynamic_pointer_cast<Spellbook>(readable);

    if (spellbook)
    {
      string spell_id = spellbook->get_spell_id();
      const SpellMap spell_map = Game::instance().get_spells_ref();
      SkillType magic_category = SkillType::SKILL_MAGIC_ARCANE;
      SpellMap::const_iterator s_it = spell_map.find(spell_id);

      if (s_it != spell_map.end())
      {
        magic_category = s_it->second.get_magic_category();
      }

      if (check_magic_skill(creature, magic_category))
      {
        if (confirm_reading_if_necessary(creature, spellbook, magic_category))
        {
          ItemIdentifier item_id;
          ItemStatus spellbook_status = spellbook->get_status();
          bool spellbook_destroyed = false;

          SpellbookCalculator sc;

          pair<bool, int> learning_result = sc.learn_spell(creature, magic_category, spellbook->get_difficulty());
          bool spell_learned = learning_result.first;
          int difference = learning_result.second;
          string sound_id;

          if (spell_learned)
          {
            Game& game = Game::instance();
            MapPtr current_map = game.get_current_map();
            Game::instance().get_deity_action_manager_ref().notify_action(creature, current_map, CreatureActionKeys::ACTION_LEARN_SPELL, true);
            learn_spell_from_spellbook(creature, spellbook, item_id, spell_id, magic_category);

            // Reading spellbooks trains intelligence.
            StatisticsMarker sm;
            sm.mark_intelligence(creature);

            // Determine whether the spellbook is destroyed afterwards.
            spellbook_destroyed = sc.get_is_spellbook_destroyed(spellbook_status);

            sound_id = SoundEffectID::SPELL;
          }
          else
          {
            // The creature did not successfully learn the spell.
            // Add a message about reading the (unid'd) spellbook.
            add_read_message(get_player_and_monster_unsuccessful_read_sids(), creature, spellbook, item_id);

            // Add a message about this being unsuccessful.
            if (creature->get_is_player())
            {
              add_spell_not_learned_message(creature);
            }

            // Check the difference to see if it falls within the "something
            // bad happens" realm. (spellbook explodes, big unfriendly creatures
            // summoned, etc.)
            spellbook_destroyed = handle_fallout_if_necessary(creature, difference);

            sound_id = SoundEffectID::MISS;
          }

          Game::instance().get_sound(creature)->play(sound_id);

          if (spellbook_destroyed)
          {
            spellbook->set_quantity(spellbook->get_quantity() - 1);
            if (spellbook->get_quantity() == 0) creature->get_inventory()->remove(spellbook->get_id());

            add_spellbook_destruction_message(creature, spellbook);
          }
        }
      }
    }

    acv = get_action_cost_value(creature);
  }

  return acv;
}

bool SpellbookReadStrategy::add_spell_castings(CreaturePtr creature, const string& spell_id, const int additional_castings)
{
  bool added_castings = false;

  if (creature != nullptr)
  {
    // Update the number of successful castings.
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);
    isk.set_castings(isk.get_castings() + additional_castings);
    sk.set_spell_knowledge(spell_id, isk);

    added_castings = true;
  }

  return added_castings;
}

void SpellbookReadStrategy::learn_spell_from_spellbook(CreaturePtr creature, SpellbookPtr spellbook, const ItemIdentifier& item_id, const string& spell_id, const SkillType magic_category)
{
  SpellbookCalculator sc;

  // The creature successfully learned the spell.
  // Identify the spellbook.
  item_id.set_item_identified(creature, spellbook, spellbook->get_base_id(), true);

  // Add a message about this.
  add_read_message(get_player_and_monster_read_sids(), creature, spellbook, item_id);
  int additional_castings = sc.get_num_castings(creature, magic_category, spellbook->get_status(), spellbook->get_difficulty());
  add_spell_castings(creature, spell_id, additional_castings);
}

// Check to see if the creature can actually read the runes on the page.
bool SpellbookReadStrategy::check_magic_skill(CreaturePtr creature, SkillType magic_category)
{
  bool has_magic_skill = true;

  Skill* magic_skill = creature->get_skills().get_skill(SkillType::SKILL_GENERAL_MAGIC);

  // Cantrips don't need a magic check - they're not written in Old Runic.
  if (magic_skill->get_value() <= 0 && magic_category != SkillType::SKILL_MAGIC_CANTRIPS)
  {
    if (creature->get_is_player())
    {
      add_no_magic_skill_message(creature);
    }

    has_magic_skill = false;
  }

  return has_magic_skill;
}

// If the creature is skilled in the spell's category, automatically return
// true.  Otherwise, prompt the creature to continue reading.
bool SpellbookReadStrategy::confirm_reading_if_necessary(CreaturePtr creature, SpellbookPtr spellbook, const SkillType spell_category)
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
      if (creature && creature->get_is_player())
      {
        // Redraw the screen, since we will have moved from the inventory
        // back to the main map, and need to redraw before the confirmation.
        Game& game = Game::instance();
        game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
        game.get_display()->redraw();
      }

      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature->get_is_player());
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(SpellcastingTextKeys::SPELLCASTING_UNFAMILIAR_CATEGORY));
      confirmation = creature->get_decision_strategy()->get_confirmation();
      
      manager.clear_if_necessary();

      if (spellbook != nullptr)
      {
        mark_spellbook_tried(spellbook);
      }
    }
  }

  return confirmation;
}

// Check to see if anything bad happens as the result of badly failing a
// spell learning check.
//
// Return true if the spellbook is destroyed as a result of the consequences.
bool SpellbookReadStrategy::handle_fallout_if_necessary(CreaturePtr creature, const int difference)
{
  SpellFailureConsequencesCoordinator sfcc;

  return sfcc.coordinate_failure_consequences(creature, difference);
}

void SpellbookReadStrategy::add_no_magic_skill_message(CreaturePtr creature)
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_NO_MAGIC_SKILL));
  manager.send();
}

void SpellbookReadStrategy::add_spell_not_learned_message(CreaturePtr creature)
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_SPELL_NOT_LEARNED));
  manager.send();
}

void SpellbookReadStrategy::add_spellbook_destruction_message(CreaturePtr creature, SpellbookPtr spellbook)
{
  ItemIdentifier item_id;
  IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

  manager.add_new_message(SpellcastingTextKeys::get_spellbook_destruction_message(item_id.get_appropriate_usage_description(spellbook)));
  manager.send();
}

pair<string, string> SpellbookReadStrategy::get_player_and_monster_read_sids() const
{
  pair<string, string> sids(SpellcastingTextKeys::SPELLCASTING_READ_SPELLBOOK_PLAYER, SpellcastingTextKeys::SPELLCASTING_READ_SPELLBOOK_MONSTER);
  return sids;
}

pair<string, string> SpellbookReadStrategy::get_player_and_monster_unsuccessful_read_sids() const
{
  pair<string, string> sids(SpellcastingTextKeys::SPELLCASTING_READ_BOOK_PLAYER, SpellcastingTextKeys::SPELLCASTING_READ_BOOK_MONSTER);
  return sids;
}

bool SpellbookReadStrategy::mark_spellbook_tried(SpellbookPtr spellbook)
{
  bool success = false;
  const ItemMap& items = Game::instance().get_items_ref();

  string base_id;

  if (spellbook != nullptr)
  {
    spellbook->set_additional_property(ItemTextKeys::ITEM_TRIED, std::to_string(true));
    base_id = spellbook->get_base_id();
  }

  auto i_it = items.find(base_id);
  if (i_it != items.end())
  {

    ItemPtr base_item = i_it->second;
    
    if (base_item != nullptr)
    {
      base_item->set_additional_property(ItemTextKeys::ITEM_TRIED, std::to_string(true));
    }

    success = true;
  }

  return success;
}
