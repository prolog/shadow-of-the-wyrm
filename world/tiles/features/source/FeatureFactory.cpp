#include <boost/make_shared.hpp>
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
  FeaturePtr jcd_fixme;

  if (feature_map.empty())
  {
    initialize_feature_map();
  }

  FeatureSerializationMap::iterator f_it = feature_map.find(ci);

  if (f_it != feature_map.end())
  {
    // JCD FIXME ENSURE THAT SHARED PTRS ARE HANDLED APPROPRIATELY
    // jcd_fixme = f_it->second->clone();
  }

  return jcd_fixme;
}

LockPtr FeatureFactory::create_lock()
{
  LockPtr lock = boost::make_shared<Lock>();
  return lock;
}

TrapPtr FeatureFactory::create_trap()
{
  TrapPtr trap = boost::make_shared<Trap>();
  return trap;
}

void FeatureFactory::initialize_feature_map()
{
  feature_map.clear();

  FeaturePtr good_altar         = boost::make_shared<GoodAltar>();
  FeaturePtr neutral_altar      = boost::make_shared<NeutralAltar>();
  FeaturePtr evil_altar         = boost::make_shared<EvilAltar>();
  FeaturePtr king_statue        = boost::make_shared<KingDecorativeStatue>();
  FeaturePtr queen_statue       = boost::make_shared<QueenDecorativeStatue>();
  FeaturePtr warlord_statue     = boost::make_shared<WarlordDecorativeStatue>();
  FeaturePtr knight_statue      = boost::make_shared<KnightDecorativeStatue>();
  FeaturePtr high_priest_statue = boost::make_shared<HighPriestDecorativeStatue>();
  FeaturePtr sorceror_statue    = boost::make_shared<SorcerorDecorativeStatue>();
  FeaturePtr bench              = boost::make_shared<Bench>();
  FeaturePtr door               = boost::make_shared<Door>();
  FeaturePtr ew_pew             = boost::make_shared<EastWestPew>();
  FeaturePtr fire_pillar        = boost::make_shared<FirePillar>();
  FeaturePtr fountain           = boost::make_shared<Fountain>();
  FeaturePtr gate               = boost::make_shared<Gate>();
  FeaturePtr pew                = boost::make_shared<Pew>();

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
  // JCD FIXME
}

