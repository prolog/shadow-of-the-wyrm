
#include "ActionTextKeys.hpp"
#include "BrewingCalculator.hpp"
#include "CauldronManipulator.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"
#include "RecipeScreen.hpp"
#include "RNG.hpp"

using namespace std;

CauldronManipulator::CauldronManipulator(FeaturePtr feature) 
: DefaultFeatureManipulator(feature)
{
}

void CauldronManipulator::strike(CreaturePtr creature, MapPtr /*current_map*/, TilePtr /*feature_tile*/, const Coordinate& /*feature_coord*/, FeaturePtr /*feature*/, ItemPtr /* item */)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_STRIKE_CAULDRON));
    manager.send();
  }
}

// Manipulating a cauldron allows the character to brew any recipes they know.
bool CauldronManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool brewed = false;
  Game& game = Game::instance();
  Recipes& recipes = game.get_recipes_ref();
  vector<Recipe> brewable_recipes = recipes.get_recipes(creature);

  if (brewable_recipes.empty())
  {
    add_nothing_brewable_message(creature);
  }
  else
  {
    DisplayPtr display = game.get_display();
    RecipeScreen rs(display, recipes, creature);
    string rec_s = rs.display();
    char sel_c = static_cast<char>(Char::keyboard_selection_char_to_int(rec_s.at(0)));
    OptionPtr option = rs.get_option(sel_c);

    if (option != nullptr && option->get_enabled())
    {
      string recipe_id = option->get_external_id();
      Recipe r = recipes.get_recipe(recipe_id);
      brewed = brew(creature, tile, r);
    }
  }

  return brewed;
}

bool CauldronManipulator::brew(CreaturePtr creature, TilePtr tile, const Recipe& r)
{
  bool brewed = false;

  if (!r.get_id().empty())
  {
    ItemPtr item = ItemManager::create_item(r.get_item_id());

    // Set the quantity based on the apothecary's skill.
    BrewingCalculator bc;
    if (RNG::percent_chance(bc.calc_pct_chance_additional_potion(creature)))
    {
      item->set_quantity(2);
    }

    // Likewise, the item status. Get the chance for each status, and then
    // check them in ascending order, setting the status each time the chance
    // is hit.
    map<ItemStatus, int> item_statuses_pct_chance = bc.calc_item_status_pct_chance(creature);
    for (const auto& st : { ItemStatus::ITEM_STATUS_CURSED, ItemStatus::ITEM_STATUS_UNCURSED, ItemStatus::ITEM_STATUS_BLESSED })
    {
      if (RNG::percent_chance(item_statuses_pct_chance[st]))
      {
        item->set_status(st);
      }
    }

    if (item != nullptr)
    {
      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BREWING_COMBINE_INGREDIENTS));
      manager.send();

      // Remove the items from the inventory.
      vector<ItemPtr> removed = creature->get_inventory()->remove_and_return(r.get_ingredients());
      
      for (ItemPtr rem : removed)
      {
        if (rem && rem->get_glowing())
        {
          item->set_glowing(true);
          break;
        }
      }

      // Create the potable and add it to the cauldron tile.
      tile->get_items()->merge_or_add(item);
      brewed = true;
    }
  }

  return brewed;
}

void CauldronManipulator::add_nothing_brewable_message(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BREWING_NO_INGREDIENTS));
    manager.send();
  }
}