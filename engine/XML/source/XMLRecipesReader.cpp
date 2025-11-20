#include "XMLRecipesReader.hpp"

using namespace std;

Recipes XMLRecipesReader::get_recipes(const XMLNode& recipes_node)
{
	Recipes recipes;

	if (!recipes_node.is_null())
	{
    vector<XMLNode> recipes_nodes = XMLUtils::get_elements_by_local_name(recipes_node, "Recipe");

    for (const XMLNode& recipe_node : recipes_nodes)
    {
      Recipe r = get_recipe(recipe_node);
      recipes.add(r);
    }
	}

	return recipes;
}

Recipe XMLRecipesReader::get_recipe(const XMLNode& recipe_node)
{
  Recipe r;

  if (!recipe_node.is_null())
  {
    string id = XMLUtils::get_attribute_value(recipe_node, "id");

    XMLNode ingredients_node = XMLUtils::get_next_element_by_local_name(recipe_node, "Ingredients");
    vector<XMLNode> ingredient_nodes = XMLUtils::get_elements_by_local_name(ingredients_node, "Ingredient");
    Ingredients ingrs;

    for (const XMLNode& ingr_node : ingredient_nodes)
    {
      Ingredient i;
      parse_ingredient(ingr_node, i);
      ingrs.push_back(i);
    }

    SkillType skill = static_cast<SkillType>(XMLUtils::get_child_node_int_value(recipe_node, "Skill"));
    int min = XMLUtils::get_child_node_int_value(recipe_node, "Min");
    string make = XMLUtils::get_child_node_value(recipe_node, "Make");
    
    XMLNode properties_node = XMLUtils::get_next_element_by_local_name(recipe_node, "Properties");
    map<string, string> properties;
    parse_properties(properties, properties_node);

    Recipe recipe(id, ingrs, skill, min, make, properties);
    return recipe;
  }

  return r;
}

void XMLRecipesReader::parse_ingredient(const XMLNode& ingredient_node, Ingredient& i)
{
  if (!ingredient_node.is_null())
  {
    string id = XMLUtils::get_child_node_value(ingredient_node, "ID");
    uint quantity = static_cast<uint>(XMLUtils::get_child_node_int_value(ingredient_node, "Quantity", 1));

    i.set_id(id);
    i.set_quantity(quantity);
  }
}