#include <sstream>
#include <boost/foreach.hpp>
#include "ActionTextKeys.hpp"
#include "CreatureDescriber.hpp"
#include "DescriberFactory.hpp"
#include "TileDescription.hpp"

using namespace std;

TileDescription::TileDescription(const bool tile, const bool feature, const bool creature, const bool items)
: show_tile(tile), show_feature(feature), show_creature(creature), show_items(items)
{
}

// Get the description for the tile, based on the following:
// - Whether the tile is non-null
// - Whether it contains a creature (with the corresponding option for the bestiary)
// - Whether it contains a feature
// - Whether it contains items
string TileDescription::describe(TilePtr tile, bool tile_is_in_fov)
{
  vector<string> tile_info_strings;

  if (tile)
  {
    // If the tile hasn't been seen (still dark), get a message saying so.
    if (show_tile && !tile->get_viewed())
    {
      tile_info_strings.push_back(StringTable::get(ActionTextKeys::ACTION_LOOK_UNEXPLORED_TILE));      
    }
    // Otherwise, get details from the tile.
    else
    {
      IDescriberPtr describer;
      
      if (show_tile)
      {
        describer = DescriberFactory::create_describer(tile);
        tile_info_strings.push_back(describer->describe());
      }

      if (tile_is_in_fov)
      {
        if (show_feature)
        {
          FeaturePtr feature = tile->get_feature();
          describer = DescriberFactory::create_describer(feature);
          tile_info_strings.push_back(describer->describe());
        }
        
        if (show_creature)
        {
          CreaturePtr creature = tile->get_creature();

          if (creature)
          {
            CreatureDescriber cd(creature);
            string creature_desc = cd.describe_for_tile_selection();
            tile_info_strings.push_back(creature_desc);
          }
        }
        
        if (show_items)
        {
          Inventory& inventory = tile->get_items();
          describer = DescriberFactory::create_describer(inventory);
          tile_info_strings.push_back(describer->describe());
        }
      }
      // If the tile's been explored, but is out of range, add another message.
      else
      {
        if (show_tile)
        {
          tile_info_strings.push_back(StringTable::get(ActionTextKeys::ACTION_LOOK_TILE_OUT_OF_RANGE));
        }
      }
    }
  }

  return format(tile_info_strings);
}

// Format the non-empty strings in the vector.  This is done by concatenating 
// to create one large string, inserting a single space (to separate 
// sentences) between each.  Capitalize/period-ize if necessary.
string TileDescription::format(const vector<string>& tile_info_strings)
{
  ostringstream ss;
  
  BOOST_FOREACH(const string& tile_info_string, tile_info_strings)
  {
    string str = tile_info_string;
    
    if (!str.empty())
    {
      str[0] = toupper(str[0]);
      
      if (str[str.size()-1] != '.')
      {
        str += ".";
      }
      
      ss << str << " ";
    }
  }
  
  return ss.str();
}
