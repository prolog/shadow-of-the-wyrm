#include "WandcraftSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "SpellSelectionScreen.hpp"
#include "Wand.hpp"
#include "WandCalculator.hpp"

using namespace std;

WandcraftSkillProcessor::WandcraftSkillProcessor()
{
}

ActionCostValue WandcraftSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature && map)
  {
    if (check_for_components(creature) &&
        check_for_spells(creature))
    {
      DisplayPtr display = Game::instance().get_display();
      SpellScreenDisplayStrategyPtr sds = std::make_shared<WandcraftSpellScreenDisplayStrategy>();
      SpellSelectionScreen ss(display, creature, sds);

      string display_s = ss.display();
      string spell_id = ss.get_selected_spell(display_s.at(0));

      if (!spell_id.empty())
      {
        Game& game = Game::instance();
        ItemPtr wand = create_wand(creature, spell_id);

        if (wand != nullptr)
        {
          acv = get_default_skill_action_cost_value(creature);

          TilePtr creature_tile = MapUtils::get_tile_for_creature(game.get_current_map(), creature);
          creature_tile->get_items()->merge_or_add(wand, InventoryAdditionType::INVENTORY_ADDITION_BACK);

          IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WANDCRAFT_WAND_CREATED));
          manager.send();
        }
      }
    }
  }

  return acv;
}

bool WandcraftSkillProcessor::check_for_components(CreaturePtr creature)
{
  bool has_comp = false;

  if (creature != nullptr)
  {
    IInventoryPtr inv = creature->get_inventory();

    if (inv &&
        ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_BRANCH) &&
        ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_MAGICI_SHARD))
    {
      has_comp = true;
    }
  }

  if (!has_comp && creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WANDCRAFT_INSUFFICIENT_COMPONENTS));

    manager.send();
  }

  return has_comp;
}

// Only external magics can go into wands.
// External spells are beams, cones, storms, balls.  Ie, not self-targetting
// spells.
bool WandcraftSkillProcessor::check_for_spells(CreaturePtr creature)
{
  bool has_spells = false;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    const SpellMap& sm = game.get_spells_ref();
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    SpellKnowledgeMap skm = sk.get_known_spells();

    for (const auto& skm_pair : skm)
    {
      string spell_id = skm_pair.first;

      const auto sm_it = sm.find(spell_id);
      if (sm_it != sm.end())
      {
        SpellShape ss = sm_it->second.get_shape();

        if (ss.get_is_external())
        {
          has_spells = true;
          break;
        }
      }
    }
  }

  if (!has_spells && creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WANDCRAFT_NO_SPELLS));

    manager.send();
  }

  return has_spells;
}

ItemPtr WandcraftSkillProcessor::create_wand(CreaturePtr creature, const string& spell_id)
{
  ItemPtr created_wand;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    const SpellMap& spells = game.get_spells_ref();
    auto s_it = spells.find(spell_id);

    if (s_it != spells.end())
    {
      WandCalculator wc;
      Spell spell = s_it->second;

      IndividualSpellKnowledge isk = creature->get_spell_knowledge_ref().get_spell_knowledge(spell_id);
      int castings = isk.get_castings();
      int cpc = wc.calc_spell_castings_per_charge(creature);
      int possible_charges = castings / cpc;
      int num_charges = wc.calc_num_charges(creature);

      if (possible_charges < num_charges)
      {
        num_charges = possible_charges;
      }

      int casting_cost = num_charges * cpc;

      // Remove a branch and magici shard.
      // Create a template wand, and populate it properly.
      ItemManager im;
      im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_BRANCH);
      im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_MAGICI_SHARD);

      ItemPtr iwand = ItemManager::create_item(ItemIdKeys::ITEM_ID_TEMPLATE_WAND);
      WandPtr wand = dynamic_pointer_cast<Wand>(iwand);

      if (wand != nullptr)
      {
        if (spell.get_has_damage())
        {
          wand->set_damage(spell.get_damage());
        }

        wand->set_additional_property(ItemProperties::ITEM_PROPERTIES_REPLACEMENT_SID, spell.get_spell_name_sid());
        wand->set_effect_type(spell.get_effect());
        wand->set_charges(num_charges);

        // JCD FIXME testing!  Fix the value!
        // TODO: Confirmation?
        wand->set_value(10 * wand->get_charges().get_current());

        created_wand = wand;

        // Reduce the spell knowledge.
        isk.set_castings(isk.get_castings() - casting_cost);
        creature->get_spell_knowledge_ref().set_spell_knowledge(spell_id, isk);
      }
    }
  }

  return created_wand;
}

ActionCostValue WandcraftSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 200;
}

