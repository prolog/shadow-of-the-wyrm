#include "ResistanceFactory.hpp"

using namespace std;

ResistancesSerializationMap ResistanceFactory::resistances_map;

ResistanceFactory::ResistanceFactory()
{
}

ResistanceFactory::~ResistanceFactory()
{
}

std::shared_ptr<Resistance> ResistanceFactory::create_resistance(const ClassIdentifier ci)
{
  std::shared_ptr<Resistance> resistance;

  if (resistances_map.empty())
  {
    initialize_resistances_map();
  }

  ResistancesSerializationMap::iterator r_it = resistances_map.find(ci);

  if (r_it != resistances_map.end())
  {
    resistance = std::shared_ptr<Resistance>(r_it->second->clone());
  }

  return resistance;
}

void ResistanceFactory::initialize_resistances_map()
{
  resistances_map.clear();

  std::shared_ptr<Resistance> slash     = std::make_shared<SlashResistance>();
  std::shared_ptr<Resistance> pierce    = std::make_shared<PierceResistance>();
  std::shared_ptr<Resistance> pound     = std::make_shared<PoundResistance>();
  std::shared_ptr<Resistance> heat      = std::make_shared<HeatResistance>();
  std::shared_ptr<Resistance> cold      = std::make_shared<ColdResistance>();
  std::shared_ptr<Resistance> acid      = std::make_shared<AcidResistance>();
  std::shared_ptr<Resistance> poison    = std::make_shared<PoisonResistance>();
  std::shared_ptr<Resistance> holy      = std::make_shared<HolyResistance>();
  std::shared_ptr<Resistance> shadow    = std::make_shared<ShadowResistance>();
  std::shared_ptr<Resistance> arcane    = std::make_shared<ArcaneResistance>();
  std::shared_ptr<Resistance> lightning = std::make_shared<LightningResistance>();

  resistances_map = ResistancesSerializationMap{{ClassIdentifier::CLASS_ID_SLASH_RESISTANCE, slash},
                                                {ClassIdentifier::CLASS_ID_PIERCE_RESISTANCE, pierce},
                                                {ClassIdentifier::CLASS_ID_POUND_RESISTANCE, pound},
                                                {ClassIdentifier::CLASS_ID_HEAT_RESISTANCE, heat},
                                                {ClassIdentifier::CLASS_ID_COLD_RESISTANCE, cold},
                                                {ClassIdentifier::CLASS_ID_ACID_RESISTANCE, acid},
                                                {ClassIdentifier::CLASS_ID_POISON_RESISTANCE, poison},
                                                {ClassIdentifier::CLASS_ID_HOLY_RESISTANCE, holy},
                                                {ClassIdentifier::CLASS_ID_SHADOW_RESISTANCE, shadow},
                                                {ClassIdentifier::CLASS_ID_ARCANE_RESISTANCE, arcane},
                                                {ClassIdentifier::CLASS_ID_LIGHTNING_RESISTANCE, lightning}};
}
