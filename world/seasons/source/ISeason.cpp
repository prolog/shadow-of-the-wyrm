#include "ISeason.hpp"
#include "Serialize.hpp"

using namespace std;

bool ISeason::operator==(ISeason& season) const
{
  return (internal_class_identifier() == season.internal_class_identifier());
}

std::set<Months> ISeason::get_months_in_season() const
{
  return months_in_season;
}

std::map<TileType, std::vector<std::string>> ISeason::get_foragables() const
{
  return foragables;
}

bool ISeason::serialize(std::ostream& stream) const
{
  Serialize::write_size_t(stream, months_in_season.size());

  for (const Months month : months_in_season)
  {
    Serialize::write_enum(stream, month);
  }

  Serialize::write_size_t(stream, foragables.size());

  for (const auto& foragables_pair : foragables)
  {
    Serialize::write_enum(stream, foragables_pair.first);
    Serialize::write_string_vector(stream, foragables_pair.second);
  }

  return true;
}

bool ISeason::deserialize(std::istream& stream)
{
  size_t months_size = 0;
  Serialize::read_size_t(stream, months_size);

  months_in_season.clear();

  for (size_t i = 0; i < months_size; i++)
  {
    int imonth;
    Serialize::read_int(stream, imonth);
    Months month = static_cast<Months>(imonth);

    months_in_season.insert(month);
  }

  size_t foragables_size = 0;
  Serialize::read_size_t(stream, foragables_size);

  for (size_t i = 0; i < foragables_size; i++)
  {
    TileType tile_type = TileType::TILE_TYPE_UNDEFINED;
    Serialize::read_enum(stream, tile_type);

    vector<string> tile_foragables;
    Serialize::read_string_vector(stream, tile_foragables);

    foragables[tile_type] = tile_foragables;
  }

  return true;
}
