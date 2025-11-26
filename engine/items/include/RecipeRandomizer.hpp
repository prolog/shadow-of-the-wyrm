#pragma once
#include "Recipes.hpp"
#include "Item.hpp"

class RecipeRandomizer 
{
  public:
    RecipeRandomizer();
    virtual ~RecipeRandomizer() = default;

    void randomize(Recipes& recipes, const ItemMap& items);

  protected:
    std::vector<ItemPtr> get_items_with_property(const ItemMap& items, const std::string& property);
};