#include "SpringsTile.hpp"
#include "MovementTextKeys.hpp"
#include "Serialize.hpp"
#include "WaterInventory.hpp"
#include "WaterTypes.hpp"

using namespace std;

SpringsTile::SpringsTile()
: temperature(static_cast<int>(SpringsTemperature::SPRINGS_TEMPERATURE_COOL))
{
  items = std::make_shared<WaterInventory>();
}

bool SpringsTile::operator==(const SpringsTile& sp) const
{
  bool result = Tile::operator==(sp);

  result = result && (temperature == sp.temperature);

  return result;
}

TileType SpringsTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SPRINGS;
}

TileSuperType SpringsTile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_WATER;
}

WaterType SpringsTile::get_water_type() const
{
  return WaterType::WATER_TYPE_FRESH;
}

std::string SpringsTile::get_tile_description_sid() const
{
  if (temperature >= static_cast<int>(SpringsTemperature::SPRINGS_TEMPERATURE_HOT))
  {
    return TileTextKeys::TILE_DESC_HOT_SPRINGS;
  }
  else
  {
    return TileTextKeys::TILE_DESC_SPRINGS;
  }
}

std::string SpringsTile::get_no_exit_down_message_sid() const
{
  return MovementTextKeys::ACTION_MOVE_NO_EXIT_DOWN_SPRINGS;
}

void SpringsTile::set_temperature(const int new_temperature)
{
  temperature = new_temperature;
}

int SpringsTile::get_temperature() const
{
  return temperature;
}

Tile* SpringsTile::clone()
{
  return new SpringsTile(*this);
}

bool SpringsTile::serialize(ostream& stream) const
{
  Tile::serialize(stream);
  Serialize::write_int(stream, temperature);

  return true;
}

bool SpringsTile::deserialize(istream& stream)
{
  Tile::deserialize(stream);
  Serialize::read_int(stream, temperature);

  return true;
}

ClassIdentifier SpringsTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SPRINGS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpringsTile_test.cpp"
#endif
