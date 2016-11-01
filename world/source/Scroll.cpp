#include "Conversion.hpp"
#include "ItemProperties.hpp"
#include "Scroll.hpp"

using namespace std;

Scroll::Scroll()
{
  type = ItemType::ITEM_TYPE_SCROLL;
  symbol = '?';
}

Scroll::~Scroll()
{
}

// Scrolls are always gone once read, unless blank.
bool Scroll::destroy_on_read() const
{
  bool destroy = String::to_bool(get_additional_property(ItemProperties::ITEM_PROPERTIES_BLANK)) == false;
  return destroy;
}

Item* Scroll::clone()
{
  return new Scroll(*this);
}

ClassIdentifier Scroll::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCROLL;
}

#ifdef UNIT_TESTS
#include "unit_tests/Scroll_test.cpp"
#endif

