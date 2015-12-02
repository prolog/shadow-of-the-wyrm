#include "Food.hpp"
#include "ItemProperties.hpp"

using namespace std;

Food::Food()
: Consumable(100,0)
{
  type = ItemType::ITEM_TYPE_FOOD;
  symbol = '%';
}

Food::Food(const int nutr)
: Consumable(nutr,0)
{
  type = ItemType::ITEM_TYPE_FOOD;
  symbol = '%';
}

Food::~Food()
{
}

ItemType Food::get_type() const
{
  return ItemType::ITEM_TYPE_FOOD;
}

void Food::set_seed_item_id(const string& new_seed_item_id)
{
  set_additional_property(ItemProperties::ITEM_PROPERTIES_SEED_ITEM_ID, new_seed_item_id);
}

string Food::get_seed_item_id() const
{
  string item_id;
  auto p_it = additional_properties.find(ItemProperties::ITEM_PROPERTIES_SEED_ITEM_ID);
  
  if (p_it != additional_properties.end())
  {
    item_id = p_it->second;
  }

  return item_id;
}

Item* Food::clone()
{
  return new Food(*this);
}

ClassIdentifier Food::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FOOD;
}

#ifdef UNIT_TESTS
#include "unit_tests/Food_test.cpp"
#endif

