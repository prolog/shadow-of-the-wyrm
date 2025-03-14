#include "GeneralMagicSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "DeathSourceTextKeys.hpp"
#include "EtherEffect.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SpellbookCalculator.hpp"

using namespace std;

GeneralMagicSkillProcessor::GeneralMagicSkillProcessor()
{
}

ActionCostValue GeneralMagicSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature && map)
  {
    IMessageManager& self_mm = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    bool has_spellbooks = creature->get_inventory()->has_item_type(ItemType::ITEM_TYPE_SPELLBOOK);

    if (has_spellbooks)
    {
      list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_type_filter(ItemType::ITEM_TYPE_SPELLBOOK);
      ItemPtr selected = Game::instance().get_action_manager_ref().inventory(creature, creature->get_inventory(), display_filter_list, {}, false, false);

      if (selected != nullptr)
      {
        SpellbookPtr book = std::dynamic_pointer_cast<Spellbook>(selected);

        if (book != nullptr)
        {
          int book_ap = 0;
          string spell_id = book->get_spell_id();

          if (!spell_id.empty())
          {
            Game& game = Game::instance();
            const SpellMap& spells = game.get_spells_ref();

            auto s_it = spells.find(spell_id);

            if (s_it != spells.end())
            {
              book_ap = s_it->second.get_ap_cost() * book->get_quantity();
            }
          }

          if (book_ap > 0)
          {
            if (creature->get_arcana_points().get_full())
            {
              self_mm.add_new_message(StringTable::get(ActionTextKeys::ACTION_INCINERATE_FULL_AP));
              self_mm.send();
            }
            else
            {
              acv = incinerate_spellbook(creature, book, book_ap);
            }
          }
          else
          {
            self_mm.add_new_message(StringTable::get(ActionTextKeys::ACTION_INCINERATE_NO_AP));
            self_mm.send();
          }
        }
      }
    }
    else
    {
      self_mm.add_new_message(StringTable::get(ActionTextKeys::ACTION_INCINERATE_NO_SPELLBOOKS));
      self_mm.send();
    }
  }

  return acv;
}

ActionCostValue GeneralMagicSkillProcessor::incinerate_spellbook(CreaturePtr creature, SpellbookPtr book, const int book_ap)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature != nullptr && book != nullptr)
  {
    Game& game = Game::instance();

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    ItemIdentifier iid;
    string item_usage_desc_sid = iid.get_appropriate_usage_description(book);

    SpellbookCalculator sc;

    if (RNG::percent_chance(sc.calculate_pct_chance_wild_incineration(book->get_quantity())))
    {
      manager.add_new_message(ActionTextKeys::get_incinerate_spellbook_wild_message(item_usage_desc_sid));
      manager.send();

      CombatManager cm;
      int damage_dealt = RNG::range(1, book_ap);
      Damage dmg;
      dmg.set_num_dice(1);
      dmg.set_dice_sides(damage_dealt);
      dmg.set_damage_type(DamageType::DAMAGE_TYPE_ARCANE);

      cm.deal_damage(nullptr, creature, AttackType::ATTACK_TYPE_MAGICAL, "", damage_dealt, dmg, "", DeathSourceTextKeys::DEATH_SOURCE_INCINERATION);
    }
    else
    {
      int ap_gained = sc.get_ap_amount(book_ap, creature);
      string ap_gained_s = to_string(ap_gained);

      EtherEffect ether;
      map<string, string> properties = {{EtherEffect::HEALING_MIN, ap_gained_s}, {EtherEffect::HEALING_MAX, ap_gained_s}};

      ether.read_properties(properties);
      ether.clear_additional_effect_messages();
      ether.effect(creature, &game.get_action_manager_ref(), book->get_status(), {}, nullptr);

      manager.add_new_message(ActionTextKeys::get_incinerate_spellbook_message(item_usage_desc_sid));
      manager.send();
    }

    creature->get_inventory()->remove(book->get_id());
  }

  return acv;
}

SkillProcessorPtr GeneralMagicSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<GeneralMagicSkillProcessor>();
  return proc;
}

// Books take a while to fully incinerate in magical fire.
ActionCostValue GeneralMagicSkillProcessor::get_default_skill_action_cost_value(CreaturePtr /*creature*/) const
{
  return ActionCostConstants::INCINERATE_SPELLBOOK;
}