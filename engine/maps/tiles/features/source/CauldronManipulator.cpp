#include "CauldronManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "RecipeScreen.hpp"

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
bool CauldronManipulator::handle(TilePtr /*tile*/, CreaturePtr creature)
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
    string d = rs.display();
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