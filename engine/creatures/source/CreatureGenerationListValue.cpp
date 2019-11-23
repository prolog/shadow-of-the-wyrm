#include "CreatureGenerationListValue.hpp"

using namespace std;

CreatureGenerationListValue::CreatureGenerationListValue(const string& new_creature_id, CreaturePtr new_creature, const CreatureGenerationValues new_cgv)
: creature_base_id(new_creature_id), creature(new_creature), cgv(new_cgv)
{
}

string CreatureGenerationListValue::get_creature_base_id() const
{
  return creature_base_id;
}

CreaturePtr CreatureGenerationListValue::get_creature() const
{
  return creature;
}

CreatureGenerationValues CreatureGenerationListValue::get_creature_generation_values() const
{
  return cgv;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureGenerationListValue_test.cpp"
#endif