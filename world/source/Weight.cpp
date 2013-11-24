#include <iomanip>
#include <sstream>
#include "Serialize.hpp"
#include "Weight.hpp"

using namespace std;

Weight::Weight()
: ounces(0)
{
}

Weight::~Weight()
{
}

bool Weight::operator==(const Weight& weight) const
{
  return (ounces == weight.ounces);
}

void Weight::set_weight(const uint new_pounds, const uint new_ounces)
{
  ounces = new_ounces + (16 * new_pounds);
}

void Weight::set_weight(const uint new_ounces)
{
  set_weight(0, new_ounces);
}

uint Weight::get_weight() const
{
  return ounces;
}

double Weight::get_weight_in_lbs() const
{
  double weight_in_lbs = ounces / 16;
  return weight_in_lbs;
}

uint Weight::get_weight_in_oz_given_lbs(const uint pounds)
{
  return pounds * 16;
}

std::string Weight::str() const
{
  std::ostringstream weight;

  uint lbs      = (ounces / 16);
  uint extra_oz = (ounces % 16);
  double wgt    = lbs + (extra_oz / 16.0);

  weight << std::setprecision(2) << wgt << "lbs";

  return weight.str();
}

bool Weight::serialize(ostream& stream) const
{
  Serialize::write_uint(stream, ounces);

  return true;
}

bool Weight::deserialize(istream& stream)
{
  Serialize::read_uint(stream, ounces);

  return true;
}

ClassIdentifier Weight::internal_class_identifier() const
{
  return CLASS_ID_WEIGHT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Weight_test.cpp"
#endif

