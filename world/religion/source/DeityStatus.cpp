#include <limits>
#include "DeityStatus.hpp"
#include "ReligionConstants.hpp"
#include "Serialize.hpp"

using namespace std;

DeityStatus::DeityStatus()
: piety(100), champion_type(CHAMPION_TYPE_UNCROWNED)
{
}

DeityStatus::~DeityStatus()
{
}

bool DeityStatus::operator==(const DeityStatus& status) const
{
  bool result = true;

  result = result && (piety == status.piety);
  result = result && (champion_type == status.champion_type);

  return result;
}

void DeityStatus::set_piety(const int new_piety)
{
  piety = new_piety;
}

int DeityStatus::get_piety() const
{
  return piety;
}

// Increment piety, guarding against ADOMish overflow
// by using actual min/max constants.
void DeityStatus::increment_piety(const int inc_amount)
{
  decrement_piety(inc_amount * -1);
}

// Decrement piety, guarding against ADOMish overflow
// by using actual min/max constants.
void DeityStatus::decrement_piety(const int dec_amount)
{
  int new_amount = piety - dec_amount;

  if (new_amount < ReligionConstants::PIETY_MIN)
  {
    new_amount = ReligionConstants::PIETY_MIN;
  }
  else if (new_amount > ReligionConstants::PIETY_MAX)
  {
    new_amount = ReligionConstants::PIETY_MAX;
  }

  piety = new_amount;
}

// Set/get whether the creature is a champion of the deity
void DeityStatus::set_champion_type(const ChampionType new_champion_type)
{
  champion_type = new_champion_type;
}

ChampionType DeityStatus::get_champion_type() const
{
  return champion_type;
}

bool DeityStatus::serialize(ostream& stream) const
{
  Serialize::write_int(stream, piety);
  Serialize::write_enum(stream, champion_type);

  return true;
}

bool DeityStatus::deserialize(istream& stream)
{
  Serialize::read_int(stream, piety);
  Serialize::read_enum(stream, champion_type);

  return true;
}

ClassIdentifier DeityStatus::internal_class_identifier() const
{
  return CLASS_ID_DEITY_STATUS;
}

#ifdef UNIT_TESTS
#include "unit_tests/DeityStatus_test.cpp"
#endif


