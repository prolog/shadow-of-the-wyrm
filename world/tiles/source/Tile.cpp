#include <sstream>
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "DecisionStrategyProperties.hpp"
#include "DigChancesFactory.hpp"
#include "Inventory.hpp"
#include "FeatureGenerator.hpp"
#include "InventoryFactory.hpp"
#include "Log.hpp"
#include "MapFactory.hpp"
#include "NullInventory.hpp"
#include "Serialize.hpp"
#include "Tile.hpp"
#include "WeatherProperties.hpp"

using namespace std;

// Routines for creating and setting/getting attributes of a given Tile.
Tile::Tile(const int new_hardness)
: hardness(new_hardness)
{
  init();
}

Tile::Tile(const DigChances& dc)
: hardness(0), dig_chances(dc)
{
  init();
}

void Tile::init()
{
  // JCD FIXME: Not working because virtual functions don't work
  // until after the object is fully constructed.
  if (hardness > 0)
  {
    items = std::make_shared<NullInventory>();
  }
  else
  {
    items = std::make_shared<Inventory>();
  }

  set_default_properties();
  tile_type = TileType::TILE_TYPE_UNDEFINED;
  tile_subtype = TileType::TILE_TYPE_UNDEFINED;
}

Tile::~Tile()
{
}

bool Tile::operator==(const Tile& tile) const
{
  bool result = true;

  result = result && (illuminated == tile.illuminated);
  result = result && (explored == tile.explored);
  result = result && (viewed == tile.viewed);
  result = result && (submerged == tile.submerged);
  result = result && (tile_type == tile.tile_type);
  result = result && (tile_subtype == tile.tile_subtype);
  result = result && (hardness == tile.hardness);
  result = result && ((creature && tile.creature) || (!creature && !tile.creature));

  result = result && (additional_properties == tile.additional_properties);

  if (result && creature)
  {
    result = result && (*creature == *tile.creature);
  }

  result = result && ((feature && tile.feature) || (!feature && !tile.feature));

  if (result && feature)
  {
    result = result && (*feature == *tile.feature);
  }

  result = result && (items && tile.items && *items == *(tile.items));

  result = result && (map_exits.size() == tile.map_exits.size());

  if (result)
  {
    TileExitMap map2 = tile.map_exits;
    TileExitMap::const_iterator t_it = map_exits.begin();
    TileExitMap::const_iterator t_it2 = map2.begin();

    while (t_it != map_exits.end())
    {
      result = result && (*t_it->second == *t_it2->second);

      if (!result) break;

      t_it++;
      t_it2++;
    }
  }

  result = result && (dig_chances == tile.dig_chances);

  return result;
}

bool Tile::display_description_on_arrival() const
{
  return false;
}

void Tile::set_extra_description_sid(const string& new_extra_description_sid)
{
  set_additional_property(TileProperties::TILE_PROPERTY_EXTRA_DESCRIPTION_SID, new_extra_description_sid);
}

// Get all the extra descriptions that should be displayed for the tile.
// These are any properties that contain "EXTRA_DESCRIPTION" in their key.
vector<string> Tile::get_extra_description_sids() const
{
  vector<string> extra_sids;

  for (const auto& p_pair : additional_properties)
  {
    if (p_pair.first.find("EXTRA_DESCRIPTION") != std::string::npos)
    {
      extra_sids.push_back(p_pair.second);
    }
  }

  return extra_sids;
}

bool Tile::has_extra_description() const
{
  for (const auto& p_pair : additional_properties)
  {
    if (p_pair.first.find("EXTRA_DESCRIPTION") != std::string::npos)
    {
      return true;
    }
  }

  return false;
}

bool Tile::has_name() const
{
  return has_additional_property(TileProperties::TILE_PROPERTY_NAME);
}

void Tile::set_name(const string& name)
{
  set_additional_property(TileProperties::TILE_PROPERTY_NAME, name);
}

string Tile::get_name() const
{
  return get_additional_property(TileProperties::TILE_PROPERTY_NAME);
}

void Tile::set_engraving_sid(const string& new_engraving_sid)
{
  set_additional_property(TileProperties::TILE_PROPERTY_ENGRAVING_SID, new_engraving_sid);
}

string Tile::get_engraving_sid() const
{
  return get_additional_property(TileProperties::TILE_PROPERTY_ENGRAVING_SID);
}

bool Tile::has_engraving() const
{
  return has_additional_property(TileProperties::TILE_PROPERTY_ENGRAVING_SID);
}

