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
      Recipe r = parse_recipe(recipe_node);
      recipes.add(r);
    }
	}

	return recipes;
}

Recipe XMLRecipesReader::parse_recipe(const XMLNode& recipe_node)
{
  Recipe r;

  if (!recipe_node.is_null())
  {
    string id = XMLUtils::get_attribute_value(recipe_node, "id");

    // JCD TODO INGREDIENTS!

    SkillType skill = static_cast<SkillType>(XMLUtils::get_child_node_int_value(recipe_node, "Skill"));
    int min = XMLUtils::get_child_node_int_value(recipe_node, "Min");
    string make = XMLUtils::get_child_node_value(recipe_node, "Make");
    
    XMLNode properties_node = XMLUtils::get_next_element_by_local_name(recipe_node, "Properties");
    map<string, string> properties;
    parse_properties(properties, properties_node);

    Recipe recipe(id, {}, skill, min, make, properties);
    return recipe;
  }

  return r;
}