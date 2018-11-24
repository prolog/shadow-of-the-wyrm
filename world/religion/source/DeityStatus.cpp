#include <limits>
#include "DeityStatus.hpp"
#include "ReligionConstants.hpp"
#include "Serialize.hpp"

using namespace std;

DeityStatus::DeityStatus()
: piety(100), piety_regen_bonus(0), champion_type(ChampionType::CHAMPION_TYPE_UNCROWNED)
{
}

DeityStatus::~DeityStatus()
{
}

bool DeityStatus::operator==(const DeityStatus& status) const
{
  bool result = true;

  result = result && (piety == status.piety);
  result = result && (piety_regen_bonus == status.piety_regen_bonus);
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

void DeityStatus::set_piety_regen_bonus(const int new_piety_regen_bonus)
{
  piety_regen_bonus = new_piety_regen_bonus;
}

int DeityStatus::get_piety_regen_bonus() const
{
  return piety_regen_bonus;
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
  Serialize::write_int(stream, piety_regen_bonus);
  Serialize::write_enum(stream, champion_type);

  return true;
}

bool DeityStatus::deserialize(istream& stream)
{
  Serialize::read_int(stream, piety);
  Serialize::read_int(stream, piety_regen_bonus);
  Serialize::read_enum(stream, champion_type);

  return true;
}

ClassIdentifier DeityStatus::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DEITY_STATUS;
}

#ifdef UNIT_TESTS
#include "unit_tests/DeityStatus_test.cpp"
#endif


