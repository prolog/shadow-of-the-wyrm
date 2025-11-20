#pragma once
#include "Recipes.hpp"
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"

class XMLRecipesReader : public XMLReader
{
  public:
    Recipes get_recipes(const XMLNode& xml_configuration_recipes_node);

  protected:
    Recipe parse_recipe(const XMLNode& recipe_node);
};
