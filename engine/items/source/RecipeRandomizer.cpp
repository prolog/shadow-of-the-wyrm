#include "RecipeRandomizer.hpp"
#include "RNG.hpp"

using namespace std;

RecipeRandomizer::RecipeRandomizer()
{
}

void RecipeRandomizer::randomize(Recipes& recipes, const ItemMap& items)
{
  RecipesType& recs = recipes.get_recipes_ref();
  std::unordered_map<string, vector<ItemPtr>> property_cache;
  
  for (auto& sr_pair : recs)
  {
    for (auto& si_pair : sr_pair.second)
    {
      map<string, Recipe>& si_recipe = si_pair.second;

      for (auto& rec_pair : si_recipe)
      {
        Ingredients& ingrs = rec_pair.second.get_ingredients_ref();

        for (Ingredient& ingr : ingrs)
        {
          string rand_prop = ingr.get_randomization_property();

          // If the ingredient isn't randomized (no randomization property),
          // leave it alone. Otherwise, set an item ID that works given the
          // property.
          if (!rand_prop.empty())
          {
            // First, check to see if we've built the cache for this
            // property.
            auto p_it = property_cache.find(rand_prop);

            // ... if not, build it.
            if (p_it == property_cache.end())
            {
              property_cache[rand_prop] = get_items_with_property(items, rand_prop);
            }

            // Get a random value from the cache
            vector<ItemPtr> p_items = property_cache[rand_prop];

            // Sanity check
            if (!p_items.empty())
            {
              // Set the ID of the item (this will clear the randomization
              // property).
              ItemPtr item = p_items[RNG::range(0, p_items.size() - 1)];

              if (item != nullptr)
              {
                ingr.set_id_and_property(item->get_base_id(), "");
              }
            }
          }
        }
      }
    }
  }
}

vector<ItemPtr> RecipeRandomizer::get_items_with_property(const ItemMap& items, const string& property)
{
  vector<ItemPtr> items_with_prop;

  for (const auto& it_pair : items)
  {
    ItemPtr i = it_pair.second;

    if (i != nullptr && i->has_additional_property(property))
    {
      items_with_prop.push_back(i);
    }
  }
  return items_with_prop;
}
