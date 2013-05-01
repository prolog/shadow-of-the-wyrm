#include "IndividualSpellKnowledge.hpp"
#include "Serialize.hpp"

using namespace std;

IndividualSpellKnowledge::IndividualSpellKnowledge()
: castings(0), bonus(0)
{
}

bool IndividualSpellKnowledge::operator==(const IndividualSpellKnowledge& isk) const
{
  bool result = true;

  result = result && (castings == isk.castings);
  result = result && (bonus == isk.bonus);

  return result;
}

void IndividualSpellKnowledge::set_castings(const uint new_castings)
{
  castings = new_castings;
}

uint IndividualSpellKnowledge::get_castings() const
{
  return castings;
}

void IndividualSpellKnowledge::set_bonus(const uint new_bonus)
{
  bonus = new_bonus;
}

uint IndividualSpellKnowledge::get_bonus() const
{
  return bonus;
}

bool IndividualSpellKnowledge::serialize(std::ostream& stream)
{
  Serialize::write_uint(stream, castings);
  Serialize::write_uint(stream, bonus);

  return true;
}

bool IndividualSpellKnowledge::deserialize(std::istream& stream)
{
  Serialize::read_uint(stream, castings);
  Serialize::read_uint(stream, bonus);

  return true;
}

ClassIdentifier IndividualSpellKnowledge::internal_class_identifier() const
{
  return CLASS_ID_INDIVIDUAL_SPELL_KNOWLEDGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/IndividualSpellKnowledge_test.cpp"
#endif
