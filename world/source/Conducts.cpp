#include "Conducts.hpp"
#include "Serialize.hpp"

using namespace std;

Conducts::Conducts()
{
  std::fill(cond.begin(), cond.end(), true);
}

bool Conducts::operator==(const Conducts& c) const
{
  bool result = true;

  result = result && (cond == c.cond);
  return result;
}

// Get all currently-valid conducts
array<bool, static_cast<size_t>(ConductType::CONDUCT_SIZE)> Conducts::get_conducts() const
{
  return cond;
}

// Break a particular conduct
void Conducts::break_conduct(const ConductType ct)
{
  cond[static_cast<int>(ct)] = false;
}

int Conducts::get_num_broken_conducts() const
{
  int broken = 0;

  for (size_t i = 0; i < static_cast<int>(ConductType::CONDUCT_SIZE); i++)
  {
    if (cond[i] == false)
    {
      broken++;
    }
  }

  return broken;
}

bool Conducts::serialize(ostream& stream) const
{
  static_assert(ConductType::CONDUCT_SIZE == ConductType(9), "Unexpected number of conducts");

  for (const bool conduct : cond)
  {
    Serialize::write_bool(stream, conduct);
  }

  return true;
}

bool Conducts::deserialize(istream& stream)
{
  for (int i = 0; i < static_cast<int>(ConductType::CONDUCT_SIZE); i++)
  {
    bool conduct = false;
    Serialize::read_bool(stream, conduct);

    cond[i] = conduct;
  }

  return true;
}

ClassIdentifier Conducts::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CONDUCTS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conducts_test.cpp"
#endif