#include "ActionTextKeys.hpp"
#include "Features.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "global_prototypes.hpp"
#include "MaterialFactory.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

// Altars

Altar::Altar(const std::string& new_desc_sid, const Symbol& new_symbol, const std::string& new_deity_id, const MaterialType new_material, const AlignmentRange new_alignment_range)
  : Feature(new_desc_sid, new_material, new_alignment_range, new_symbol), deity_id(new_deity_id)
{
}

bool Altar::operator==(const Altar& altar) const
{
  bool result = Feature::operator==(altar);

  result = result && (deity_id == altar.deity_id);

  return result;
}

string Altar::get_deity_id() const
{
  return deity_id;
}

bool Altar::can_offer() const
{
  return true;
}

bool Altar::offer()
{
  // Good things happen.
  return true;
}

float Altar::get_piety_loss_multiplier() const
{
  return 0.5f;
}

AlignmentRange Altar::get_alignment_range() const
{
  return alignment_range;
}

bool Altar::serialize(ostream& stream) const
{
  Feature::serialize(stream);
  Serialize::write_string(stream, deity_id);

  return true;
}

bool Altar::deserialize(istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_string(stream, deity_id);

  return true;
}

ClassIdentifier Altar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ALTAR;
}

EvilAltar::EvilAltar(const Symbol& new_symbol)
  : Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR, new_symbol, "", MaterialType::MATERIAL_TYPE_ONYX, AlignmentRange::ALIGNMENT_RANGE_EVIL)
{
}

EvilAltar::EvilAltar(const Symbol& new_symbol, const std::string& new_deity_id)
  : Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR, new_symbol, new_deity_id, MaterialType::MATERIAL_TYPE_ONYX, AlignmentRange::ALIGNMENT_RANGE_EVIL)
{
}

Feature* EvilAltar::clone()
{
  return new EvilAltar(*this);
}

ClassIdentifier EvilAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EVIL_ALTAR;
}

// This constructor is only used by the serialization code.
GoodAltar::GoodAltar(const Symbol& new_symbol)
  : Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GOOD_ALTAR, new_symbol, "", MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_GOOD)
{
}

GoodAltar::GoodAltar(const Symbol& new_symbol, const std::string& new_deity_id)
  : Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GOOD_ALTAR, new_symbol, new_deity_id, MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_GOOD)
{
}

Feature* GoodAltar::clone()
{
  return new GoodAltar(*this);
}

ClassIdentifier GoodAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GOOD_ALTAR;
}

// This constructor is only used by the serialization code
NeutralAltar::NeutralAltar(const Symbol& new_symbol)
  : Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR, new_symbol, "", MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

NeutralAltar::NeutralAltar(const Symbol& new_symbol, const std::string& new_deity_id)
  : Altar(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR, new_symbol, new_deity_id, MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL)
{
}

Feature* NeutralAltar::clone()
{
  return new NeutralAltar(*this);
}

ClassIdentifier NeutralAltar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR;
}
// Barrel
const int Barrel::MIN_DRINKS = 3;
const int Barrel::MAX_DRINKS = 64;

Barrel::Barrel(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BARREL, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), drinks(1), tap(false)
{
  initialize_drinks();
}

void Barrel::initialize_drinks()
{
  drinks = RNG::range(MIN_DRINKS, MAX_DRINKS);
}

Feature* Barrel::clone()
{
  return new Barrel(*this);
}

bool Barrel::operator==(const Barrel& b) const
{
  bool equal = true;

  equal = Feature::operator==(b);

  equal = equal && (drinks == b.drinks);
  equal = equal && (tap == b.tap);
  equal = equal && (pour_item_id == b.pour_item_id);

  return equal;
}

bool Barrel::pour()
{
  bool poured = false;

  if (can_pour())
  {
    drinks--;
    poured = true;
  }

  return poured;
}

bool Barrel::can_pour() const
{
  bool pour = false;

  if (tap && !pour_item_id.empty() && drinks > 0)
  {
    pour = true;
  }

  return pour;
}

ClassIdentifier Barrel::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BARREL;
}

void Barrel::set_drinks(const int new_drinks)
{
  drinks = new_drinks;
}

int Barrel::get_drinks() const
{
  return drinks;
}

void Barrel::set_tap(const bool new_tap)
{
  tap = new_tap;
}

bool Barrel::get_tap() const
{
  return tap;
}

