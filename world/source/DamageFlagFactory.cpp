#include "DamageFlagFactory.hpp"
#include "TextKeys.hpp"

DamageFlagFactory::DamageFlagFactory()
: description_sids({{DamageFlagType::DAMAGE_FLAG_CHAOTIC, TextKeys::DAMAGE_CHAOTIC},
                    {DamageFlagType::DAMAGE_FLAG_VORPAL, TextKeys::DAMAGE_VORPAL},
                    {DamageFlagType::DAMAGE_FLAG_DRAINING, TextKeys::DAMAGE_DRAINING},
                    {DamageFlagType::DAMAGE_FLAG_ETHEREAL, TextKeys::DAMAGE_ETHEREAL},
                    {DamageFlagType::DAMAGE_FLAG_PIERCING, TextKeys::DAMAGE_PIERCING},
                    {DamageFlagType::DAMAGE_FLAG_INCORPOREAL, TextKeys::DAMAGE_INCORPOREAL},
                    {DamageFlagType::DAMAGE_FLAG_SCYTHING, TextKeys::DAMAGE_SCYTHING}})
{
}

DamageFlag DamageFlagFactory::create_damage_flag(const DamageFlagType df)
{
  auto d_it = description_sids.find(df);

  if (d_it != description_sids.end())
  {
    DamageFlag dflag(d_it->first, d_it->second);
    return dflag;
  }
  else
  {
    DamageFlag dflag(df, "");
    return dflag;
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/DamageFlagFactory_test.cpp"
#endif

