#include "FeatureGenerator.hpp"
#include "ConfigurableFeature.hpp"
#include "Game.hpp"
#include "Log.hpp"

using namespace std;

FeatureGenerator::FeatureGenerator()
{
}

FeatureGenerator::~FeatureGenerator()
{
}

FeatureSerializationMap FeatureGenerator::feature_map;
FeatureSymbolMap FeatureGenerator::feature_symbol_map;

Symbol FeatureGenerator::get_config_symbol(const ClassIdentifier ci)
{
  auto f_it = feature_symbol_map.find(ci);
  if (f_it != feature_symbol_map.end())
  {
  }
  else
  {
    ostringstream ss;
    ss << "Couldn't find CI in FeatureGenerator::get_config_symbol: " << static_cast<int>(ci);
    string error_msg = ss.str();

    Log::instance().error(error_msg);
  }

  // The feature map might be empty when we're running unit tests
  // and haven't loaded game data.
  Symbol symbol('?', Colour::COLOUR_WHITE);

  if (f_it != feature_symbol_map.end())
  {
    symbol = f_it->second;
  }

  return symbol;
}

FeaturePtr FeatureGenerator::create_feature(const ClassIdentifier ci)
{
  FeaturePtr feature;
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
  TrapPtr trap = std::make_shared<Trap>(get_config_symbol(ClassIdentifier::CLASS_ID_TRAP));
  return trap;
}