void Barrel::set_pour_item_id(const string& new_pour_item_id)
{
  pour_item_id = new_pour_item_id;
}

string Barrel::get_pour_item_id() const
{
  return pour_item_id;
}

bool Barrel::serialize(std::ostream& stream) const
{
  Feature::serialize(stream);

  Serialize::write_int(stream, drinks);
  Serialize::write_bool(stream, tap);
  Serialize::write_string(stream, pour_item_id);

  return true;
}

bool Barrel::deserialize(std::istream& stream)
{
  Feature::deserialize(stream);

  Serialize::read_int(stream, drinks);
  Serialize::read_bool(stream, tap);
  Serialize::read_string(stream, pour_item_id);

  return true;
}

// Bed

Bed::Bed(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BED, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Bed::clone()
{
  return new Bed(*this);
}

float Bed::get_hp_regeneration_multiplier() const
{
  return 0.3f;
}

float Bed::get_ap_regeneration_multiplier() const
{
  return 0.75f;
}

ClassIdentifier Bed::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BED;
}

// Bench

Bench::Bench(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BENCH, MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Bench::clone()
{
  return new Bench(*this);
}

ClassIdentifier Bench::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BENCH;
}

// Decorative Statues

// Abstract base decorative statue class.
DecorativeStatue::DecorativeStatue(const string& new_description_sid, const Symbol& new_symbol)
  : Feature(new_description_sid, MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

bool DecorativeStatue::get_is_blocking() const
{
  return true;
}

ClassIdentifier DecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DECORATIVE_STATUE;
}

// King
KingDecorativeStatue::KingDecorativeStatue(const Symbol& new_symbol)
  : DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KING_STATUE, new_symbol)
{
}

Feature* KingDecorativeStatue::clone()
{
  return new KingDecorativeStatue(*this);
}

ClassIdentifier KingDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE;
}

// Queen
QueenDecorativeStatue::QueenDecorativeStatue(const Symbol& new_symbol)
  : DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_QUEEN_STATUE, new_symbol)
{
}

Feature* QueenDecorativeStatue::clone()
{
  return new QueenDecorativeStatue(*this);
}

ClassIdentifier QueenDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE;
}

// Warlord
WarlordDecorativeStatue::WarlordDecorativeStatue(const Symbol& new_symbol)
  : DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WARLORD_STATUE, new_symbol)
{
}

Feature* WarlordDecorativeStatue::clone()
{
  return new WarlordDecorativeStatue(*this);
}

ClassIdentifier WarlordDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE;
}

// Knight
KnightDecorativeStatue::KnightDecorativeStatue(const Symbol& new_symbol)
  : DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KNIGHT_STATUE, new_symbol)
{
}

Feature* KnightDecorativeStatue::clone()
{
  return new KnightDecorativeStatue(*this);
}

ClassIdentifier KnightDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE;
}

// High Priest
HighPriestDecorativeStatue::HighPriestDecorativeStatue(const Symbol& new_symbol)
  : DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE, new_symbol)
{
}

Feature* HighPriestDecorativeStatue::clone()
{
  return new HighPriestDecorativeStatue(*this);
}

ClassIdentifier HighPriestDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE;
}

// Sorceror
SorcerorDecorativeStatue::SorcerorDecorativeStatue(const Symbol& new_symbol)
  : DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SORCEROR_STATUE, new_symbol)
{
}

Feature* SorcerorDecorativeStatue::clone()
{
  return new SorcerorDecorativeStatue(*this);
}

ClassIdentifier SorcerorDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE;
}

// Door

// This constructor is really only used by serialization.
Door::Door(const Symbol& new_symbol)
  : Entrance(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_DOOR, new_symbol)
{
}

// By default, doors are made of wood.
Door::Door(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state)
  : Entrance(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_DOOR, new_symbol, new_lock, new_state)
{
}

string Door::get_open_message_sid() const
{
  return ActionTextKeys::ACTION_OPEN_DOOR;
}

string Door::get_close_message_sid() const
{
  return ActionTextKeys::ACTION_CLOSE_DOOR;
}

Feature* Door::clone()
{
  return new Door(*this);
}

bool Door::get_is_blocking() const
{
  // Only closed doors are blocking.
  return (state.get_state() == EntranceStateType::ENTRANCE_TYPE_CLOSED);
}

