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
      recipes[r.get_skill()][r.get_skill_required()].push_back(r);
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
  }

  return r;
}