// Before this function is called, the feature_symbol_map member should have
// been initialized.
void FeatureGenerator::initialize_feature_map()
{
  feature_map.clear();

  FeaturePtr good_altar         = std::make_shared<GoodAltar>(get_config_symbol(ClassIdentifier::CLASS_ID_GOOD_ALTAR));
  FeaturePtr neutral_altar      = std::make_shared<NeutralAltar>(get_config_symbol(ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR));
  FeaturePtr evil_altar         = std::make_shared<EvilAltar>(get_config_symbol(ClassIdentifier::CLASS_ID_EVIL_ALTAR));
  FeaturePtr generic_dec_statue = std::make_shared<KingDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_DECORATIVE_STATUE));
  FeaturePtr generic_reg_statue = std::make_shared<KingDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_REGULAR_STATUE));
  FeaturePtr king_statue        = std::make_shared<KingDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE));
  FeaturePtr queen_statue       = std::make_shared<QueenDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE));
  FeaturePtr warlord_statue     = std::make_shared<WarlordDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE));
  FeaturePtr knight_statue      = std::make_shared<KnightDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE));
  FeaturePtr high_priest_statue = std::make_shared<HighPriestDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE));
  FeaturePtr sorceror_statue    = std::make_shared<SorcerorDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE));
  FeaturePtr bench              = std::make_shared<Bench>(get_config_symbol(ClassIdentifier::CLASS_ID_BENCH));
  
  FeaturePtr door               = std::make_shared<Door>(get_config_symbol(ClassIdentifier::CLASS_ID_DOOR));
  FeaturePtr ew_pew             = std::make_shared<EastWestPew>(get_config_symbol(ClassIdentifier::CLASS_ID_EAST_WEST_PEW));
  FeaturePtr fire_pillar        = std::make_shared<FirePillar>(get_config_symbol(ClassIdentifier::CLASS_ID_FIRE_PILLAR));
  FeaturePtr fountain           = std::make_shared<Fountain>(get_config_symbol(ClassIdentifier::CLASS_ID_FOUNTAIN));
  FeaturePtr gate               = std::make_shared<Gate>(get_config_symbol(ClassIdentifier::CLASS_ID_GATE));

  FeaturePtr pew                = std::make_shared<Pew>(get_config_symbol(ClassIdentifier::CLASS_ID_PEW));
  FeaturePtr petrified_corpse   = std::make_shared<PetrifiedCorpseStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE));
  FeaturePtr sarcophagus        = std::make_shared<Sarcophagus>(get_config_symbol(ClassIdentifier::CLASS_ID_SARCOPHAGUS));
  FeaturePtr barrel             = std::make_shared<Barrel>(get_config_symbol(ClassIdentifier::CLASS_ID_BARREL));
  FeaturePtr forge              = std::make_shared<Forge>(get_config_symbol(ClassIdentifier::CLASS_ID_FORGE));
  FeaturePtr tannery            = std::make_shared<Tannery>(get_config_symbol(ClassIdentifier::CLASS_ID_TANNERY));
  FeaturePtr pulper             = std::make_shared<Pulper>(get_config_symbol(ClassIdentifier::CLASS_ID_PULPER));
  FeaturePtr jeweler_workbench  = std::make_shared<JewelerWorkbench>(get_config_symbol(ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH));
  FeaturePtr wheel_and_loom     = std::make_shared<WheelAndLoom>(get_config_symbol(ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM));
  FeaturePtr trap               = std::make_shared<Trap>(get_config_symbol(ClassIdentifier::CLASS_ID_TRAP));
  FeaturePtr bed                = std::make_shared<Bed>(get_config_symbol(ClassIdentifier::CLASS_ID_BED));
  FeaturePtr stone_marker       = std::make_shared<StoneMarker>(get_config_symbol(ClassIdentifier::CLASS_ID_STONE_MARKER));
  FeaturePtr table              = std::make_shared<Table>(get_config_symbol(ClassIdentifier::CLASS_ID_TABLE));
  FeaturePtr config_feature     = std::make_shared<ConfigurableFeature>(Symbol('?', Colour::COLOUR_WHITE));
  FeaturePtr slot_machine       = std::make_shared<SlotMachine>(get_config_symbol(ClassIdentifier::CLASS_ID_SLOT_MACHINE));
  FeaturePtr sign               = std::make_shared<Sign>(get_config_symbol(ClassIdentifier::CLASS_ID_SIGN), "fake_sid");
  FeaturePtr kiln               = std::make_shared<Kiln>(get_config_symbol(ClassIdentifier::CLASS_ID_KILN));

  feature_map = FeatureSerializationMap{{ClassIdentifier::CLASS_ID_GOOD_ALTAR, good_altar},
                                        {ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR, neutral_altar},
                                        {ClassIdentifier::CLASS_ID_EVIL_ALTAR, evil_altar},
                                        {ClassIdentifier::CLASS_ID_DECORATIVE_STATUE, generic_dec_statue},
                                        {ClassIdentifier::CLASS_ID_REGULAR_STATUE, generic_reg_statue},
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
                                        {ClassIdentifier::CLASS_ID_CONFIGURABLE_FEATURE, config_feature},
                                        {ClassIdentifier::CLASS_ID_SLOT_MACHINE, slot_machine},
                                        {ClassIdentifier::CLASS_ID_SIGN, sign},
                                        {ClassIdentifier::CLASS_ID_PULPER, pulper},
                                        {ClassIdentifier::CLASS_ID_KILN, kiln}};
}


// Generates an altar based on the alignment and provided deity ID.
FeaturePtr FeatureGenerator::generate_altar(const std::string& deity_id, const AlignmentRange alignment)
{
  FeaturePtr altar;
  
  switch(alignment)
  {
    case AlignmentRange::ALIGNMENT_RANGE_EVIL:
      altar = std::make_shared<EvilAltar>(get_config_symbol(ClassIdentifier::CLASS_ID_EVIL_ALTAR), deity_id);
      break;
    case AlignmentRange::ALIGNMENT_RANGE_NEUTRAL:
      altar = std::make_shared<NeutralAltar>(get_config_symbol(ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR), deity_id);
      break;
    case AlignmentRange::ALIGNMENT_RANGE_GOOD:
    default:
      altar = std::make_shared<GoodAltar>(get_config_symbol(ClassIdentifier::CLASS_ID_GOOD_ALTAR), deity_id);
      break;    
  }
  
  return altar;
}

FeaturePtr FeatureGenerator::generate_barrel()
{
  FeaturePtr barrel = std::make_shared<Barrel>(get_config_symbol(ClassIdentifier::CLASS_ID_BARREL));
  return barrel;
}

FeaturePtr FeatureGenerator::generate_bed()
{
  FeaturePtr bed = std::make_shared<Bed>(get_config_symbol(ClassIdentifier::CLASS_ID_BED));
  return bed;
}

