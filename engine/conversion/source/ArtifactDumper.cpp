#include <sstream>
#include "ArtifactDumper.hpp"
#include "Conversion.hpp"
#include "ItemDumper.hpp"
#include "TextKeys.hpp"

using namespace std;

ArtifactDumper::ArtifactDumper(const ItemMap& new_item_map, const GenerationValuesMap& new_igv_map, const uint new_num_cols)
: item_map(new_item_map), igv_map(new_igv_map), num_cols(new_num_cols)
{
}

// Loop through all the items in the game, and display info for artifacts.
string ArtifactDumper::str() const
{
  ostringstream ss;
  
  ss << String::centre(StringTable::get(TextKeys::GENERATED_ARTIFACTS), num_cols) << endl << endl;
  ss << get_artifacts() << endl;
  ss << endl;
  
  return ss.str();
}

string ArtifactDumper::get_artifacts() const
{
  ostringstream ss;

  for (const auto& item_pair : item_map)
  {
    ItemPtr item = item_pair.second;

    if (item != nullptr && item->get_artifact())
    {
      auto igv_it = igv_map.find(item->get_base_id());

      // Ensure we only show artifacts that have already been generated.
      if (igv_it != igv_map.end() && igv_it->second.is_maximum_reached())
      {
        ItemDumper item_dumper(nullptr, item, false);

        // Ignore blindness checks because we're checking on globally generated
        // values, not what's in the creature's equipment or inventory.
        item_dumper.set_ignore_blindness_checks(true);

        ss << item_dumper.str();
      }
    }
  }
  
  return ss.str();
}
