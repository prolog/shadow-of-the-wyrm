#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"
#include "Recipes.hpp"

class RecipesDumper : public StringConverter
{
  public:
    RecipesDumper(CreaturePtr new_creature, const Recipes& new_recipes, const uint new_num_cols);

    std::string str() const override;

  protected:
    CreaturePtr creature;
    Recipes recipes;
    uint num_cols;
};