void Tile::set_inscription_sid(const string& new_inscription_sid)
{
  set_additional_property(TileProperties::TILE_PROPERTY_INSCRIPTION_SID, new_inscription_sid);
}

string Tile::get_inscription_sid() const
{
  return get_additional_property(TileProperties::TILE_PROPERTY_INSCRIPTION_SID);
}

bool Tile::has_inscription() const
{
  return has_additional_property(TileProperties::TILE_PROPERTY_INSCRIPTION_SID);
}

bool Tile::has_been_dug() const
{
  string prop = get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG);

  return (prop == to_string(true));
}

bool Tile::has_been_planted() const
{
  string prop = get_additional_property(TileProperties::TILE_PROPERTY_PLANTED);

  return (prop == to_string(true));
}

bool Tile::has_remains() const
{
  string prop = get_additional_property(TileProperties::TILE_PROPERTY_REMAINS);

  return (prop == to_string(true));
}

void Tile::set_custom_map_id(const string& map_generator_id)
{
  set_additional_property(TileProperties::TILE_PROPERTY_CUSTOM_MAP_ID, map_generator_id);
}

string Tile::get_custom_map_id() const
{
  return get_additional_property(TileProperties::TILE_PROPERTY_CUSTOM_MAP_ID);
}

bool Tile::has_custom_map_id() const
{
  return has_additional_property(TileProperties::TILE_PROPERTY_CUSTOM_MAP_ID);
}

void Tile::set_additional_properties(const map<string, string>& new_props)
{
  additional_properties = new_props;
}

void Tile::set_additional_property(const string& property_name, const string& property_value)
{
  additional_properties[property_name] = property_value;
}

string Tile::get_additional_property(const string& property_name) const
{
  string property_value;

  map<string, string>::const_iterator t_it = additional_properties.find(property_name);
  if (t_it != additional_properties.end())
  {
    property_value = t_it->second;
  }

  return property_value;
}

size_t Tile::remove_additional_property(const string& property_name)
{
  return additional_properties.erase(property_name);
}

map<string, string> Tile::get_additional_properties() const
{
  return additional_properties;
}

bool Tile::has_additional_property(const std::string& property_name) const
{
  string property_value = get_additional_property(property_name);
  return (!property_value.empty());
}

void Tile::set_default_properties()
{
  illuminated = true;
  explored    = false;
  viewed      = false;
  submerged   = false;
}

void Tile::set_illuminated(const bool new_illuminated)
{
  illuminated = new_illuminated;
}

bool Tile::get_illuminated() const
{
  return illuminated;
}

bool Tile::get_is_staircase() const
{
  TileType val = get_tile_type();
  return (val == TileType::TILE_TYPE_UP_STAIRCASE || val == TileType::TILE_TYPE_DOWN_STAIRCASE);
}

bool Tile::get_is_available_for_creature(CreaturePtr creature) const
{
  bool avail = !get_is_blocking_ignore_present_creature(creature);
  
  // Does the tile have race restrictions?  If so, does the creature meet them?
  // Similarly for any creature ID restrictions?
  if (avail && 
      (((has_race_restrictions() && 
       !is_race_allowed(creature->get_race_id()) && 
        String::to_bool(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_IGNORE_RACIAL_MOVEMENT_RESTRICTIONS)) == false))
    || (has_creature_id_restrictions() && !is_creature_id_allowed(creature->get_id()))))
  {
    avail = false;
  }
  
  return avail;
}

// The conditions are broken up for easier debugging.
//
// A tile should only be blocking from the perspective of a particular
// incorporeal creature (ghost, spirit, etc) if the tile has another
// creature present.
bool Tile::get_is_blocking(CreaturePtr perspective_creature) const
{
  bool tile_blocking = get_is_blocking_ignore_present_creature(perspective_creature);
  
  if (creature != nullptr)
  {
    string creature_id = creature->get_id();

    if (perspective_creature && creature_id != perspective_creature->get_id())
    {
      // Check to see if the searching creature is hostile to this creature.
      // If the creature's not hostile, consider the tile blocking; otherwise,
      // use whatever the current value of tile_blocking is (based on movement,
      // features, etc).
      if (!perspective_creature->get_decision_strategy()->get_threats_ref().has_threat(creature->get_id()).first)
      {
        // Is it the leader's tile? Or, are we supposed to be following the 
        // creature? If so, don't consider it blocking
        string follow_id = perspective_creature->get_decision_strategy()->get_property(DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID);
        string leader_id = perspective_creature->get_leader_id();

        if ((follow_id != creature_id) && (leader_id != creature_id))
        {
          tile_blocking = true;
        }
      }
    }
  }

  return tile_blocking;
}

