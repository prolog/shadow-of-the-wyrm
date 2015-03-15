#include "InitialItem.hpp"
#include "Serialize.hpp"

using namespace std;

InitialItem::InitialItem()
: item_quantity(1, 1, 0) /* Default amount is 1. */
{
}

InitialItem::InitialItem(const string& new_item_id, const Dice& quant, const vector<pair<string, Dice>>& new_random_ids, const map<string, pair<string, Dice> >& new_racial_ids)
: item_id(new_item_id), item_quantity(quant), random_item_ids(new_random_ids), racial_item_ids(new_racial_ids)
{
}

bool InitialItem::operator==(const InitialItem& ii) const
{
  bool result = true;

  result = result && (item_id == ii.item_id);
  result = result && (item_quantity == ii.item_quantity);
  result = result && (random_item_ids == ii.random_item_ids);
  result = result && (racial_item_ids == ii.racial_item_ids);

  return result;
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

void InitialItem::set_random_item_ids(const vector<pair<string, Dice>>& new_random_item_ids)
{
  random_item_ids = new_random_item_ids;
}

vector<pair<string, Dice>> InitialItem::get_random_item_ids() const
{
  return random_item_ids;
}

void InitialItem::set_racial_item_ids(const map<string, pair<string, Dice>>& new_racial_item_ids)
{
  racial_item_ids = new_racial_item_ids;
}

map<string, pair<string, Dice>> InitialItem::get_racial_item_ids() const
{
  return racial_item_ids;
}

bool InitialItem::serialize(ostream& stream) const
{
  Serialize::write_string(stream, item_id);
  item_quantity.serialize(stream);

  // Random item IDs
  size_t rand_item_id_size = random_item_ids.size();
  Serialize::write_size_t(stream, rand_item_id_size);

  for (const auto& rand_id_pair : random_item_ids)
  {
    Serialize::write_string(stream, rand_id_pair.first);
    rand_id_pair.second.serialize(stream);
  }

  // Racial item IDs
  size_t map_size = racial_item_ids.size();
  Serialize::write_size_t(stream, map_size);

  for (const auto& racial_pair : racial_item_ids)
  {
    Serialize::write_string(stream, racial_pair.first);
    Serialize::write_string(stream, racial_pair.second.first);
    racial_pair.second.second.serialize(stream);
  }

  return true;
}

bool InitialItem::deserialize(istream& stream)
{
  Serialize::read_string(stream, item_id);
  item_quantity.deserialize(stream);

  // Random item IDs
  size_t rand_item_id_size = 0;
  Serialize::read_size_t(stream, rand_item_id_size);
  random_item_ids.clear();

  for (size_t i = 0; i < rand_item_id_size; i++)
  {
    string rand_id;
    Serialize::read_string(stream, rand_id);

    Dice rand_dice;
    rand_dice.deserialize(stream);

    random_item_ids.push_back(make_pair(rand_id, rand_dice));
  }

  // Racial item IDs
  size_t map_size = 0;
  Serialize::read_size_t(stream, map_size);
  racial_item_ids.clear();

  for (size_t i = 0; i < map_size; i++)
  {
    string map_key;
    Serialize::read_string(stream, map_key);

    string pair_key;
    Serialize::read_string(stream, pair_key);

    Dice dice;
    dice.deserialize(stream);

    racial_item_ids.insert(make_pair(map_key, make_pair(pair_key, dice)));
  }

  return true;
}

ClassIdentifier InitialItem::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_INITIAL_ITEM;
}

#ifdef UNIT_TESTS
#include "unit_tests/InitialItem_test.cpp"
#endif