#include "Conversion.hpp"
#include "ItemDescriber.hpp"
#include "ItemIdentifier.hpp"
#include "ResistancesTranslator.hpp"
#include "StringTable.hpp"

using namespace std;

ItemDescriber::ItemDescriber(ItemPtr new_item)
: item(new_item)
{
}

string ItemDescriber::describe() const
{
  string item_description;

  if (item)
  {
    ItemIdentifier item_id;
    item_description = item_id.get_appropriate_description(item);
    
    uint quantity = item->get_quantity();
    
    // Add quantity as necessary
    if (quantity > 1)
    {
      item_description += " (" + std::to_string(quantity) + ")";
    }

    // Add weight
    item_description += " [" + item->get_total_weight().str() + "]";
  }

  return item_description;
}

string ItemDescriber::describe_usage() const
{
  string item_description;

  if (item)
  {
    ItemIdentifier item_id;
    item_description = item_id.get_appropriate_usage_description(item);

    uint quantity = item->get_quantity();

    // Add quantity
    if (quantity > 1)
    {
      item_description += " (" + std::to_string(quantity) + ")";
    }

    // No need to add weight to the usage description.
  }

  return item_description;
}

string ItemDescriber::describe_resists_and_flags() const
{
  string rf_desc;

  if (item)
  {
    ItemIdentifier item_id;

    if (item_id.get_item_identified(item->get_base_id()))
    {
      ostringstream ss;
      Resistances res = item->get_resistances();

      ResistancesTranslator rt;
      string rt_desc = rt.create_description(res);

      vector<string> flag_sids = item->get_flag_sids();

      if (!rt_desc.empty())
      {
        ss << rt_desc << " ";
      }

      bool has_flags = !flag_sids.empty();

      if (has_flags)
      {
        ss << "(";
        size_t sz = flag_sids.size();

        for (size_t i = 0; i < sz; i++)
        {
          ss << StringTable::get(flag_sids.at(i));

          if (i < sz - 1)
          {
            ss << ", ";
          }
        }

        ss << ")";
      }

      rf_desc = ss.str();
    }
  }

  return rf_desc;
}