ClassIdentifier Door::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DOOR;
}

// Entrance

// This constructor is only used by the serialization code
Entrance::Entrance(const string& new_desc_sid, const Symbol& new_symbol)
: Feature(new_desc_sid, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), state(EntranceStateType::ENTRANCE_TYPE_OPEN), maximum_size(CreatureSize::CREATURE_SIZE_BEHEMOTH)
{
}

Entrance::Entrance(const string& new_desc_sid, const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state)
: Feature(new_desc_sid, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), state(new_state), maximum_size(CreatureSize::CREATURE_SIZE_BEHEMOTH)
{
  set_lock(new_lock);
}

bool Entrance::operator==(const Entrance& entr) const
{
  bool result = Feature::operator==(entr);

  result = result && (state == entr.state);
  result = result && (maximum_size == entr.maximum_size);

  return result;
}

void Entrance::set_state(const EntranceState& new_state)
{
  state = new_state;
}

EntranceState Entrance::get_state() const
{
  return state;
}

EntranceState& Entrance::get_state_ref()
{
  return state;
}

Symbol Entrance::get_symbol() const
{
  Symbol s = state.get_symbol();
  s.set_colour(get_colour());

  return s;
}

bool Entrance::get_is_entrance() const
{
  return true;
}

void Entrance::set_maximum_size(const CreatureSize new_size)
{
  maximum_size = new_size;
}

CreatureSize Entrance::get_maximum_size() const
{
  return maximum_size;
}

bool Entrance::can_handle(const bool feature_tile_occupied) const
{
  // entrances can only be handled if the space is not occupied.
  return (!feature_tile_occupied);
}

bool Entrance::can_open() const
{
  return true;
}

bool Entrance::can_lock() const
{
  return true;
}

bool Entrance::open()
{
  bool result = false;

  EntranceState& st = get_state_ref();

  if (st.get_state() == EntranceStateType::ENTRANCE_TYPE_CLOSED)
  {
    st.set_state(EntranceStateType::ENTRANCE_TYPE_OPEN);
    result = true;
  }

  return result;
}

bool Entrance::close()
{
  bool result = false;

  EntranceState& st = get_state_ref();

  if (st.get_state() == EntranceStateType::ENTRANCE_TYPE_OPEN)
  {
    st.set_state(EntranceStateType::ENTRANCE_TYPE_CLOSED);
    result = true;
  }

  return result;
}

string Entrance::get_handle_message_sid() const
{
  string handle_message_sid;
  EntranceStateType entrance_state = state.get_state();

  switch (entrance_state)
  {
    case EntranceStateType::ENTRANCE_TYPE_DESTROYED:
      handle_message_sid = ActionTextKeys::ACTION_DOOR_DESTROYED;
      break;
    case EntranceStateType::ENTRANCE_TYPE_OPEN:
      handle_message_sid = get_open_message_sid();
      break;
    case EntranceStateType::ENTRANCE_TYPE_CLOSED:
    default:
      handle_message_sid = get_close_message_sid();
      break;
  }

  return handle_message_sid;
}

bool Entrance::serialize(ostream& stream) const
{
  Feature::serialize(stream);

  // Entrance-specific values.
  state.serialize(stream);
  Serialize::write_enum(stream, maximum_size);

  return true;
}

bool Entrance::deserialize(istream& stream)
{
  Feature::deserialize(stream);

  // Entrance-specific values.
  state.deserialize(stream);
  Serialize::read_enum(stream, maximum_size);

  return true;
}

ClassIdentifier Entrance::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ENTRANCE;
}

// Gate

Gate::Gate(const Symbol& new_symbol)
  : Entrance(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GATE, new_symbol)
{
}

// Gates are always made of iron
Gate::Gate(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state)
  : Entrance(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GATE, new_symbol, new_lock, new_state)
{
  set_material_type(MaterialType::MATERIAL_TYPE_IRON);
}

string Gate::get_open_message_sid() const
{
  return ActionTextKeys::ACTION_OPEN_GATE;
}

string Gate::get_close_message_sid() const
{
  return ActionTextKeys::ACTION_CLOSE_GATE;
}

Feature* Gate::clone()
{
  return new Gate(*this);
}

bool Gate::get_is_blocking() const
{
  return (state.get_state() == EntranceStateType::ENTRANCE_TYPE_CLOSED);
}

ClassIdentifier Gate::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GATE;
}

