#include <sstream>
#include <boost/foreach.hpp>
#include "DescriberFactory.hpp"
#include "TileDescription.hpp"

using namespace std;

// Get the description for the tile, based on the following:
// - Whether the tile is non-null
// - Whether it contains a creature
// - Whether it contains a feature
// - Whether it contains items
string TileDescription::describe(TilePtr tile, bool tile_is_in_fov)
{
  vector<string> tile_info_strings;

  if (tile)
  {
    // If the tile hasn't been seen (still dark), get a message saying so.
    if (!tile->get_viewed())
    {
      tile_info_strings.push_back(StringTable::get(ActionTextKeys::ACTION_LOOK_UNEXPLORED_TILE));      
    }
    // Otherwise, get details from the tile.
    else
    {
      IDescriberPtr describer = DescriberFactory::create_describer(tile);
      tile_info_strings.push_back(describer->describe());

      if (tile_is_in_fov)
      {
        FeaturePtr feature = tile->get_feature();
        describer = DescriberFactory::create_describer(feature);
        tile_info_strings.push_back(describer->describe());
        
        CreaturePtr creature = tile->get_creature();
        describer = DescriberFactory::create_describer(creature);
        tile_info_strings.push_back(describer->describe());
        
        Inventory& inventory = tile->get_items();
        describer = DescriberFactory::create_describer(inventory);
        tile_info_strings.push_back(describer->describe());
      }
      // If the tile's been explored, but is out of range, add another message.
      else
      {
        tile_info_strings.push_back(StringTable::get(ActionTextKeys::ACTION_LOOK_TILE_OUT_OF_RANGE));
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
