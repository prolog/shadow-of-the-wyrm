#include "XMLRecipesReader.hpp"
#include "RNG.hpp"

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
      vector<Ingredient> ingrs_rnd = get_ingredient(ingr_node);
      std::copy(ingrs_rnd.begin(), ingrs_rnd.end(), std::back_inserter(ingrs));
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

vector<Ingredient> XMLRecipesReader::get_ingredient(const XMLNode& ingredient_node)
{
  vector<Ingredient> ingredients;

  if (!ingredient_node.is_null())
  {
    Ingredient ingr;
    string randomization_property = XMLUtils::get_child_node_value(ingredient_node, "Random");
    string id = XMLUtils::get_child_node_value(ingredient_node, "ID");
    XMLNode quantity_node = XMLUtils::get_next_element_by_local_name(ingredient_node, "Quantity");
    Dice quantity = parse_quantity(quantity_node);
    int rand_min = XMLUtils::get_attribute_int_value(ingredient_node, "rand_min", 1);
    int rand_max = XMLUtils::get_attribute_int_value(ingredient_node, "rand_max", 1);

    ingr.set_randomization_property(randomization_property);
    ingr.set_id(id);
    ingr.set_quantity(static_cast<uint>(RNG::dice(quantity)));

    if (rand_min > 0 && rand_max >= rand_min)
    {
      int num_ingr = RNG::range(rand_min, rand_max);

      for (int i = 0; i < num_ingr; i++)
      {
        ingredients.push_back(ingr);
      }
    }
  }

  return ingredients;
}