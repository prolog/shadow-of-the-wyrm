#include <boost/make_shared.hpp>
#include "ResistanceFactory.hpp"

using namespace std;

ResistancesSerializationMap ResistanceFactory::resistances_map;

ResistanceFactory::ResistanceFactory()
{
}

ResistanceFactory::~ResistanceFactory()
{
}

boost::shared_ptr<Resistance> ResistanceFactory::create_resistance(const ClassIdentifier ci)
{
  boost::shared_ptr<Resistance> resistance;

  if (resistances_map.empty())
  {
    initialize_resistances_map();
  }

  ResistancesSerializationMap::iterator r_it = resistances_map.find(ci);

  if (r_it != resistances_map.end())
  {
    resistance = boost::shared_ptr<Resistance>(r_it->second->clone());
  }

  return resistance;
}

void ResistanceFactory::initialize_resistances_map()
{
  resistances_map.clear();

  boost::shared_ptr<Resistance> slash     = boost::make_shared<SlashResistance>();
  boost::shared_ptr<Resistance> pierce    = boost::make_shared<PierceResistance>();
  boost::shared_ptr<Resistance> pound     = boost::make_shared<PoundResistance>();
  boost::shared_ptr<Resistance> heat      = boost::make_shared<HeatResistance>();
  boost::shared_ptr<Resistance> cold      = boost::make_shared<ColdResistance>();
  boost::shared_ptr<Resistance> acid      = boost::make_shared<AcidResistance>();
  boost::shared_ptr<Resistance> poison    = boost::make_shared<PoisonResistance>();
  boost::shared_ptr<Resistance> holy      = boost::make_shared<HolyResistance>();
  boost::shared_ptr<Resistance> shadow    = boost::make_shared<ShadowResistance>();
  boost::shared_ptr<Resistance> arcane    = boost::make_shared<ArcaneResistance>();
  boost::shared_ptr<Resistance> mental    = boost::make_shared<MentalResistance>();
  boost::shared_ptr<Resistance> sonic     = boost::make_shared<SonicResistance>();
  boost::shared_ptr<Resistance> radiant   = boost::make_shared<RadiantResistance>();
  boost::shared_ptr<Resistance> lightning = boost::make_shared<LightningResistance>();

  resistances_map.insert(make_pair(CLASS_ID_SLASH_RESISTANCE, slash));
  resistances_map.insert(make_pair(CLASS_ID_PIERCE_RESISTANCE, pierce));
  resistances_map.insert(make_pair(CLASS_ID_POUND_RESISTANCE, pound));
  resistances_map.insert(make_pair(CLASS_ID_HEAT_RESISTANCE, heat));
  resistances_map.insert(make_pair(CLASS_ID_COLD_RESISTANCE, cold));
  resistances_map.insert(make_pair(CLASS_ID_ACID_RESISTANCE, acid));
  resistances_map.insert(make_pair(CLASS_ID_POISON_RESISTANCE, poison));
  resistances_map.insert(make_pair(CLASS_ID_HOLY_RESISTANCE, holy));
  resistances_map.insert(make_pair(CLASS_ID_SHADOW_RESISTANCE, shadow));
  resistances_map.insert(make_pair(CLASS_ID_ARCANE_RESISTANCE, arcane));
  resistances_map.insert(make_pair(CLASS_ID_MENTAL_RESISTANCE, mental));
  resistances_map.insert(make_pair(CLASS_ID_SONIC_RESISTANCE, sonic));
  resistances_map.insert(make_pair(CLASS_ID_RADIANT_RESISTANCE, radiant));
  resistances_map.insert(make_pair(CLASS_ID_LIGHTNING_RESISTANCE, lightning));
}
