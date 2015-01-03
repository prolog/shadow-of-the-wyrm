#include "FieldTileConfiguration.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"

using namespace std;

FieldTileConfiguration::FieldTileConfiguration()
{
  initialize_additional_flora_map();
}

void FieldTileConfiguration::configure(TilePtr tile, const Season season) const
{
  bool created_rock = ItemManager::create_item_with_probability(1, 200, tile->get_items(), ItemIdKeys::ITEM_ID_ROCK);

  if (!created_rock)
  {
    auto fl_it = flora_map.find(season);

    if (fl_it != flora_map.end())
    {
      auto item_vec = fl_it->second;

      for (const pair<pair<int, int>, string>& item_details : item_vec)
      {
        pair<int, int> x_y = item_details.first;
        string item_id = item_details.second;

        bool x_y_chance = RNG::x_in_y_chance(x_y.first, x_y.second);

        if (x_y_chance)
        {
          bool created = ItemManager::create_item_with_probability(1, 1, tile->get_items(), item_id);

          // Only create one additional item per tile.
          if (created)
          {
            return;
          }
        }
      }
    }
  }
}

void FieldTileConfiguration::initialize_additional_flora_map()
{
  vector<pair<pair<int, int>, string>> summer_p_map = { { {1, 1000}, "_wildflower_1" }, 
                                                        { {1, 1000}, "_wildflower_2" }, 
                                                        { {1, 1000}, "_wildflower_3"}, 
                                                        { {1, 1000}, "_wildflower_4"}, 
                                                        { {1, 1000}, "_wildflower_5"}, 
                                                        { {1, 1000}, "_wildflower_6"},
                                                        { {1, 2500}, "_whiteflower" } };

  flora_map = AdditionalFloraMap{ {Season::SEASON_SUMMER, summer_p_map} };
}