// Fence

Fence::Fence(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FENCE, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

bool Fence::get_is_blocking() const
{
  return true;
}

Feature* Fence::clone()
{
  return new Fence(*this);
}

ClassIdentifier Fence::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FENCE;
}

// FirePillar
FirePillar::FirePillar(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FIRE_PILLAR, MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
  shimmer_colours = ShimmerColours({ Colour::COLOUR_RED, Colour::COLOUR_BOLD_RED, Colour::COLOUR_BOLD_YELLOW }, 75);
}

Feature* FirePillar::clone()
{
  return new FirePillar(*this);
}

bool FirePillar::get_is_blocking() const
{
  return true;
}

ClassIdentifier FirePillar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FIRE_PILLAR;
}
// FIXME: Still need to add lit/unlit state.

// Forge

Forge::Forge(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FORGE, MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Forge::clone()
{
  return new Forge(*this);
}

ClassIdentifier Forge::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FORGE;
}

// Fountain
Fountain::Fountain(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FOUNTAIN, MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Fountain::clone()
{
  return new Fountain(*this);
}

ClassIdentifier Fountain::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FOUNTAIN;
}

// JewelerWorkbench
JewelerWorkbench::JewelerWorkbench(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_JEWELER_WORKBENCH, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* JewelerWorkbench::clone()
{
  return new JewelerWorkbench(*this);
}

ClassIdentifier JewelerWorkbench::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH;
}

// Kiln

Kiln::Kiln(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KILN, MaterialType::MATERIAL_TYPE_CLAY, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Kiln::clone()
{
  return new Kiln(*this);
}

ClassIdentifier Kiln::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KILN;
}

// Pew and EastWestPew
Pew::Pew(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PEW, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Pew::clone()
{
  return new Pew(*this);
}

float Pew::get_piety_loss_multiplier() const
{
  return 0.5f;
}

ClassIdentifier Pew::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PEW;
}

EastWestPew::EastWestPew(const Symbol& new_symbol)
  : Pew(new_symbol)
{
}

Feature* EastWestPew::clone()
{
  return new EastWestPew(*this);
}

ClassIdentifier EastWestPew::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EAST_WEST_PEW;
}

// Pulper

Pulper::Pulper(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PULPER, MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Pulper::clone()
{
  return new Pulper(*this);
}

ClassIdentifier Pulper::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PULPER;
}

// RegularStatues and PetrifiedStatues

RegularStatue::RegularStatue(const Symbol& new_symbol)
  : Feature("", MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

bool RegularStatue::get_is_blocking() const
{
  return true;
}

ClassIdentifier RegularStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_REGULAR_STATUE;
}

// Petrified corpses
PetrifiedCorpseStatue::PetrifiedCorpseStatue(const Symbol& new_symbol)
  : RegularStatue(new_symbol)
{
}

PetrifiedCorpseStatue::PetrifiedCorpseStatue(const Symbol& new_symbol, const string& corpse_sid)
  : RegularStatue(new_symbol), corpse_description_sid(corpse_sid)
{
}

bool PetrifiedCorpseStatue::operator==(const PetrifiedCorpseStatue& pcs) const
{
  bool result = RegularStatue::operator==(pcs);

  result = result && (corpse_description_sid == pcs.corpse_description_sid);

  return result;
}

void PetrifiedCorpseStatue::set_corpse_description_sid(const string& new_corpse_description_sid)
{
  corpse_description_sid = new_corpse_description_sid;
}

string PetrifiedCorpseStatue::get_corpse_description_sid() const
{
  return corpse_description_sid;
}

pair<string, vector<string>> PetrifiedCorpseStatue::get_description_and_replacement_sids() const
{
  vector<string> replacement_sids;
  string desc_sid = get_description_sid();

  if (!corpse_description_sid.empty())
  {
    replacement_sids.push_back(corpse_description_sid);
  }

  return make_pair(desc_sid, replacement_sids);
}

Feature* PetrifiedCorpseStatue::clone()
{
  return new PetrifiedCorpseStatue(*this);
}

bool PetrifiedCorpseStatue::serialize(ostream& stream) const
{
  RegularStatue::serialize(stream);
  Serialize::write_string(stream, corpse_description_sid);

  return true;
}

bool PetrifiedCorpseStatue::deserialize(istream& stream)
{
  RegularStatue::deserialize(stream);
  Serialize::read_string(stream, corpse_description_sid);

  return true;
}

