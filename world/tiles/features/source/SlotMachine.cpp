#include "global_prototypes.hpp"
#include "SlotMachine.hpp"
#include "MaterialFactory.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

SlotMachine::SlotMachine(const Symbol& new_symbol, const MaterialType material, const int new_cost, const int new_pct_chance_win, const float new_payout_multiplier)
: Feature(material, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol),
cost(new_cost),
pct_chance_win(new_pct_chance_win),
payout_multiplier(new_payout_multiplier)
{
}

SlotMachine::SlotMachine(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), cost(1), pct_chance_win(0), payout_multiplier(0.0f)
{
}

SlotMachine::SlotMachine(const Symbol& new_symbol, const MaterialType material_type)
: Feature(material_type, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol),
cost(1), pct_chance_win(0), payout_multiplier(0.0f)
{
}

bool SlotMachine::operator==(const SlotMachine& sm) const
{
  bool result = Feature::operator==(sm);

  result = result && (cost == sm.cost);
  result = result && (pct_chance_win == sm.pct_chance_win);
  result = result && fequal(payout_multiplier, sm.get_payout_multiplier());

  return result;
}

void SlotMachine::set_cost(const int new_cost)
{
  cost = new_cost;
}

int SlotMachine::get_cost() const
{
  return cost;
}

void SlotMachine::set_pct_chance_win(const int new_pct_chance_win)
{
  pct_chance_win = new_pct_chance_win;
}

int SlotMachine::get_pct_chance_win() const
{
  return pct_chance_win;
}

void SlotMachine::set_payout_multiplier(const float new_payout_multiplier)
{
  payout_multiplier = new_payout_multiplier;
}

float SlotMachine::get_payout_multiplier() const
{
  return payout_multiplier;
}

Colour SlotMachine::get_colour() const
{
  return static_cast<Colour>(RNG::range(static_cast<int>(Colour::COLOUR_BOLD_RED), static_cast<int>(Colour::COLOUR_BOLD_WHITE)));
}

Feature* SlotMachine::clone()
{
  return new SlotMachine(*this);
}

string SlotMachine::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SLOT_MACHINE;
}

bool SlotMachine::serialize(ostream& stream) const
{
  Feature::serialize(stream);

  Serialize::write_int(stream, cost);
  Serialize::write_int(stream, pct_chance_win);
  Serialize::write_float(stream, payout_multiplier);

  return true;
}

bool SlotMachine::deserialize(istream& stream)
{
  Feature::deserialize(stream);

  Serialize::read_int(stream, cost);
  Serialize::read_int(stream, pct_chance_win);
  Serialize::read_float(stream, payout_multiplier);

  return true;
}

ClassIdentifier SlotMachine::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SLOT_MACHINE;
}

#ifdef UNIT_TESTS
#include "unit_tests/SlotMachine_test.cpp"
#endif

