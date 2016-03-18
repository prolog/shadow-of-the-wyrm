#include "Amulet.hpp"

using namespace std;

Amulet::Amulet()
{
  type = ItemType::ITEM_TYPE_AMULET;
  symbol = '#';
}

Amulet::~Amulet()
{
}

Item* Amulet::clone()
{
  return new Amulet(*this);
}

ClassIdentifier Amulet::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AMULET;
}

#ifdef UNIT_TESTS
#include "unit_tests/Amulet_test.cpp"
#endif

