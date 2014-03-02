#include "Conducts.hpp"
#include "Serialize.hpp"

using namespace std;

Conducts::Conducts()
{
  cond = array<bool, 5>{{ true, true, true, true }};
}

bool Conducts::operator==(const Conducts& c) const
{
  bool result = true;

  result = result && (cond == c.cond);
  return result;
}

// Get all currently-valid conducts
array<bool, CONDUCT_SIZE> Conducts::get_conducts() const
{
  return cond;
}

// Break a particular conduct
void Conducts::break_conduct(const ConductType ct)
{
  cond[ct] = false;
}

bool Conducts::serialize(ostream& stream) const
{
  static_assert(CONDUCT_SIZE == 5, "Unexpected number of conducts");

  for (const bool conduct : cond)
  {
    Serialize::write_bool(stream, conduct);
  }

  return true;
}

bool Conducts::deserialize(istream& stream)
{
  for (int i = 0; i < CONDUCT_SIZE; i++)
  {
    bool conduct = false;
    Serialize::read_bool(stream, conduct);

    cond[i] = conduct;
  }

  return true;
}

ClassIdentifier Conducts::internal_class_identifier() const
{
  return CLASS_ID_CONDUCTS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conducts_test.cpp"
#endif