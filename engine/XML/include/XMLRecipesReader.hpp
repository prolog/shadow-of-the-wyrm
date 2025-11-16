#pragma once
#include "Recipe.hpp"
#include "XMLDataStructures.hpp"

class XMLRecipesReader
{
  public:
    Recipes get_recipes(const XMLNode& xml_configuration_recipes_node);

  protected:
    Recipe parse_recipe(const XMLNode& recipe_node);
};
