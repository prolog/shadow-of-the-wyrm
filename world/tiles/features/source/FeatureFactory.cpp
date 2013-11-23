#include "FeatureFactory.hpp"
#include "DecorativeStatues.hpp"
#include "GoodAltar.hpp"
#include "NeutralAltar.hpp"
#include "EvilAltar.hpp"
#include "Bench.hpp"
#include "Door.hpp"
#include "EastWestPew.hpp"
#include "FirePillar.hpp"
#include "Fountain.hpp"
#include "Gate.hpp"
#include "Pew.hpp"
#include "RegularStatues.hpp"
#include "Sarcophagus.hpp"

using namespace std;

FeatureSerializationMap FeatureFactory::feature_map;

FeatureFactory::FeatureFactory()
{
}

FeatureFactory::~FeatureFactory()
{
}

FeaturePtr FeatureFactory::create_feature(const ClassIdentifier ci)
{
  FeaturePtr feature;

  if (feature_map.empty())
  {
    initialize_feature_map();
  }

  FeatureSerializationMap::iterator f_it = feature_map.find(ci);

  if (f_it != feature_map.end())
  {
    feature = FeaturePtr(f_it->second->clone());
  }

  return feature;
}

LockPtr FeatureFactory::create_lock()
{
  LockPtr lock = std::make_shared<Lock>();
  return lock;
}

TrapPtr FeatureFactory::create_trap()
{
  TrapPtr trap = std::make_shared<Trap>();
  return trap;
}

void FeatureFactory::initialize_feature_map()
{
  feature_map.clear();

  FeaturePtr good_altar         = std::make_shared<GoodAltar>();
  FeaturePtr neutral_altar      = std::make_shared<NeutralAltar>();
  FeaturePtr evil_altar         = std::make_shared<EvilAltar>();
  FeaturePtr king_statue        = std::make_shared<KingDecorativeStatue>();
  FeaturePtr queen_statue       = std::make_shared<QueenDecorativeStatue>();
  FeaturePtr warlord_statue     = std::make_shared<WarlordDecorativeStatue>();
  FeaturePtr knight_statue      = std::make_shared<KnightDecorativeStatue>();
  FeaturePtr high_priest_statue = std::make_shared<HighPriestDecorativeStatue>();
  FeaturePtr sorceror_statue    = std::make_shared<SorcerorDecorativeStatue>();
  FeaturePtr bench              = std::make_shared<Bench>();
  FeaturePtr door               = std::make_shared<Door>();
  FeaturePtr ew_pew             = std::make_shared<EastWestPew>();
  FeaturePtr fire_pillar        = std::make_shared<FirePillar>();
  FeaturePtr fountain           = std::make_shared<Fountain>();
  FeaturePtr gate               = std::make_shared<Gate>();
  FeaturePtr pew                = std::make_shared<Pew>();
  FeaturePtr petrified_corpse   = std::make_shared<PetrifiedCorpseStatue>();
  FeaturePtr sarcophagus        = std::make_shared<Sarcophagus>();

  feature_map.insert(make_pair(CLASS_ID_GOOD_ALTAR, good_altar));
  feature_map.insert(make_pair(CLASS_ID_NEUTRAL_ALTAR, neutral_altar));
  feature_map.insert(make_pair(CLASS_ID_EVIL_ALTAR, evil_altar));
  feature_map.insert(make_pair(CLASS_ID_KING_DECORATIVE_STATUE, king_statue));
  feature_map.insert(make_pair(CLASS_ID_QUEEN_DECORATIVE_STATUE, queen_statue));
  feature_map.insert(make_pair(CLASS_ID_WARLORD_DECORATIVE_STATUE, warlord_statue));
  feature_map.insert(make_pair(CLASS_ID_KNIGHT_DECORATIVE_STATUE, knight_statue));
  feature_map.insert(make_pair(CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE, high_priest_statue));
  feature_map.insert(make_pair(CLASS_ID_SORCEROR_DECORATIVE_STATUE, sorceror_statue));
  feature_map.insert(make_pair(CLASS_ID_BENCH, bench));
  feature_map.insert(make_pair(CLASS_ID_DOOR, door));
  feature_map.insert(make_pair(CLASS_ID_EAST_WEST_PEW, ew_pew));
  feature_map.insert(make_pair(CLASS_ID_FIRE_PILLAR, fire_pillar));
  feature_map.insert(make_pair(CLASS_ID_FOUNTAIN, fountain));
  feature_map.insert(make_pair(CLASS_ID_GATE, gate));
  feature_map.insert(make_pair(CLASS_ID_PEW, pew));
  feature_map.insert(make_pair(CLASS_ID_PETRIFIED_CORPSE_STATUE, petrified_corpse));
  feature_map.insert(make_pair(CLASS_ID_SARCOPHAGUS, sarcophagus));
  // JCD FIXME
}