// Check to see if the tile is blocking, checking as if the present creature
// (if there is one) was not there.
bool Tile::get_is_blocking_ignore_present_creature(CreaturePtr perspective_creature) const
{
  bool tile_blocking = false;
  bool perspective_creature_incorporeal = perspective_creature && perspective_creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);

  if (get_movement_multiplier() == 0 && !perspective_creature_incorporeal)
  {
    tile_blocking = true;
  }

  if (feature && feature->get_is_blocking() && !perspective_creature_incorporeal)
  {
    tile_blocking = true;
  }

  return tile_blocking;
}

// JCD FIXME: If items can ever be incorporeal, this needs to be updated.
bool Tile::get_is_blocking_for_item(ItemPtr item) const
{
  bool tile_blocking = false;

  if (get_movement_multiplier() == 0)
  {
    tile_blocking = true;
  }

  if (feature && feature->get_is_blocking())
  {
    tile_blocking = true;
  }

  return tile_blocking;
}

int Tile::get_movement_multiplier() const
{
  return 1;
}

void Tile::set_explored(const bool new_explored)
{
  explored = new_explored;
}

bool Tile::get_explored() const
{
  return explored;
}

void Tile::set_viewed(const bool new_viewed)
{
  viewed = new_viewed;
}

bool Tile::get_viewed() const
{
  return viewed;
}

void Tile::set_submerged(const bool new_submerged)
{
  submerged = new_submerged;
}

bool Tile::get_submerged() const
{
  return submerged;
}

bool Tile::has_feature() const
{
  return (feature != nullptr);
}

bool Tile::has_blocking_feature() const
{
  return (feature && feature->get_is_blocking());
}

void Tile::set_feature(FeaturePtr new_feature)
{
  if (new_feature != nullptr)
  {
    // Do we need to update the dig chances from what was there previously?
    pair<bool, DigChances> update_dig_chances = DigChancesFactory::create_feature_dig_chances(new_feature->get_class_identifier());

    if (update_dig_chances.first)
    {
      dig_chances = update_dig_chances.second;
    }
  }

  feature = new_feature;
}

void Tile::remove_feature()
{
  feature = nullptr;
}

FeaturePtr Tile::get_feature()
{
  return feature;
}

bool Tile::has_creature() const
{
  return (creature != nullptr);
}

void Tile::set_creature(const CreaturePtr& new_creature)
{
  ostringstream ss;
  
  if (creature != nullptr && new_creature != nullptr)
  {
    ss << creature->get_id() << " being replaced by " << new_creature->get_id();
    Log::instance().debug(ss.str());
  }

  creature = new_creature;
  
  if (creature->get_is_player())
  {
    set_explored(true);
  }
}

void Tile::remove_creature()
{
  creature = nullptr;
}

CreaturePtr Tile::get_creature() const
{
  return creature;
}

