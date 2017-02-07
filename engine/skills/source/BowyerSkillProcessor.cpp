#include "ActionTextKeys.hpp"
#include "BowyerSkillProcessor.hpp"
#include "CreateItemScreen.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

ActionCostValue BowyerSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = 0;

  if (creature != nullptr && map != nullptr)
  {
    acv = get_default_skill_action_cost_value(creature);

    if (check_for_bough(creature))
    {
      Game& game = Game::instance();
      DisplayPtr cur_disp = game.get_display();

      CreateItemScreen cis(cur_disp, SkillType::SKILL_GENERAL_BOWYER);
//      string created_item_id = cis.display();
    }
  }

  return acv;
}

bool BowyerSkillProcessor::check_for_bough(CreaturePtr creature)
{
  bool has_bough = false;

  if (creature != nullptr)
  {
    ItemPtr bough = creature->get_inventory()->get_from_base_id(ItemIdKeys::ITEM_ID_BOUGH);

    if (bough != nullptr)
    {
      has_bough = true;
    }
  }

  if (has_bough == false)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BOWYER_INSUFFICIENT_COMPONENTS));
    manager.send();
  }

  return has_bough;
}