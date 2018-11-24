#include <map>
#include "BuildingConfigFactory.hpp"
#include "ItemTypes.hpp"
#include "RNG.hpp"

using namespace std;

// Shops have no features in them, they're just empty space filled with items.
vector<ClassIdentifier> BuildingConfigFactory::create_shop_features() const
{
  vector<ClassIdentifier> features;
  return features;
}

// Shops have nothing in them that aren't for sale.
vector<string> BuildingConfigFactory::create_shop_item_ids() const
{
  vector<string> item_ids;
  return item_ids;
}

vector<ClassIdentifier> BuildingConfigFactory::create_house_features() const
{
  map<ClassIdentifier, int> f_probs = {{ClassIdentifier::CLASS_ID_BED, 80}, 
                                       {ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM, 10}, 
                                       {ClassIdentifier::CLASS_ID_BENCH, 15},
                                       {ClassIdentifier::CLASS_ID_TABLE, 30}};
  vector<ClassIdentifier> features;

  for (auto f_pair : f_probs)
  {
    if (RNG::percent_chance(f_pair.second))
    {
      features.push_back(f_pair.first);
    }
  }

  return features;
}

vector<string> BuildingConfigFactory::create_house_item_ids() const
{
  map<string, int> i_probs = {{ItemIdKeys::ITEM_ID_CLAY_POT, 80}, 
                              {ItemIdKeys::ITEM_ID_INKPOT, 10},
                              {ItemIdKeys::ITEM_ID_MAGICI_SHARD, 5}};
  vector<string> item_ids;

  for (auto i_pair : i_probs)
  {
    if (RNG::percent_chance(i_pair.second))
    {
      item_ids.push_back(i_pair.first);
    }
  }

  return item_ids;  
}