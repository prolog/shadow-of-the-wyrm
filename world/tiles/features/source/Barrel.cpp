#include "ActionTextKeys.hpp"
#include "Barrel.hpp"
#include "ItemManager.hpp"
#include "MaterialFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

Barrel::Barrel()
: Feature(MATERIAL_TYPE_WOOD), tap(false)
{
}

Feature* Barrel::clone()
{
  return new Barrel(*this);
}

bool Barrel::operator==(const Barrel& b) const
{
  bool equal = true;

  equal = Feature::operator==(b);

  equal = equal && (tap == b.tap);
  equal = equal && (pour_item_id == b.pour_item_id);

  return equal;
}

// Check to see if the barrel has a tap (if so, it can pour a drink).
// If the barrel has a tap, attempt to pour a drink, creating the item
// on the barrel's tile.
bool Barrel::handle(std::shared_ptr<Tile> tile, std::shared_ptr<Creature> creature)
{
  if (creature && tap)
  {
    if (!pour_item_id.empty())
    {
      ItemPtr item = ItemManager::create_item(pour_item_id);
      if (item != nullptr)
      {
        IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

        IInventoryPtr inv = tile->get_items();
        inv->add(item);

        manager.add_new_message(ActionTextKeys::get_pour_message(creature->get_description_sid(), item->get_usage_description_sid(), creature->get_is_player()));
        manager.send();
      }
    }
  }
  else
  {
  }

  return true;
}

bool Barrel::kick()
{
  return true;
}

uchar Barrel::get_symbol() const
{
  return 'o';
}

string Barrel::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BARREL;
}

ClassIdentifier Barrel::internal_class_identifier() const
{
  return CLASS_ID_BARREL;
}

void Barrel::set_tap(const bool new_tap)
{
  tap = new_tap;
}

bool Barrel::get_tap() const
{
  return tap;
}

void Barrel::set_pour_item_id(const string& new_pour_item_id)
{
  pour_item_id = new_pour_item_id;
}

string Barrel::get_pour_item_id() const
{
  return pour_item_id;
}

bool Barrel::serialize(std::ostream& stream) const
{
  Feature::serialize(stream);
  Serialize::write_bool(stream, tap);
  Serialize::write_string(stream, pour_item_id);

  return true;
}

bool Barrel::deserialize(std::istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_bool(stream, tap);
  Serialize::read_string(stream, pour_item_id);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Barrel_test.cpp"
#endif

