#include "DamageFlag.hpp"

using namespace std;

DamageFlag::DamageFlag(const DamageFlagType dft, const string& desc_sid)
: flag(dft), description_sid(desc_sid)
{
}

DamageFlagType DamageFlag::get_flag() const
{
  return flag;
}

string DamageFlag::get_description_sid() const
{
  return description_sid;
}

#ifdef UNIT_TESTS
#include "unit_tests/DamageFlag_test.cpp"
#endif

