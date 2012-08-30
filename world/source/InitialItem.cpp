#include "InitialItem.hpp"

using namespace std;

InitialItem::InitialItem()
: item_quantity(1, 1, 0) /* Default amount is 1. */
{
}

InitialItem::InitialItem(const string& new_item_id, const Dice& quant, const vector<pair<string, Dice> >& new_random_ids, const map<string, pair<string, Dice> >& new_racial_ids)
: item_id(new_item_id), item_quantity(quant), random_item_ids(new_random_ids), racial_item_ids(new_racial_ids)
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

void InitialItem::set_item_quantity(const Dice& new_quantity)
{
  item_quantity = new_quantity;
}

Dice InitialItem::get_item_quantity() const
{
  return item_quantity;
}

void InitialItem::set_random_item_ids(const vector<pair<string, Dice> >& new_random_item_ids)
{
  random_item_ids = new_random_item_ids;
}

vector<pair<string, Dice> > InitialItem::get_random_item_ids() const
{
  return random_item_ids;
}

void InitialItem::set_racial_item_ids(const map<string, pair<string, Dice> >& new_racial_item_ids)
{
  racial_item_ids = new_racial_item_ids;
}

map<string, pair<string, Dice> > InitialItem::get_racial_item_ids() const
{
  return racial_item_ids;
}

