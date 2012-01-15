#include <iomanip>
#include <sstream>
#include "Weight.hpp"

Weight::Weight()
: ounces(0)
{
}

Weight::~Weight()
{
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

std::string Weight::str() const
{
  std::ostringstream weight;

  uint lbs      = (ounces / 16);
  uint extra_oz = (ounces % 16);
  double wgt    = lbs + (extra_oz / 16.0);

  weight << std::setprecision(2) << wgt << "lbs";

  return weight.str();
}