void Tile::add_items(IInventoryPtr new_items)
{
  if (items != nullptr)
  {
    const list<ItemPtr> new_items_raw = new_items->get_items_cref();

    for (ItemPtr i : new_items_raw)
    {
      if (i != nullptr)
      {
        items->merge_or_add(i, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }
  }
}

void Tile::set_items(IInventoryPtr new_items)
{
  items = new_items;
}

IInventoryPtr Tile::get_items()
{
  return items;
}

// Copy entities from the given tile to the current, but not overwriting
// any existing creature or feature.
void Tile::copy_entities(TilePtr tile)
{
  if (tile != nullptr)
  {
    if (creature == nullptr && tile->has_creature())
    {
      set_creature(tile->get_creature());
    }

    add_items(tile->get_items());

    if (feature == nullptr)
    {
      set_feature(tile->get_feature());
    }
  }
}
TileType Tile::get_tile_type() const
{
  return tile_type;
}

TileSuperType Tile::get_tile_super_type() const
{
  if (submerged)
  {
    return TileSuperType::TILE_SUPER_TYPE_WATER;
  }
  else
  {
    return get_tile_base_super_type();
  }
}

// All tiles are assumed to be ground tiles, unless the derived class declares otherwise.
TileSuperType Tile::get_tile_base_super_type() const
{
  return TileSuperType::TILE_SUPER_TYPE_GROUND;
}

// Tiles are assumed to have no water on them.
WaterType Tile::get_water_type() const
{
  return WaterType::WATER_TYPE_UNDEFINED;
}

bool Tile::get_is_frozen(const Season season) const
{
  if (season == Season::SEASON_WINTER 
   && get_water_type() == WaterType::WATER_TYPE_FRESH 
   && !submerged)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Tile::set_tile_subtype(const TileType new_tile_subtype)
{
  tile_subtype = new_tile_subtype;
}

TileType Tile::get_tile_subtype() const
{
  return tile_subtype;
}

TileType Tile::get_decomposition_tile_type() const
{
  return tile_type;
}

float Tile::get_breakage_multiplier() const
{
  return 0.0f;
}

vector<pair<pair<int, int>, string>> Tile::get_decomposition_item_ids() const
{
  vector<pair<pair<int, int>, string>> no_items;
  return no_items;
}

void Tile::set_hardness(const int new_hardness)
{
  hardness = new_hardness;
}

int Tile::get_hardness() const
{
  return hardness;
}

TileExitMap& Tile::get_tile_exit_map_ref()
{
  return map_exits;
}

bool Tile::get_is_blocking_visually(CreaturePtr creature) const
{
  return get_is_blocking(creature);
}

bool Tile::get_is_blocking_or_dangerous(CreaturePtr creature) const
{
  return get_dangerous(creature) || get_is_blocking(creature);
}

bool Tile::get_dangerous(CreaturePtr creature) const
{
  return false;
}

string Tile::get_danger_confirmation_sid() const
{
  string empty_sid;
  return empty_sid;
}

float Tile::get_piety_loss_multiplier() const
{
  float piety_mult = 1.0;

  if (feature != nullptr)
  {
    piety_mult = feature->get_piety_loss_multiplier();
  }

  return piety_mult;
}

void Tile::set_weather(const Weather& w)
{
  string wind_speed_s = std::to_string(w.get_wind_speed());
  set_additional_property(WeatherProperties::WEATHER_PROPERTIES_WIND_SPEED, wind_speed_s);
}

Weather Tile::get_weather() const
{
  string wind_speed = get_additional_property(WeatherProperties::WEATHER_PROPERTIES_WIND_SPEED);
  Weather weather(wind_speed);

  return weather;
}

// Transform a tile from an original tile type.  The new tile (this object)
// will be assumed to have the new tile type and subtype, but won't have
// any of the original's required values: creature, inventory, exits,
// certain flags, etc.  Copy those values over to this tile.
void Tile::transform_from(std::shared_ptr<Tile> original_tile)
{
  if (original_tile != nullptr)
  {
    // Keep the properties.
    // Copy everything else.
    // Copy over the inventory using the raw items.
    map<string, string> props = additional_properties;
    IInventoryPtr new_inv = items;

    *this = *original_tile;

    // Ensure the inventory is of the right type, so that dug tiles have real
    // inventories instead of null ones.
    list<ItemPtr> raw_items = original_tile->get_items()->get_items_ref();
    items = new_inv;
    items->add_items(raw_items);

    for (const auto& p_pair : props)
    {
      set_additional_property(p_pair.first, p_pair.second);
    }

    // Remove particular properties
    vector<string> props_to_remove = { TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG, TileProperties::TILE_PROPERTY_PLANTED };

    for (const auto& p : props_to_remove)
    {
      remove_additional_property(p);
    }
  }
}

float Tile::get_hp_regeneration_multiplier() const
{
  return 1.0f;
}

float Tile::get_ap_regeneration_multiplier() const
{
  return 1.0f;
}

void Tile::set_dig_chances(const DigChances& new_dig_chances)
{
  dig_chances = new_dig_chances;
}

DigChances Tile::get_dig_chances() const
{
  return dig_chances;
}

DigChances& Tile::get_dig_chances_ref()
{
  return dig_chances;
}

bool Tile::has_race_restrictions() const
{
  bool restr = false;

  string races = get_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_RACES);
  restr = (races.empty() == false);

  return restr;
}

bool Tile::is_race_allowed(const std::string& race_id) const
{
  bool allowed = true;

  string races = get_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_RACES);
  if (!races.empty())
  {
    vector<string> race_ids = String::create_string_vector_from_csv_string(races);
    auto r_it = std::find(race_ids.begin(), race_ids.end(), race_id);

    if (r_it == race_ids.end())
    {
      allowed = false;
    }
  }

  return allowed;
}

bool Tile::has_creature_id_restrictions() const
{
  bool restr = false;

  string cr_ids = get_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_CREATURE_IDS);
  restr = (cr_ids.empty() == false);

  return restr;
}

