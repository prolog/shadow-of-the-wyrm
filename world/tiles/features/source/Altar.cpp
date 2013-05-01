#include "Altar.hpp"
#include "Serialize.hpp"

using namespace std;

Altar::Altar(const std::string& new_deity_id, const MaterialType new_material)
: Feature(new_material), deity_id(new_deity_id)
{
}

bool Altar::operator==(const Altar& altar) const
{
  bool result = Feature::operator==(altar);

  result = result && (deity_id == altar.deity_id);

  return result;
}

string Altar::get_deity_id() const
{
  return deity_id;
}

bool Altar::can_offer() const
{
  return true;
}

bool Altar::handle()
{
  return offer();
}

bool Altar::kick()
{
  // Bad things happen.
  return true;
}

bool Altar::offer()
{
  // Good things happen.
  return true;
}

uchar Altar::get_symbol() const
{
  return '_';
}

bool Altar::serialize(ostream& stream)
{
  Feature::serialize(stream);
  Serialize::write_string(stream, deity_id);

  return true;
}

bool Altar::deserialize(istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_string(stream, deity_id);

  return true;
}

ClassIdentifier Altar::internal_class_identifier() const
{
  return CLASS_ID_ALTAR;
}

#ifdef UNIT_TESTS
#include "unit_tests/AllAltars_test.cpp"
#endif