// Generate a door based on the parameters provided.
DoorPtr FeatureGenerator::generate_door(const EntranceStateType est)
{
  LockPtr lock_info;
  EntranceState door_state;
  DoorPtr door = std::make_shared<Door>(get_config_symbol(ClassIdentifier::CLASS_ID_DOOR), lock_info, door_state);
  door->get_state_ref().set_state(est);
  return door;
}

// Generate a gate
FeaturePtr FeatureGenerator::generate_gate()
{
  LockPtr lock_info;
  EntranceState gate_state;
  FeaturePtr gate = std::make_shared<Gate>(get_config_symbol(ClassIdentifier::CLASS_ID_GATE), lock_info, gate_state);
  return gate;
}

// Generate a fire pillar
FeaturePtr FeatureGenerator::generate_fire_pillar()
{
  FeaturePtr fire_pillar = std::make_shared<FirePillar>(get_config_symbol(ClassIdentifier::CLASS_ID_FIRE_PILLAR));
  return fire_pillar;
}

// Generate a happy, bubbly fountain
FeaturePtr FeatureGenerator::generate_fountain()
{
  FeaturePtr fountain = std::make_shared<Fountain>(get_config_symbol(ClassIdentifier::CLASS_ID_FOUNTAIN));
  return fountain;
}

// Generate a pew
FeaturePtr FeatureGenerator::generate_pew(const PewDirection pew_direction)
{
  FeaturePtr pew;
  
  switch(pew_direction)
  {
    case PewDirection::PEW_DIRECTION_NORTH_SOUTH:
      pew = std::make_shared<Pew>(get_config_symbol(ClassIdentifier::CLASS_ID_PEW));
      break;
    case PewDirection::PEW_DIRECTION_EAST_WEST:
    default:
      pew = std::make_shared<EastWestPew>(get_config_symbol(ClassIdentifier::CLASS_ID_EAST_WEST_PEW));
      break;
  }

  return pew;
}

// Generate a wrought-iron bench
FeaturePtr FeatureGenerator::generate_bench()
{
  FeaturePtr bench = std::make_shared<Bench>(get_config_symbol(ClassIdentifier::CLASS_ID_BENCH));
  return bench;
}

// Generate a sarcophagus
SarcophagusPtr FeatureGenerator::generate_sarcophagus(const MaterialType material_type)
{
  SarcophagusPtr sarcophagus = std::make_shared<Sarcophagus>(get_config_symbol(ClassIdentifier::CLASS_ID_SARCOPHAGUS), material_type);
  return sarcophagus;
}

// Generate a slot machine
SlotMachinePtr FeatureGenerator::generate_slot_machine(const MaterialType material_type, const int cost, const int pct_chance_win, const float payout_multiplier)
{
  SlotMachinePtr slot_machine = std::make_shared<SlotMachine>(get_config_symbol(ClassIdentifier::CLASS_ID_SLOT_MACHINE), material_type, cost, pct_chance_win, payout_multiplier);
  return slot_machine;
}

// Generate a forge
FeaturePtr FeatureGenerator::generate_forge()
{
  FeaturePtr forge = std::make_shared<Forge>(get_config_symbol(ClassIdentifier::CLASS_ID_FORGE));
  return forge;
}

// Generate a kiln
FeaturePtr FeatureGenerator::generate_kiln()
{
  FeaturePtr kiln = std::make_shared<Kiln>(get_config_symbol(ClassIdentifier::CLASS_ID_KILN));
  return kiln;
}

// Generate a tannery
FeaturePtr FeatureGenerator::generate_tannery()
{
  FeaturePtr tannery = std::make_shared<Tannery>(get_config_symbol(ClassIdentifier::CLASS_ID_TANNERY));
  return tannery;
}

// Generate a pulper
FeaturePtr FeatureGenerator::generate_pulper()
{
  FeaturePtr pulper = std::make_shared<Pulper>(get_config_symbol(ClassIdentifier::CLASS_ID_PULPER));
  return pulper;
}

