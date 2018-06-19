#include "FeatureGenerator.hpp"
#include "Barrel.hpp"
#include "BasicFeature.hpp"
#include "Bench.hpp"
#include "Bed.hpp"
#include "DecorativeStatues.hpp"
#include "Door.hpp"
#include "EastWestPew.hpp"
#include "EvilAltar.hpp"
#include "FirePillar.hpp"
#include "Fountain.hpp"
#include "Forge.hpp"
#include "Game.hpp"
#include "Gate.hpp"
#include "GoodAltar.hpp"
#include "JewelerWorkbench.hpp"
#include "Log.hpp"
#include "NeutralAltar.hpp"
#include "Pew.hpp"
#include "RegularStatues.hpp"
#include "StoneMarker.hpp"
#include "Table.hpp"
#include "Tannery.hpp"
#include "WheelAndLoom.hpp"

using namespace std;

FeatureGenerator::FeatureGenerator()
{
}

FeatureGenerator::~FeatureGenerator()
{
}

FeatureSerializationMap FeatureGenerator::feature_map;

FeaturePtr FeatureGenerator::create_feature(const ClassIdentifier ci)
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
    string s_cl_id = std::to_string(static_cast<int>(ci));
    string msg = "FeatureGenerator::create_feature - Could not instantiate feature with class_id " + s_cl_id;
    Log::instance().error(msg);
    BOOST_ASSERT_MSG(false, msg.c_str());
  }

  return feature;
}

LockPtr FeatureGenerator::create_lock()
{
  LockPtr lock = std::make_shared<Lock>();
  return lock;
}

TrapPtr FeatureGenerator::create_trap()
{
  TrapPtr trap = std::make_shared<Trap>();
  return trap;
}

void FeatureGenerator::initialize_feature_map()
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
  FeaturePtr trap               = std::make_shared<Trap>();
  FeaturePtr bed                = std::make_shared<Bed>();
  FeaturePtr stone_marker       = std::make_shared<StoneMarker>();
  FeaturePtr table              = std::make_shared<Table>();
  FeaturePtr basic_feature      = std::make_shared<BasicFeature>();

  feature_map = FeatureSerializationMap{{ClassIdentifier::CLASS_ID_GOOD_ALTAR, good_altar},
                                        {ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR, neutral_altar},
                                        {ClassIdentifier::CLASS_ID_EVIL_ALTAR, evil_altar},
                                        {ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE, king_statue},
                                        {ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE, queen_statue},
                                        {ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE, warlord_statue},
                                        {ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE, knight_statue},
                                        {ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE, high_priest_statue},
                                        {ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE, sorceror_statue},
                                        {ClassIdentifier::CLASS_ID_BENCH, bench},
                                        {ClassIdentifier::CLASS_ID_DOOR, door},
                                        {ClassIdentifier::CLASS_ID_EAST_WEST_PEW, ew_pew},
                                        {ClassIdentifier::CLASS_ID_FIRE_PILLAR, fire_pillar},
                                        {ClassIdentifier::CLASS_ID_FOUNTAIN, fountain},
                                        {ClassIdentifier::CLASS_ID_GATE, gate},
                                        {ClassIdentifier::CLASS_ID_PEW, pew},
                                        {ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE, petrified_corpse},
                                        {ClassIdentifier::CLASS_ID_SARCOPHAGUS, sarcophagus},
                                        {ClassIdentifier::CLASS_ID_BARREL, barrel},
                                        {ClassIdentifier::CLASS_ID_FORGE, forge},
                                        {ClassIdentifier::CLASS_ID_TANNERY, tannery},
                                        {ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH, jeweler_workbench},
                                        {ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM, wheel_and_loom},
                                        {ClassIdentifier::CLASS_ID_TRAP, trap},
                                        {ClassIdentifier::CLASS_ID_BED, bed},
                                        {ClassIdentifier::CLASS_ID_STONE_MARKER, stone_marker},
                                        {ClassIdentifier::CLASS_ID_TABLE, table},
                                        {ClassIdentifier::CLASS_ID_BASIC_FEATURE, basic_feature}};
}


// Generates an altar based on the alignment and provided deity ID.
FeaturePtr FeatureGenerator::generate_altar(const std::string& deity_id, const AlignmentRange alignment)
{
  FeaturePtr altar;
  
  switch(alignment)
  {
    case AlignmentRange::ALIGNMENT_RANGE_EVIL:
      altar = std::make_shared<EvilAltar>(deity_id);
      break;
    case AlignmentRange::ALIGNMENT_RANGE_NEUTRAL:
      altar = std::make_shared<NeutralAltar>(deity_id);
      break;
    case AlignmentRange::ALIGNMENT_RANGE_GOOD:
    default:
      altar = std::make_shared<GoodAltar>(deity_id);
      break;    
  }
  
  return altar;
}

