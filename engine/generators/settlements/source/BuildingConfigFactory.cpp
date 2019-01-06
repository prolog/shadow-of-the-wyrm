#include <map>
#include "BuildingConfigFactory.hpp"
#include "CreatureFeatures.hpp"
#include "ItemTypes.hpp"
#include "RNG.hpp"

using namespace std;

map<ClassIdentifier, vector<pair<string, int>>> BuildingConfigFactory::feature_items;
map<ClassIdentifier, vector<pair<string, int>>> BuildingConfigFactory::feature_creatures;

BuildingConfigFactory::BuildingConfigFactory()
{
  if (feature_items.empty())
  {
    initialize_feature_items();
    initialize_feature_creatures();
  }
}

void BuildingConfigFactory::initialize_feature_items()
{
  feature_items = {{ClassIdentifier::CLASS_ID_BED,            {{ItemIdKeys::ITEM_ID_CLAY_POT, 80},
                                                               {ItemIdKeys::ITEM_ID_QUILL, 10},
                                                               {ItemIdKeys::ITEM_ID_INKPOT, 10},
                                                               {ItemIdKeys::ITEM_ID_BLANK_SCROLL, 5}}},
                   {ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM, {{ItemIdKeys::ITEM_ID_WHITEFLOWER, 100}}},
                   {ClassIdentifier::CLASS_ID_FORGE,          {{ItemIdKeys::ITEM_ID_STEEL_INGOT, 20},
                                                               {ItemIdKeys::ITEM_ID_IRON_INGOT, 80}}},
                   {ClassIdentifier::CLASS_ID_PULPER,         {{ItemIdKeys::ITEM_ID_BLANK_SCROLL, 100},
                                                               {ItemIdKeys::ITEM_ID_QUILL, 80},
                                                               {ItemIdKeys::ITEM_ID_INKPOT, 80}}}};
}

void BuildingConfigFactory::initialize_feature_creatures()
{
  feature_creatures = {{ClassIdentifier::CLASS_ID_BED,            {{CreatureID::CREATURE_ID_COMMONER, 80},
                                                                   {CreatureID::CREATURE_ID_FARMER, 20},
                                                                   {CreatureID::CREATURE_ID_FISHERMAN, 20},
                                                                   {CreatureID::CREATURE_ID_NOBLE, 10},
                                                                   {CreatureID::CREATURE_ID_SMALL_CHILD, 50}}},
                       {ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM,  {{CreatureID::CREATURE_ID_WEAVER, 90}}},
                       {ClassIdentifier::CLASS_ID_FORGE,           {{CreatureID::CREATURE_ID_SMITH, 90}}},
                       {ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH, {{CreatureID::CREATURE_ID_JEWELER, 90}}},
                       {ClassIdentifier::CLASS_ID_PULPER,          {{CreatureID::CREATURE_ID_SCRIBE, 90}}}};
}

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

vector<ClassIdentifier> BuildingConfigFactory::create_house_or_workshop_features(const int pct_chance_ws) const
{
  if (RNG::percent_chance(pct_chance_ws))
  {
    return create_workshop_features();
  }
  else
  {
    return create_house_features();
  }
}

vector<string> BuildingConfigFactory::create_item_ids(const vector<ClassIdentifier>& features) const
{
  vector<string> item_ids;

  for (const auto& ci : features)
  {
    auto item_i = feature_items.find(ci);

    if (item_i != feature_items.end())
    {
      vector<pair<string, int>> item_and_p = item_i->second;

      for (const auto& ip_pair : item_and_p)
      {
        if (RNG::percent_chance(ip_pair.second))
        {
          item_ids.push_back(ip_pair.first);
        }
      }
    }
  }

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

vector<ClassIdentifier> BuildingConfigFactory::create_workshop_features() const
{
  map<ClassIdentifier, int> f_probs = {{ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM, 20}, 
                                       {ClassIdentifier::CLASS_ID_TANNERY, 20},
                                       {ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH, 20},
                                       {ClassIdentifier::CLASS_ID_FORGE, 20},
                                       {ClassIdentifier::CLASS_ID_PULPER, 20}};
  vector<ClassIdentifier> features;

  for (auto f_pair : f_probs)
  {
    if (RNG::percent_chance(f_pair.second))
    {
      features.push_back(f_pair.first);
    }
  }

  if (features.empty())
  {
    features.push_back(ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM);
  }

  return features;
}