string PetrifiedCorpseStatue::get_description_sid() const
{
  if (!corpse_description_sid.empty())
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PETRIFIED_CORPSE_STATUE_WITH_DESC;
  }
  else
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PETRIFIED_CORPSE_STATUE;
  }
}

ClassIdentifier PetrifiedCorpseStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE;
}

// Sarcophagus

Sarcophagus::Sarcophagus(const Symbol& new_symbol)
  : Feature("", MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Sarcophagus::Sarcophagus(const Symbol& new_symbol, const MaterialType material_type)
  : Feature("", material_type, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

bool Sarcophagus::operator==(const Sarcophagus& sar) const
{
  bool result = Feature::operator==(sar);

  result = result && (inscription_sid == sar.inscription_sid);

  return result;
}

Feature* Sarcophagus::clone()
{
  return new Sarcophagus(*this);
}

pair<string, vector<string>> Sarcophagus::get_description_and_replacement_sids() const
{
  string message_sid = get_description_sid();

  vector<string> replacements;
  string inscription = get_inscription_sid();

  if (!inscription.empty())
  {
    replacements.push_back(inscription);
  }

  return make_pair(message_sid, replacements);
}

string Sarcophagus::get_description_sid() const
{
  if (!inscription_sid.empty())
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SARCOPHAGUS;
  }
  else
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SARCOPHAGUS_NO_INSCR;
  }
}

void Sarcophagus::set_inscription_sid(const string& new_inscription_sid)
{
  inscription_sid = new_inscription_sid;
}

string Sarcophagus::get_inscription_sid() const
{
  return inscription_sid;
}

bool Sarcophagus::serialize(ostream& stream) const
{
  Feature::serialize(stream);
  Serialize::write_string(stream, inscription_sid);

  return true;
}

bool Sarcophagus::deserialize(istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_string(stream, inscription_sid);

  return true;
}

ClassIdentifier Sarcophagus::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SARCOPHAGUS;
}

// Sign

Sign::Sign(const Symbol& new_symbol, const string& new_text_sid)
  : Feature(new_text_sid, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Sign::clone()
{
  return new Sign(*this);
}

pair<string, vector<string>> Sign::get_description_and_replacement_sids() const
{
  vector<string> replace = { get_description_sid() };
  return make_pair(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SIGN, replace);
}

ClassIdentifier Sign::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SIGN;
}

// SlotMachine

SlotMachine::SlotMachine(const Symbol& new_symbol, const MaterialType material, const int new_cost, const int new_pct_chance_win, const float new_payout_multiplier)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SLOT_MACHINE, material, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol),
  cost(new_cost),
  pct_chance_win(new_pct_chance_win),
  payout_multiplier(new_payout_multiplier)
{
}

SlotMachine::SlotMachine(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SLOT_MACHINE, MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), cost(1), pct_chance_win(0), payout_multiplier(0.0f)
{
}

SlotMachine::SlotMachine(const Symbol& new_symbol, const MaterialType material_type)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SLOT_MACHINE, material_type, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol),
  cost(1), pct_chance_win(0), payout_multiplier(0.0f)
{
}

bool SlotMachine::operator==(const SlotMachine& sm) const
{
  bool result = Feature::operator==(sm);

  result = result && (cost == sm.cost);
  result = result && (pct_chance_win == sm.pct_chance_win);
  result = result && fequal(payout_multiplier, sm.get_payout_multiplier());

  return result;
}

void SlotMachine::set_cost(const int new_cost)
{
  cost = new_cost;
}

int SlotMachine::get_cost() const
{
  return cost;
}

void SlotMachine::set_pct_chance_win(const int new_pct_chance_win)
{
  pct_chance_win = new_pct_chance_win;
}

int SlotMachine::get_pct_chance_win() const
{
  return pct_chance_win;
}

void SlotMachine::set_payout_multiplier(const float new_payout_multiplier)
{
  payout_multiplier = new_payout_multiplier;
}

float SlotMachine::get_payout_multiplier() const
{
  return payout_multiplier;
}

Colour SlotMachine::get_colour() const
{
  return static_cast<Colour>(RNG::range(static_cast<int>(Colour::COLOUR_BOLD_RED), static_cast<int>(Colour::COLOUR_BOLD_WHITE)));
}

