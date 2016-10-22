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
#include "SpellSelectionScreen.hpp"

using namespace std;

ActionCostValue ScribingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature && map)
  {
    if (check_for_components(creature) &&
        check_for_spells(creature))
    {
      Game& game = Game::instance();
      DisplayPtr display = game.get_display();
      SpellScreenDisplayStrategyPtr sds = std::make_shared<SituationTypeSpellScreenDisplayStrategy>(SpellSituationType::SPELL_SITUATION_INTERNAL);
      SpellSelectionScreen ss(display, creature, sds);

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

          IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SCRIBING_SCROLL_CREATED));
          manager.send();

          acv = get_default_skill_action_cost_value(creature);
        }
      }
    } 
  }

  return acv;
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
    IMessageManager& manager = MM::instance();
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
    IMessageManager& manager = MM::instance();
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
        IMessageManager& manager = MM::instance();
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

          // First, remove the items needed to create the scroll.
          // Quills can be reused over and over.
          ItemManager im;
          im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_INKPOT);
          im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_BLANK_SCROLL);

          // Next, add the necessary effects, properties, and so on.
          sscroll->set_additional_property(ItemProperties::ITEM_PROPERTIES_REPLACEMENT_SID, spell.get_spell_name_sid());
          sscroll->set_effect_type(spell.get_effect());
          sscroll->set_modifier(spell.get_modifier());

          map<string, string> spell_props = spell.get_properties();

          // Set any properties needed by spells that set modifiers, etc.
          for (const auto& s_pair : spell_props)
          {
            sscroll->set_additional_property(s_pair.first, s_pair.second);
          }

          sscroll->set_value(spell.get_ap_cost());

          // Now that the scroll is created, reduce the number of spell
          // castings for the creature's memorized spell.
          isk.set_castings(isk.get_castings() - cps);
          creature->get_spell_knowledge_ref().set_spell_knowledge(spell_id, isk);
        }
      }
    }

  }

  return scroll;
}

ActionCostValue ScribingSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 300;
}
