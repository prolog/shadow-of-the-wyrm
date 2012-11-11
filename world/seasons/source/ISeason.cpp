#include <boost/foreach.hpp>
#include "ISeason.hpp"
#include "Serialize.hpp"

bool ISeason::operator==(ISeason& season)
{
  return (internal_class_identifier() == season.internal_class_identifier());
}

std::set<Months> ISeason::get_months_in_season() const
{
  return months_in_season;
}

bool ISeason::serialize(std::ostream& stream)
{
  Serialize::write_size_t(stream, months_in_season.size());

  BOOST_FOREACH(Months month, months_in_season)
  {
    Serialize::write_int(stream, month);
  }

  return true;
}

bool ISeason::deserialize(std::istream& stream)
{
  size_t months_size;
  Serialize::read_size_t(stream, months_size);

  months_in_season.clear();

  for (unsigned int i = 0; i < months_size; i++)
  {
    int imonth;
    Serialize::read_int(stream, imonth);
    Months month = static_cast<Months>(imonth);

    months_in_season.insert(month);
  }

  return true;
}