// Generate a jeweler's workbench
FeaturePtr FeatureGenerator::generate_jeweler_workbench()
{
  FeaturePtr workbench = std::make_shared<JewelerWorkbench>(get_config_symbol(ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH));
  return workbench;
}

// Generate spinning wheel and loom
FeaturePtr FeatureGenerator::generate_wheel_and_loom()
{
  FeaturePtr wheel_and_loom = std::make_shared<WheelAndLoom>(get_config_symbol(ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM));
  return wheel_and_loom;
}

// Generate a strange, stone marker
FeaturePtr FeatureGenerator::generate_stone_marker()
{
  FeaturePtr stm = std::make_shared<StoneMarker>(get_config_symbol(ClassIdentifier::CLASS_ID_STONE_MARKER));
  return stm;
}

FeaturePtr FeatureGenerator::generate_table()
{
  FeaturePtr table = std::make_shared<Table>(get_config_symbol(ClassIdentifier::CLASS_ID_TABLE));
  return table;
}

// Generate a configurable feature by ID.
// Will return null if the feature doesn't exist in the game's collection.
FeaturePtr FeatureGenerator::generate_configurable_feature(const string& configurable_feature_id)
{
  FeaturePtr configurable_feature;
  Game& game = Game::instance();
  const FeatureMap& fm = game.get_configurable_features_ref();
  const auto f_it = fm.find(configurable_feature_id);

  if (f_it != fm.end())
  {
    FeaturePtr cf = f_it->second;

    if (cf != nullptr)
    {
      configurable_feature = std::shared_ptr<Feature>(f_it->second->clone());
    }
  }

  return configurable_feature;
}

// Construct and generate a configurable
FeaturePtr FeatureGenerator::generate_configurable_feature(const MaterialType mt, const Symbol& s, const std::string& desc_sid)
{
  FeaturePtr feature = std::make_shared<ConfigurableFeature>(s, mt, desc_sid);

  return feature;
}

FeaturePtr FeatureGenerator::generate_sign(const string& text_sid)
{
  FeaturePtr sign = std::make_shared<Sign>(get_config_symbol(ClassIdentifier::CLASS_ID_SIGN), text_sid);

  return sign;
}

// Generate a random decorative statue
FeaturePtr FeatureGenerator::generate_decorative_statue(const DecorativeStatueType type)
{
  FeaturePtr statue;

  static_assert(DecorativeStatueType::DECORATIVE_STATUE_TYPE_LAST == DecorativeStatueType(5), "Unexpected DecorativeStatueType::DECORATIVE_STATUE_TYPE_LAST value.");

  switch(type)
  {
    case DecorativeStatueType::DECORATIVE_STATUE_TYPE_KING:
      statue = std::make_shared<KingDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE));
      break;
    case DecorativeStatueType::DECORATIVE_STATUE_TYPE_QUEEN:
      statue = std::make_shared<QueenDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE));
      break;
    case DecorativeStatueType::DECORATIVE_STATUE_TYPE_WARLORD:
      statue = std::make_shared<WarlordDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE));
      break;
    case DecorativeStatueType::DECORATIVE_STATUE_TYPE_KNIGHT:
      statue = std::make_shared<KnightDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE));
      break;
    case DecorativeStatueType::DECORATIVE_STATUE_TYPE_HIGH_PRIEST:
      statue = std::make_shared<HighPriestDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE));
      break;
    case DecorativeStatueType::DECORATIVE_STATUE_TYPE_SORCEROR:
      statue = std::make_shared<SorcerorDecorativeStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE));
      break;
    default:
      break;
  }

  return statue;
}

PetrifiedCorpseStatuePtr FeatureGenerator::generate_petrified_corpse_statue(const string& corpse_description_sid)
{
  PetrifiedCorpseStatuePtr statue;
  statue = std::make_shared<PetrifiedCorpseStatue>(get_config_symbol(ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE), corpse_description_sid);
  
  return statue;
}

void FeatureGenerator::set_feature_symbol_map(const FeatureSymbolMap& new_fsm)
{
  feature_symbol_map = new_fsm;
  initialize_feature_map();
}

FeatureSymbolMap FeatureGenerator::get_feature_symbol_map()
{
  return feature_symbol_map;
}
