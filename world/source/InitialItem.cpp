#include "InitialItem.hpp"

using namespace std;

InitialItem::InitialItem()
{
}

InitialItem::InitialItem(const string& new_item_id, const vector<string>& new_random_ids, const map<string, string>& new_racial_ids)
: item_id(new_item_id), random_item_ids(new_random_ids), racial_item_ids(new_racial_ids)
{
}

void InitialItem::set_item_id(const string& new_item_id)
{
  item_id = new_item_id;
}

string InitialItem::get_item_id() const
{
  return item_id;
}

void InitialItem::set_random_item_ids(const vector<string>& new_random_item_ids)
{
  random_item_ids = new_random_item_ids;
}

vector<string> InitialItem::get_random_item_ids() const
{
  return random_item_ids;
}

void InitialItem::set_racial_item_ids(const map<string, string>& new_racial_item_ids)
{
  racial_item_ids = new_racial_item_ids;
}

map<string, string> InitialItem::get_racial_item_ids() const
{
  return racial_item_ids;
}

