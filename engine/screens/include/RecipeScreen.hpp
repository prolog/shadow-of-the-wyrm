#pragma once
#include "Creature.hpp"
#include "Display.hpp"
#include "Recipes.hpp"
#include "Screen.hpp"

class RecipeScreen : public Screen
{
  public:
    RecipeScreen(DisplayPtr new_display, const Recipes& new_recipes, CreaturePtr new_creature);

  protected:
    void initialize() override;

    CreaturePtr brewing_creature;
    Recipes recipes;
};
