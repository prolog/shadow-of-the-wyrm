#include "DigChancesFactory.hpp"

using namespace std;

DigChancesFactory::DigChancesFactory()
{
}

DigChancesFactory::~DigChancesFactory()
{
}

pair<bool, DigChances> DigChancesFactory::create_feature_dig_chances(const ClassIdentifier ci)
{
  pair<bool, DigChances> update_dc;
  update_dc.first = false;

  if (ci == ClassIdentifier::CLASS_ID_SARCOPHAGUS)
  {
    update_dc.first = true;

    DigChances dc;
    dc.set_pct_chance_item(25);
    dc.set_pct_chance_undead(20);

    update_dc.second = dc;
  }

  return update_dc;
}

