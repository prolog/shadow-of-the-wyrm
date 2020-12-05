#include "GeneralMagicSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

const int GeneralMagicSkillProcessor::PCT_CHANCE_BACKFIRE = 5;

GeneralMagicSkillProcessor::GeneralMagicSkillProcessor()
{
}

ActionCostValue GeneralMagicSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature && map)
  {
    IMessageManager& self_mm = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
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
            acv = incinerate_spellbook(creature, book);
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

ActionCostValue GeneralMagicSkillProcessor::incinerate_spellbook(CreaturePtr creature, SpellbookPtr book)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature != nullptr && book != nullptr)
  {
    acv *= static_cast<int>(book->get_quantity());

    if (RNG::percent_chance(PCT_CHANCE_BACKFIRE))
    {

    }
    else
    {

    }
  }

  return acv;
}

SkillProcessorPtr GeneralMagicSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<GeneralMagicSkillProcessor>();
  return proc;
}

// Books take a while to fully incinerate in magical fire.
ActionCostValue GeneralMagicSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return ActionCostConstants::INCINERATE_SPELLBOOK;
}