Feature* SlotMachine::clone()
{
  return new SlotMachine(*this);
}

bool SlotMachine::serialize(ostream& stream) const
{
  Feature::serialize(stream);

  Serialize::write_int(stream, cost);
  Serialize::write_int(stream, pct_chance_win);
  Serialize::write_float(stream, payout_multiplier);

  return true;
}

bool SlotMachine::deserialize(istream& stream)
{
  Feature::deserialize(stream);

  Serialize::read_int(stream, cost);
  Serialize::read_int(stream, pct_chance_win);
  Serialize::read_float(stream, payout_multiplier);

  return true;
}

ClassIdentifier SlotMachine::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SLOT_MACHINE;
}

// StoneMarker

StoneMarker::StoneMarker(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_STONE_MARKER, MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* StoneMarker::clone()
{
  return new StoneMarker(*this);
}

float StoneMarker::get_hp_regeneration_multiplier() const
{
  return 1.0f;
}

float StoneMarker::get_ap_regeneration_multiplier() const
{
  return 0.1f;
}

ClassIdentifier StoneMarker::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STONE_MARKER;
}

// Table

Table::Table(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TABLE, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Table::clone()
{
  return new Table(*this);
}

ClassIdentifier Table::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TABLE;
}

// Tannery


Tannery::Tannery(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TANNERY, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Tannery::clone()
{
  return new Tannery(*this);
}

ClassIdentifier Tannery::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TANNERY;
}

// Trap

Trap::Trap(const Symbol& new_symbol)
  : Feature("", MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol, 1 /* 1 use by default - will be set later */), triggered(false), trigger_symbol(Symbol('?', Colour::COLOUR_WHITE)), effect(EffectType::EFFECT_TYPE_NULL)
{
}

bool Trap::operator==(const Trap& trap) const
{
  bool result = (Feature::operator==(trap));
  result = result && (triggered == trap.triggered);
  result = result && (id == trap.id);
  result = result && (trigger_message_sid == trap.trigger_message_sid);
  result = result && (trigger_symbol == trap.trigger_symbol);
  result = result && (player_damage_message_sid == trap.player_damage_message_sid);
  result = result && (item_id == trap.item_id);
  result = result && (damage == trap.damage);
  result = result && (effect == trap.effect);

  return result;
}

Trap* Trap::clone()
{
  return new Trap(*this);
}

Trap* Trap::clone_and_randomize_uses()
{
  Trap* trap = clone();

  if (trap)
  {
    // Jiggle the number of uses.
    int num_uses = trap->get_uses();

    if (num_uses > 1)
    {
      // 20% chance of +1 use.  5% chance of -1.
      if (RNG::percent_chance(20))
      {
        num_uses++;
      }
      else if (RNG::percent_chance(5))
      {
        num_uses--;
      }

      trap->set_uses(num_uses);
    }
  }

  return trap;
}

void Trap::set_is_hidden(const bool new_hidden)
{
  triggered = (new_hidden == false);
}

bool Trap::get_is_hidden() const
{
  return !triggered;
}

// Traps are dangerous.
// That's, uh, why we call them traps --
// only if triggered.
bool Trap::get_is_dangerous() const
{
  return triggered;
}

bool Trap::apply_on_movement(std::shared_ptr<Creature> creature) const
{
  // If the creature is flying, the trap won't be triggered on movement.
  if (creature && (creature->has_status(StatusIdentifiers::STATUS_ID_FLYING) || creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL)))
  {
    return false;
  }

  bool apply_trap = true;

  // A successful detection check is required to not trigger a trap.
  int detection_value = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DETECTION);

  // If the trap has already been triggered, the creature has two
  // attempts to not set it off on movement, since its presence is
  // known.
  int num_chances = triggered ? 2 : 1;

  for (int i = 0; i < num_chances; i++)
  {
    if (RNG::percent_chance(detection_value))
    {
      apply_trap = false;
    }
  }

  return apply_trap;
}

void Trap::set_triggered(const bool new_triggered)
{
  triggered = new_triggered;
}

bool Trap::get_triggered() const
{
  return triggered;
}

// Other features (fountains, fire pillars, etc) are class-based and 
// differentiated by their class ID. Traps are just configurations of a Trap 
// object, and are differentiated (arrow trap, fireball trap, etc) by their ID.
void Trap::set_id(const string& new_id)
{
  id = new_id;
}