bool Tile::is_creature_id_allowed(const std::string& creature_id) const
{
  bool allowed = true;

  string creature_ids = get_additional_property(TileProperties::TILE_PROPERTY_ALLOWED_CREATURE_IDS);

  if (!creature_ids.empty())
  {
    vector<string> cr_ids = String::create_string_vector_from_csv_string(creature_ids);
    auto cr_it = std::find(cr_ids.begin(), cr_ids.end(), creature_id);

    if (cr_it == cr_ids.end())
    {
      allowed = false;
    }
  }

  return allowed;
}

SkillType Tile::get_treasure_skill() const
{
  return SkillType::SKILL_UNDEFINED;
}

bool Tile::has_treasure() const
{
  string treasure_difficulty_s = get_additional_property(TileProperties::TILE_PROPERTY_MIN_LORE_REQUIRED);

  if (!treasure_difficulty_s.empty() && String::to_int(treasure_difficulty_s) > 0)
  {
    return true;
  }

  return false;
}

bool Tile::serialize(ostream& stream) const
{
  Serialize::write_bool(stream, illuminated);
  Serialize::write_bool(stream, explored);
  Serialize::write_bool(stream, viewed);
  Serialize::write_bool(stream, submerged);
  Serialize::write_enum(stream, tile_type);
  Serialize::write_enum(stream, tile_subtype);
  Serialize::write_int(stream, hardness);

  Serialize::write_string_map(stream, additional_properties);

  if (creature)
  {
    Serialize::write_class_id(stream, creature->get_class_identifier());
    creature->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }

  if (feature)
  {
    Serialize::write_class_id(stream, feature->get_class_identifier());
    feature->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }
  
  Serialize::write_class_id(stream, items->get_class_identifier());
  items->serialize(stream);

  Serialize::write_size_t(stream, map_exits.size());

  for (const TileExitMap::value_type& tile_exit_map_pair : map_exits)
  {
    Direction d = tile_exit_map_pair.first;
    MapExitPtr map_exit = tile_exit_map_pair.second;

    Serialize::write_enum(stream, d);

    if (map_exit)
    {
      Serialize::write_class_id(stream, map_exit->get_class_identifier());
      map_exit->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  dig_chances.serialize(stream);

  return true;
}

bool Tile::deserialize(istream& stream)
{
  Serialize::read_bool(stream, illuminated);
  Serialize::read_bool(stream, explored);
  Serialize::read_bool(stream, viewed);
  Serialize::read_bool(stream, submerged);
  Serialize::read_enum(stream, tile_type);
  Serialize::read_enum(stream, tile_subtype);
  Serialize::read_int(stream, hardness);

  Serialize::read_string_map(stream, additional_properties);

  ClassIdentifier creature_clid;
  Serialize::read_class_id(stream, creature_clid);

  if (creature_clid != ClassIdentifier::CLASS_ID_NULL)
  {
    creature = std::make_shared<Creature>();
    creature->deserialize(stream);
  }

  ClassIdentifier feature_clid;
  Serialize::read_class_id(stream, feature_clid);

  if (feature_clid != ClassIdentifier::CLASS_ID_NULL)
  {
    FeaturePtr feature = FeatureGenerator::create_feature(feature_clid);
    if (!feature) return false;
    if (!feature->deserialize(stream)) return false;
    set_feature(feature);
  }

  ClassIdentifier items_class_id;
  Serialize::read_class_id(stream, items_class_id);

  items = InventoryFactory::create_inventory(items_class_id);
  items->deserialize(stream);

  size_t map_size;
  Serialize::read_size_t(stream, map_size);

  map_exits.clear();

  for (unsigned int i = 0; i < map_size; i++)
  {
    Direction d = Direction::DIRECTION_NORTH; // just a random default value - otherwise, compiler warnings.
    Serialize::read_enum(stream, d);

    ClassIdentifier map_exit_clid;
    Serialize::read_class_id(stream, map_exit_clid);
    if (map_exit_clid != ClassIdentifier::CLASS_ID_NULL)
    {
      MapExitPtr current_dir_map_exit = MapFactory::create_map_exit();
      current_dir_map_exit->deserialize(stream);
      map_exits.insert(make_pair(d, current_dir_map_exit));
    }
  }

  dig_chances.deserialize(stream);

  return true;
}

ClassIdentifier Tile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tile_test.cpp"
#endif
