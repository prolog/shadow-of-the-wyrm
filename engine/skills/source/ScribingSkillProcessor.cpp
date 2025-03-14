#include "ScribingSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureUtils.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "ItemTypes.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "ScribingCalculator.hpp"
#include "Scroll.hpp"
#include "SkillManager.hpp"
#include "SpellSelectionScreen.hpp"
#include "SpellTransfer.hpp"

using namespace std;

ActionCostValue ScribingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature && map)
  {
    if (check_for_components(creature) &&
        check_for_spells(creature))
    {
      Game& game = Game::instance();
      DisplayPtr display = game.get_display();
      SpellScreenDisplayStrategyPtr sds = std::make_unique<SituationTypeSpellScreenDisplayStrategy>(SpellSituationType::SPELL_SITUATION_INTERNAL);
      SpellSelectionScreen ss(display, creature, sds.get());

      string display_s = ss.display();
      string spell_id = ss.get_selected_spell(display_s.at(0));

      if (!spell_id.empty())
      {
        TilePtr creatures_tile = MapUtils::get_tile_for_creature(map, creature);
        ItemPtr created_scroll = create_scroll(creature, spell_id);

        if (creatures_tile && created_scroll)
        {
          TilePtr creature_tile = MapUtils::get_tile_for_creature(game.get_current_map(), creature);
          creature_tile->get_items()->merge_or_add(created_scroll, InventoryAdditionType::INVENTORY_ADDITION_BACK);

          IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SCRIBING_SCROLL_CREATED));
          manager.send();

          acv = get_default_skill_action_cost_value(creature);
        }
      }
    } 
  }

  return acv;
}

SkillProcessorPtr ScribingSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<ScribingSkillProcessor>();
  return proc;
}

bool ScribingSkillProcessor::check_for_components(CreaturePtr creature)
{
  bool has_comp = false;

  if (creature != nullptr)
  {
    IInventoryPtr inv = creature->get_inventory();

    if (inv &&
      ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_QUILL) &&
      ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_INKPOT) &&
      ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_BLANK_SCROLL))
    {
      has_comp = true;
    }
  }

  if (!has_comp && creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SCRIBING_INSUFFICIENT_COMPONENTS));

    manager.send();
  }

  return has_comp;
}

bool ScribingSkillProcessor::check_for_spells(CreaturePtr creature)
{
  bool has_spells = CreatureUtils::has_spell_for_situation_type(creature, SpellSituationType::SPELL_SITUATION_INTERNAL);

  if (!has_spells && creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SCRIBING_NO_SPELLS));

    manager.send();
  }

  return has_spells;
}

ItemPtr ScribingSkillProcessor::create_scroll(CreaturePtr creature, const string& spell_id)
{
  ItemPtr scroll;

  if (creature)
  {
    Game& game = Game::instance();
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);

    ScribingCalculator sc;
    int cps = sc.calc_castings_per_scroll(creature);

    if (isk.get_castings() < static_cast<uint>(cps))
    {
      if (creature && creature->get_is_player())
      {
        IMessageManager& manager = MMF::instance();
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SCRIBING_INSUFFICIENT_CASTINGS));
        manager.send();
      }
    }
    else
    {
      scroll = ItemManager::create_item(ItemIdKeys::ITEM_ID_TEMPLATE_SCROLL);
      ScrollPtr sscroll = dynamic_pointer_cast<Scroll>(scroll);

      if (sscroll != nullptr)
      {
        const SpellMap& spells = game.get_spells_ref();
        auto s_it = spells.find(spell_id);

        if (s_it != spells.end())
        {
          Spell spell = s_it->second;

          if (spell.get_magic_category() == SkillType::SKILL_MAGIC_DIVINE && !game.do_deities_exist())
          {
            IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_CRAFTING_NO_DEITIES));
            manager.send();

            return nullptr;
          }

          // First, remove the items needed to create the scroll.
          // Quills can be reused over and over.
          ItemManager im;
          auto ink_rem = im.remove_item_from_inv_or_eq(creature, ItemIdKeys::ITEM_ID_INKPOT);
          auto scroll_rem = im.remove_item_from_inv_or_eq(creature, ItemIdKeys::ITEM_ID_BLANK_SCROLL);

          // Next, add the necessary effects, properties, and so on.
          SpellTransfer st;
          st.to_scroll(spell, sscroll);
          sscroll->set_value(spell.get_ap_cost());

          // Now that the scroll is created, reduce the number of spell
          // castings for the creature's memorized spell.
          isk.set_castings(isk.get_castings() - cps);
          creature->get_spell_knowledge_ref().set_spell_knowledge(spell_id, isk);

          // Creating a scroll trains Scribing.
          SkillManager sm;
          sm.mark_skill(creature, SkillType::SKILL_GENERAL_SCRIBING, true);
        }
      }
    }

  }

  return scroll;
}

ActionCostValue ScribingSkillProcessor::get_default_skill_action_cost_value(CreaturePtr /*creature*/) const
{
  return 300;
}
