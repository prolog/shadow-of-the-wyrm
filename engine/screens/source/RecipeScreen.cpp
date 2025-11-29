#include "RecipeScreen.hpp"

RecipeScreen::RecipeScreen(DisplayPtr new_display, const Recipes& new_recipes, CreaturePtr new_creature)
: Screen(new_display), recipes(new_recipes), brewing_creature(new_creature)
{
}

void RecipeScreen::initialize()
{
  // ...
}