FeaturePtr FeatureGenerator::generate_bed()
{
  FeaturePtr bed = std::make_shared<Bed>();
  return bed;
}

// Generate a door based on the parameters provided.
DoorPtr FeatureGenerator::generate_door(const EntranceStateType est)
{
  LockPtr lock_info;
  EntranceState door_state;
  DoorPtr door = std::make_shared<Door>(lock_info, door_state);
  door->get_state_ref().set_state(est);
  return door;
}

// Generate a gate
FeaturePtr FeatureGenerator::generate_gate()
{
  LockPtr lock_info;
  EntranceState gate_state;
  FeaturePtr gate = std::make_shared<Gate>(lock_info, gate_state);
  return gate;
}

// Generate a fire pillar
FeaturePtr FeatureGenerator::generate_fire_pillar()
{
  FeaturePtr fire_pillar = std::make_shared<FirePillar>();
  return fire_pillar;
}

// Generate a happy, bubbly fountain
FeaturePtr FeatureGenerator::generate_fountain()
{
  FeaturePtr fountain = std::make_shared<Fountain>();
  return fountain;
}

// Generate a pew
FeaturePtr FeatureGenerator::generate_pew(const PewDirection pew_direction)
{
  FeaturePtr pew;
  
  switch(pew_direction)
  {
    case PewDirection::PEW_DIRECTION_NORTH_SOUTH:
      pew = std::make_shared<Pew>();
      break;
    case PewDirection::PEW_DIRECTION_EAST_WEST:
    default:
      pew = std::make_shared<EastWestPew>();
      break;
  }

  return pew;
}

// Generate a wrought-iron bench
FeaturePtr FeatureGenerator::generate_bench()
{
  FeaturePtr bench = std::make_shared<Bench>();
  return bench;
}

// Generate a sarcophagus
SarcophagusPtr FeatureGenerator::generate_sarcophagus(const MaterialType material_type)
{
  SarcophagusPtr sarcophagus = std::make_shared<Sarcophagus>(material_type);

  return sarcophagus;
}

// Generate a forge
FeaturePtr FeatureGenerator::generate_forge()
{
  FeaturePtr forge = std::make_shared<Forge>();
  return forge;
}

// Generate a tannery
FeaturePtr FeatureGenerator::generate_tannery()
{
  FeaturePtr tannery = std::make_shared<Tannery>();
  return tannery;
}

// Generate a jeweler's workbench
FeaturePtr FeatureGenerator::generate_jeweler_workbench()
{
  FeaturePtr workbench = std::make_shared<JewelerWorkbench>();
  return workbench;
}

// Generate spinning wheel and loom
FeaturePtr FeatureGenerator::generate_wheel_and_loom()
{
  FeaturePtr wheel_and_loom = std::make_shared<WheelAndLoom>();
  return wheel_and_loom;
}

// Generate a strange, stone marker
FeaturePtr FeatureGenerator::generate_stone_marker()
{
  FeaturePtr stm = std::make_shared<StoneMarker>();
  return stm;
}

FeaturePtr FeatureGenerator::generate_table()
{
  FeaturePtr table = std::make_shared<Table>();
  return table;
}

// Generate a basic feature by ID.
// Will return null if the feature doesn't exist in the game's collection.
FeaturePtr FeatureGenerator::generate_basic_feature(const string& basic_feature_id)
{
  FeaturePtr basic_feature;
  Game& game = Game::instance();
  const FeatureMap& fm = game.get_basic_features_ref();
  const auto f_it = fm.find(basic_feature_id);

  if (f_it != fm.end())
  {
    FeaturePtr bf = f_it->second;

    if (bf != nullptr)
    {
      basic_feature = std::shared_ptr<Feature>(f_it->second->clone());
    }
  }

  return basic_feature;
}

// Construct and generate a basic feature
FeaturePtr FeatureGenerator::generate_basic_feature(const MaterialType mt, const uchar symbol, const Colour colour, const std::string& desc_sid)
{
  FeaturePtr feature = std::make_shared<BasicFeature>(mt, symbol, colour, desc_sid);
  return feature;
}