string Trap::get_id() const
{
  return id;
}

void Trap::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

void Trap::set_trigger_message_sid(const string& new_trigger_message_sid)
{
  trigger_message_sid = new_trigger_message_sid;
}

string Trap::get_trigger_message_sid() const
{
  return trigger_message_sid;
}

void Trap::set_trigger_symbol(const Symbol& new_trigger_symbol)
{
  trigger_symbol = new_trigger_symbol;
}

Symbol Trap::get_trigger_symbol() const
{
  return trigger_symbol;
}

void Trap::set_player_damage_message_sid(const string& new_player_damage_message_sid)
{
  player_damage_message_sid = new_player_damage_message_sid;
}

string Trap::get_player_damage_message_sid() const
{
  return player_damage_message_sid;
}

void Trap::set_colour(const Colour new_colour)
{
  symbol.set_colour(new_colour);
}

Colour Trap::get_colour() const
{
  return symbol.get_colour();
}

void Trap::set_item_id(const std::string& new_item_id)
{
  item_id = new_item_id;
}

string Trap::get_item_id() const
{
  return item_id;
}

bool Trap::has_items() const
{
  return (!item_id.empty() && (uses > 0));
}

void Trap::set_damage(const Damage& new_damage)
{
  damage = new_damage;
}

Damage Trap::get_damage() const
{
  return damage;
}

void Trap::set_effect(const EffectType new_effect)
{
  effect = new_effect;
}

EffectType Trap::get_effect() const
{
  return effect;
}

string Trap::get_description_sid() const
{
  if (description_sid.empty())
  {
    return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_TRAP_GENERIC;
  }
  else
  {
    return description_sid;
  }
}

bool Trap::serialize(std::ostream& stream) const
{
  bool result = Feature::serialize(stream);

  Serialize::write_bool(stream, triggered);
  Serialize::write_string(stream, id);
  Serialize::write_string(stream, trigger_message_sid);
  trigger_symbol.serialize(stream);
  Serialize::write_string(stream, player_damage_message_sid);
  Serialize::write_string(stream, item_id);
  damage.serialize(stream);
  Serialize::write_enum(stream, effect);

  return result;
}

bool Trap::deserialize(istream& stream)
{
  bool result = Feature::deserialize(stream);

  Serialize::read_bool(stream, triggered);
  Serialize::read_string(stream, id);
  Serialize::read_string(stream, trigger_message_sid);
  trigger_symbol.deserialize(stream);
  Serialize::read_string(stream, player_damage_message_sid);
  Serialize::read_string(stream, item_id);
  damage.deserialize(stream);
  Serialize::read_enum(stream, effect);

  return result;
}

ClassIdentifier Trap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TRAP;
}

// WheelAndLoom

WheelAndLoom::WheelAndLoom(const Symbol& new_symbol)
  : Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WHEEL_AND_LOOM, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* WheelAndLoom::clone()
{
  return new WheelAndLoom(*this);
}

ClassIdentifier WheelAndLoom::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM;
}

#ifdef UNIT_TESTS
#include "unit_tests/AllAltars_test.cpp"
#include "unit_tests/AllEntrances_test.cpp"
#include "unit_tests/Barrel_test.cpp"
#include "unit_tests/Bed_test.cpp"
#include "unit_tests/Bench_test.cpp"
#include "unit_tests/DecorativeStatues_test.cpp"
#include "unit_tests/EastWestPew_test.cpp"
#include "unit_tests/Fence_test.cpp"
#include "unit_tests/FirePillar_test.cpp"
#include "unit_tests/Forge_test.cpp"
#include "unit_tests/Fountain_test.cpp"
#include "unit_tests/JewelerWorkbench_test.cpp"
#include "unit_tests/Pew_test.cpp"
#include "unit_tests/Pulper_test.cpp"
#include "unit_tests/RegularStatues_test.cpp"
#include "unit_tests/Sarcophagus_test.cpp"
#include "unit_tests/Sign_test.cpp"
#include "unit_tests/SlotMachine_test.cpp"
#include "unit_tests/StoneMarker_test.cpp"
#include "unit_tests/Table_test.cpp"
#include "unit_tests/Tannery_test.cpp"
#include "unit_tests/Trap_test.cpp"
#include "unit_tests/WheelAndLoom_test.cpp"
#endif
