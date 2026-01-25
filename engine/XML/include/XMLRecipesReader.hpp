#pragma once
#include "Recipes.hpp"
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"

class XMLRecipesReader : public XMLReader
{
  public:
    Recipes get_recipes(const XMLNode& xml_configuration_recipes_node);

  protected:
    Recipe get_recipe(const XMLNode& recipe_node);
    std::vector<Ingredient> get_ingredient(const XMLNode& ingredient_node);
};
