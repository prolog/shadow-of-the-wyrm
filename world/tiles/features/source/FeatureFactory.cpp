#include <boost/assert.hpp>
#include "FeatureFactory.hpp"
#include "Barrel.hpp"
#include "Conversion.hpp"
#include "DecorativeStatues.hpp"
#include "GoodAltar.hpp"
#include "NeutralAltar.hpp"
#include "EvilAltar.hpp"
#include "Bench.hpp"
#include "Door.hpp"
#include "EastWestPew.hpp"
#include "FirePillar.hpp"
#include "Forge.hpp"
#include "Fountain.hpp"
#include "Gate.hpp"
#include "JewelerWorkbench.hpp"
#include "Log.hpp"
#include "Pew.hpp"
#include "RegularStatues.hpp"
#include "Sarcophagus.hpp"
#include "Tannery.hpp"
#include "WheelAndLoom.hpp"

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
  else
  {
    // This is a problem, and likely means I've forgotten to update
    // the class ID map!
    string s_cl_id = Integer::to_string(ci);
    string msg = "Could not instantiate feature with class_id " + s_cl_id;
    Log::instance().error(msg);
    BOOST_ASSERT_MSG(false, msg.c_str());
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
  FeaturePtr barrel             = std::make_shared<Barrel>();
  FeaturePtr forge              = std::make_shared<Forge>();
  FeaturePtr tannery            = std::make_shared<Tannery>();
  FeaturePtr jeweler_workbench  = std::make_shared<JewelerWorkbench>();
  FeaturePtr wheel_and_loom     = std::make_shared<WheelAndLoom>();

  feature_map = FeatureSerializationMap{{CLASS_ID_GOOD_ALTAR, good_altar},
                                        {CLASS_ID_NEUTRAL_ALTAR, neutral_altar},
                                        {CLASS_ID_EVIL_ALTAR, evil_altar},
                                        {CLASS_ID_KING_DECORATIVE_STATUE, king_statue},
                                        {CLASS_ID_QUEEN_DECORATIVE_STATUE, queen_statue},
                                        {CLASS_ID_WARLORD_DECORATIVE_STATUE, warlord_statue},
                                        {CLASS_ID_KNIGHT_DECORATIVE_STATUE, knight_statue},
                                        {CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE, high_priest_statue},
                                        {CLASS_ID_SORCEROR_DECORATIVE_STATUE, sorceror_statue},
                                        {CLASS_ID_BENCH, bench},
                                        {CLASS_ID_DOOR, door},
                                        {CLASS_ID_EAST_WEST_PEW, ew_pew},
                                        {CLASS_ID_FIRE_PILLAR, fire_pillar},
                                        {CLASS_ID_FOUNTAIN, fountain},
                                        {CLASS_ID_GATE, gate},
                                        {CLASS_ID_PEW, pew},
                                        {CLASS_ID_PETRIFIED_CORPSE_STATUE, petrified_corpse},
                                        {CLASS_ID_SARCOPHAGUS, sarcophagus},
                                        {CLASS_ID_BARREL, barrel},
                                        {CLASS_ID_FORGE, forge},
                                        {CLASS_ID_TANNERY, tannery},
                                        {CLASS_ID_JEWELER_WORKBENCH, jeweler_workbench},
                                        {CLASS_ID_WHEEL_AND_LOOM, wheel_and_loom} };
}

