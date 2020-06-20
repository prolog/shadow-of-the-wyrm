#include "Conversion.hpp"
#include "ItemDescriber.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTextKeys.hpp"
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
    ostringstream ss;

    ItemIdentifier item_id;
    ss << item_id.get_appropriate_description(item);
    ss << describe_tried();
    ss << describe_quantity_and_value();

    // Add weight
    ss << " [" << item->get_total_weight().str() << "]";
    item_description = ss.str();
  }

  return item_description;
}

string ItemDescriber::describe_usage() const
{
  string item_description;

  if (item)
  {
    ostringstream ss;

    ItemIdentifier item_id;
    ss << item_id.get_appropriate_usage_description(item);
    ss << describe_quantity_and_value();

    // No need to add weight to the usage description.
    item_description = ss.str();
  }

  return item_description;
}

string ItemDescriber::describe_tried() const
{
  ostringstream ss;

  if (item && String::to_bool(item->get_additional_property(ItemTextKeys::ITEM_TRIED)))
  {
    ss << " " << StringTable::get(ItemTextKeys::ITEM_TRIED);
  }

  return ss.str();
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
      ResistancesDisplayOptions rdo(true, true);
      string rt_desc = rt.create_description(res, rdo);

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

string ItemDescriber::describe_quantity_and_value() const
{
  ostringstream ss;
  vector<string> quantity_and_unpaid_value;

  uint quantity = item->get_quantity();

  // Add quantity as necessary
  if (quantity > 1)
  {
    quantity_and_unpaid_value.push_back(std::to_string(quantity));
  }

  // If this is from a shop, and unpaid, add the necessary info.
  if (item->get_unpaid())
  {
    quantity_and_unpaid_value.push_back(ItemTextKeys::get_value(item->get_total_value()));
  }

  if (!quantity_and_unpaid_value.empty())
  {
    ss << " (";

    for (size_t i = 0; i < quantity_and_unpaid_value.size(); i++)
    {
      string cur = quantity_and_unpaid_value.at(i);
      ss << cur;

      if (i != quantity_and_unpaid_value.size() - 1)
      {
        ss << "; ";
      }
    }

    ss << ")";
  }

  return ss.str();
}