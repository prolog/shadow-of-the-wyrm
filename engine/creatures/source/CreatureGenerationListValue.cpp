#include "CreatureGenerationListValue.hpp"

using namespace std;

CreatureGenerationListValue::CreatureGenerationListValue(const string& new_creature_id, CreaturePtr new_creature, const CreatureGenerationValues new_cgv)
: creature_base_id(new_creature_id), creature(new_creature), cgv(new_cgv)
{
}

bool CreatureGenerationListValue::operator==(const CreatureGenerationListValue& cglv2) const
{
  bool result = (creature_base_id == cglv2.creature_base_id);
  result = result && ((creature == nullptr && cglv2.creature == nullptr) || (creature && cglv2.creature && *creature == *cglv2.creature));
  result = result && (cgv == cglv2.cgv);

  return result;
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