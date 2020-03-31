#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureUtils.hpp"
#include "DeityTextKeys.hpp"
#include "EngineConversion.hpp"
#include "FieldOfViewStrategy.hpp"
#include "FieldOfViewStrategyFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "LineOfSightCalculator.hpp"
#include "MessageManagerFactory.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "SpellAdditionalProperties.hpp"
#include "StatisticTextKeys.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "ViewMapTranslator.hpp"

using namespace std;

CreatureUtils::CreatureUtils()
{
}

CreatureUtils::~CreatureUtils()
{
}

map<HungerLevel, string> CreatureUtils::hunger_message_sid_map;

// Initialize the map of message SIDs.  Messages are shown when the creature
// (the player, realistically) transitions to a new state.
void CreatureUtils::initialize_hunger_message_sid_map()
{
  hunger_message_sid_map.clear();

  hunger_message_sid_map = std::map<HungerLevel, std::string>{
    { HungerLevel::HUNGER_LEVEL_STUFFED, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STUFFED },
    { HungerLevel::HUNGER_LEVEL_FULL, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_FULL },
    { HungerLevel::HUNGER_LEVEL_NORMAL, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_NORMAL },
    { HungerLevel::HUNGER_LEVEL_HUNGRY, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_HUNGRY },
    { HungerLevel::HUNGER_LEVEL_STARVING, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STARVING },
    { HungerLevel::HUNGER_LEVEL_DYING, StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_DYING } };
}


// Add a message about a change in hunger status, if appropriate.
void CreatureUtils::add_hunger_level_message_if_necessary(CreaturePtr creature, const int old_hunger, const int new_hunger)
{
  HungerLevel old_level = HungerLevelConverter::to_hunger_level(old_hunger);
  HungerLevel new_level = HungerLevelConverter::to_hunger_level(new_hunger);

  if (old_level != new_level)
  {
    if (creature && creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();

      if (hunger_message_sid_map.empty())
      {
        initialize_hunger_message_sid_map();
      }

      string message_sid = hunger_message_sid_map[new_level];

      manager.add_new_message(StringTable::get(message_sid));
      manager.send();
    }
  }
}



string CreatureUtils::get_race_class_synopsis(CreaturePtr c)
{
  string synopsis;
  Game& game = Game::instance();

  string race_id = c->get_race_id();
  string class_id = c->get_class_id();
  RaceMap races = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();

  RacePtr race = races[race_id];
  ClassPtr current_class = classes[class_id];

  if (race && current_class)
  {
    synopsis = StringTable::get(race->get_race_abbreviation_sid()) + StringTable::get(current_class->get_class_abbreviation_sid());
    synopsis = String::add_trailing_spaces(synopsis, 5);
  }

  synopsis = String::add_trailing_spaces(synopsis, 5);

  return synopsis;
}

// Handle alignment change, including switching to a new religion, becoming
// a fallen champion, etc.
void CreatureUtils::handle_alignment_change(CreaturePtr creature, const int new_alignment)
{
  if (creature)
  {
    Alignment& a = creature->get_alignment_ref();
    AlignmentRange range_before = a.get_alignment_range();

    a.set_alignment(new_alignment);
    
    AlignmentRange range_after = a.get_alignment_range();
    Game& game = Game::instance();
    const DeityMap& deities = game.get_deities_cref();

    if (range_before != range_after)
    {
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

      // Champion?  Not anymore!
      ReligionManager rm;
      Religion& religion = creature->get_religion_ref();
      DeityPtr active_deity = rm.get_active_deity(creature);
      DeityStatus status = rm.get_active_deity_status(creature);

      if (status.get_champion_type() == ChampionType::CHAMPION_TYPE_CROWNED)
      {
        // The creature is hereby a fallen champion of all deities.
        for (auto deity_pair : deities)
        {
          string deity_id = deity_pair.second->get_id();

          DeityStatus cur_status = religion.get_deity_status(deity_id);
          cur_status.set_champion_type(ChampionType::CHAMPION_TYPE_FALLEN);

          religion.set_deity_status(deity_id, cur_status);
        }

        if (creature->get_is_player())
        {
          manager.add_new_message(StringTable::get(DeityTextKeys::DEITY_FALLEN_CHAMPION));
          manager.send();
        }

        religion.set_deity_status(active_deity->get_id(), status);
      }

      // Change religion.
      // Get all the deities for the new alignment range.
      vector<DeityPtr> potential_deities;

      for (auto deity_pair : deities)
      {
        DeityPtr deity = deity_pair.second;

        if (deity && !deity->get_id().empty() && (deity->get_alignment_range() == range_after))
        {
          potential_deities.push_back(deity);
        }
      }

      if (!potential_deities.empty())
      {
        // Pick one randomly.
        std::shuffle(potential_deities.begin(), potential_deities.end(), RNG::get_engine());

        // Make this the active deity for the creature.
        DeityPtr new_deity = potential_deities.at(0);
        religion.set_active_deity_id(new_deity->get_id());

        // Add a message about the new deity.
        if (creature->get_is_player())
        {
          manager.add_new_message(DeityTextKeys::get_deity_change_message(new_deity->get_name_sid()));
          manager.send();
        }
      }
    }
  }
}

// Is the creature the player, or in the player's line of sight?
bool CreatureUtils::is_player_or_in_los(CreaturePtr creature)
{
  bool result = false;

  if (creature != nullptr)
  {
    string creature_id = creature->get_id();

    if (creature_id == CreatureID::CREATURE_ID_PLAYER)
    {
      result = true;
    }
    else
    {
      Game& game = Game::instance();
      CreaturePtr player = game.get_current_player();
      MapPtr view_map = player->get_decision_strategy()->get_fov_map();
      map<string, CreaturePtr> view_creatures = view_map->get_creatures();

      if (view_creatures.find(creature_id) != view_creatures.end())
      {
        result = true;
      }
    }
  }

  return result;
}

void CreatureUtils::incr_str(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_str = creature->get_strength();
  int new_base_str = cr_str.get_base() + 1;

  int cur_str = cr_str.get_current();

  cr_str.set_base(new_base_str);
  cr_str.set_current(cur_str - (cur_str - new_base_str));

  creature->set_strength(cr_str);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_STRENGTH));
    manager.send();
  }
}

void CreatureUtils::incr_dex(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_dex = creature->get_dexterity();
  int new_base_dex = cr_dex.get_base() + 1;

  int cur_dex = cr_dex.get_current();

  cr_dex.set_base(new_base_dex);
  cr_dex.set_current(cur_dex - (cur_dex - new_base_dex));

  creature->set_dexterity(cr_dex);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_DEXTERITY));
    manager.send();
  }
}

void CreatureUtils::incr_agi(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_agi = creature->get_agility();
  int new_base_agi = cr_agi.get_base() + 1;

  int cur_agi = cr_agi.get_current();

  cr_agi.set_base(new_base_agi);
  cr_agi.set_current(cur_agi - (cur_agi - new_base_agi));

  creature->set_agility(cr_agi);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_AGILITY));
    manager.send();
  }
}

void CreatureUtils::incr_hea(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_hea = creature->get_health();
  int new_base_hea = cr_hea.get_base() + 1;

  int cur_hea = cr_hea.get_current();

  cr_hea.set_base(new_base_hea);
  cr_hea.set_current(cur_hea - (cur_hea - new_base_hea));

  creature->set_health(cr_hea);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_HEALTH));
    manager.send();
  }
}

void CreatureUtils::incr_int(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_int = creature->get_intelligence();
  int new_base_int = cr_int.get_base() + 1;

  int cur_int = cr_int.get_current();

  cr_int.set_base(new_base_int);
  cr_int.set_current(cur_int - (cur_int - new_base_int));

  creature->set_intelligence(cr_int);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_INTELLIGENCE));
    manager.send();
  }
}

void CreatureUtils::incr_wil(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_wil = creature->get_willpower();
  int new_base_wil = cr_wil.get_base() + 1;

  int cur_wil = cr_wil.get_current();

  cr_wil.set_base(new_base_wil);
  cr_wil.set_current(cur_wil - (cur_wil - new_base_wil));

  creature->set_willpower(cr_wil);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_WILLPOWER));
    manager.send();
  }
}

void CreatureUtils::incr_cha(CreaturePtr creature, const bool add_msg)
{
  Statistic cr_cha = creature->get_charisma();
  int new_base_cha = cr_cha.get_base() + 1;

  int cur_cha = cr_cha.get_current();

  cr_cha.set_base(new_base_cha);
  cr_cha.set_current(cur_cha - (cur_cha - new_base_cha));

  creature->set_charisma(cr_cha);

  if (add_msg)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_CHARISMA));
    manager.send();
  }
}

pair<bool, string> CreatureUtils::can_pick_up(CreaturePtr c, ItemPtr i)
{
  pair<bool, string> can_pu;
  can_pu.first = false;

  if (c != nullptr && i != nullptr)
  {
    CarryingCapacityCalculator ccc;
    uint total_items = ccc.calculate_carrying_capacity_total_items(c);

    can_pu.first = (i->get_type() == ItemType::ITEM_TYPE_CURRENCY || c->count_items() + i->get_quantity() <= total_items);

    if (!can_pu.first)
    {
      can_pu.second = ActionTextKeys::ACTION_PICK_UP_MAX_ITEMS;
    }
    else
    {
      can_pu.first = c->get_weight_carried() < ccc.calculate_overburdened_weight(c);

      if (!can_pu.first)
      {
        can_pu.second = ActionTextKeys::ACTION_PICK_UP_MAX_WEIGHT;
      }
    }
  }

  return can_pu;
}

RacePtr CreatureUtils::get_random_user_playable_race()
{
  Game& game = Game::instance();
  RaceMap  races = game.get_races_ref();
  vector<RacePtr> playable_races;
  RacePtr race;

  for (const auto& race_pair : races)
  {
    RacePtr race = race_pair.second;

    if (race && race->get_user_playable())
    {
      playable_races.push_back(race);
    }
  }

  if (!playable_races.empty())
  {
    race = playable_races.at(RNG::range(0, playable_races.size() - 1));
  }

  return race;
}

ClassPtr CreatureUtils::get_random_user_playable_class()
{
  Game& game = Game::instance();
  ClassMap classes = game.get_classes_ref();
  vector<ClassPtr> playable_classes;
  ClassPtr cur_class;

  for (const auto& class_pair : classes)
  {
    ClassPtr cur_class = class_pair.second;

    if (cur_class && cur_class->get_user_playable())
    {
      playable_classes.push_back(cur_class);
    }
  }

  if (!playable_classes.empty())
  {
    cur_class = playable_classes.at(RNG::range(0, playable_classes.size() - 1));
  }

  return cur_class;
}

DeityPtr CreatureUtils::get_random_deity_for_race(RacePtr race)
{
  Game& game = Game::instance();
  DeityMap deities = game.get_deities_cref();
  vector<string> allowable_deity_ids;
  DeityPtr deity;

  if (race != nullptr)
  {
    allowable_deity_ids = race->get_initial_deity_ids();
  }

  if (!allowable_deity_ids.empty())
  {
    string deity_id = allowable_deity_ids.at(RNG::range(0, allowable_deity_ids.size() - 1));
    deity = deities.at(deity_id);
  }

  return deity;
}

bool CreatureUtils::has_spell_for_situation_type(CreaturePtr creature, const SpellSituationType sst)
{
  bool has_spells = false;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    const SpellMap& sm = game.get_spells_ref();
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    SpellKnowledgeMap skm = sk.get_known_spells();

    for (const auto& skm_pair : skm)
    {
      string spell_id = skm_pair.first;

      const auto sm_it = sm.find(spell_id);
      if (sm_it != sm.end())
      {
        SpellShape ss = sm_it->second.get_shape();

        if (ss.get_spell_situation() == sst)
        {
          has_spells = true;
          break;
        }
      }
    }
  }

  return has_spells;
}

// Mark all modifiers for a particular identifier for deletion.
void CreatureUtils::mark_modifiers_for_deletion(CreaturePtr creature, const string& identifier, const StatusRemovalType sr)
{
  if (creature != nullptr && !identifier.empty())
  {
    map<double, vector<pair<string, Modifier>>>& creature_modifiers = creature->get_modifiers_ref();

    for (auto& cm_pair : creature_modifiers)
    {
      vector<pair<string, Modifier>>& modifiers = cm_pair.second;

      for (auto& mod : modifiers)
      {
        if (mod.first == identifier)
        {
          process_creature_modifier(creature, mod, sr);
        }
      }
    }
  }
}

// Finalize all the modifiers after a certain min expiry
void CreatureUtils::mark_modifiers_for_deletion(CreaturePtr creature, const double current_seconds, const double min_expiry, const StatusRemovalType sr)
{
  if (creature != nullptr)
  {
    map<double, vector<pair<string, Modifier>>>& creature_modifiers = creature->get_modifiers_ref();
    auto m_it = creature_modifiers.begin();

    while (m_it != creature_modifiers.end())
    {
      double modifier_expiry = m_it->first;

      if ((modifier_expiry >= min_expiry) && (modifier_expiry <= current_seconds))
      {
        process_creature_modifiers(creature, m_it->second, sr);
      }
      
      if (modifier_expiry > current_seconds)
      {
        // Since std::map is ordered by key, once we've hit modifiers that
        // are past the present moment in time, we can stop iterating.
        //
        // Check the modifier vs current seconds explicitly to avoid falling
        // into here when modifier_expiry < min_expiry.
        break;
      }

      m_it++;
    }
  }
}

// Process the current set of modifiers for the given second.
// Mark them as deleted, as well as any modifiers they're linked to.
void CreatureUtils::process_creature_modifiers(CreaturePtr creature, vector<pair<string, Modifier>>& modifiers, const StatusRemovalType sr)
{
  for (auto& mod_pair : modifiers)
  {
    process_creature_modifier(creature, mod_pair, sr);
  }
}

void CreatureUtils::process_creature_modifier(CreaturePtr creature, pair<string, Modifier>& mod_pair, const StatusRemovalType sr)
{
  // Don't process/remove permanent modifiers, and also don't attempt to
  // double-process a modifier already marked for deletion.
  if (mod_pair.second.get_permanent() == true || mod_pair.second.get_delete())
  {
    return;
  }
  
  string spell_id = mod_pair.first;
  mod_pair.second.set_delete(true);

  Modifier m = mod_pair.second;
  vector<pair<string, int>> statuses = m.get_affected_statuses();

  add_removal_message(creature, spell_id);

  for (const auto& status : statuses)
  {
    string status_id = status.first;

    if (creature->has_status(status_id))
    {
      Status st = creature->get_status(status_id);
      StatusEffectPtr status_p = StatusEffectFactory::create_status_effect(status_id, st.get_source_id());

      if (sr == StatusRemovalType::STATUS_REMOVAL_FINALIZE)
      {
        status_p->finalize_change(creature);
      }
      else
      {
        status_p->undo_change(creature);
      }
    }
  }
}

void CreatureUtils::apply_status_ailments(WearablePtr wearable, CreaturePtr creature)
{
  if (wearable != nullptr && creature != nullptr)
  {
    if (wearable != nullptr)
    {
      string creature_id = creature->get_id();
      StatusAilments sa = wearable->get_status_ailments();
      set<string> ailments = sa.get_ailments();

      for (const auto& ailment : ailments)
      {
        if (!creature->has_status(ailment))
        {
          ModifyStatisticsEffect mse;
          Modifier m;

          StatusEffectPtr status = StatusEffectFactory::create_status_effect(ailment, "");
          creature->set_status(ailment, { ailment, true, 1 /* JCD FIXME? */, creature_id });
          m.set_status(ailment, true);
          mse.set_spell_id(ailment); // set for easy rollback
          mse.apply_modifiers(creature, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, -1);

          if (status != nullptr)
          {
            IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
            manager.add_new_message(status->get_application_message(creature));
            manager.send();
          }
        }
      }
    }
  }
}

void CreatureUtils::remove_status_ailments_from_wearable(WearablePtr wearable, CreaturePtr creature)
{
  if (wearable != nullptr && creature != nullptr)
  {
    StatusAilments sa = wearable->get_status_ailments();
    set<string> ailments = sa.get_ailments();

    auto& cr_mods = creature->get_modifiers_ref();
    auto indefinite_mod_it = creature->get_modifiers_ref().find(-1);

    if (indefinite_mod_it != cr_mods.end())
    {
      vector<pair<string, Modifier>>& mods = indefinite_mod_it->second;

      for (pair<string, Modifier>& mod_pair : mods)
      {
        string status_id = mod_pair.first;
        if (mod_pair.second.get_permanent() == false)
        {
          if (ailments.find(status_id) != ailments.end() && !has_status_ailment_from_wearable(creature, status_id))
          {
            CreatureUtils::process_creature_modifier(creature, mod_pair, StatusRemovalType::STATUS_REMOVAL_UNDO);
            mod_pair.second.set_delete(true);
          }
        }
      }
    }

    CreatureUtils::remove_modifiers(creature);
  }
}

void CreatureUtils::remove_modifiers(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    map<double, vector<pair<string, Modifier>>>& creature_modifiers = creature->get_modifiers_ref();

    for (auto cm_it = creature_modifiers.begin(); cm_it != creature_modifiers.end(); )
    {
      vector<pair<string, Modifier>>& t_mods = cm_it->second;

      // Remove any marked modifiers at the current time
      for (auto t_it = t_mods.begin(); t_it != t_mods.end(); )
      {
        t_it->second.get_delete() ? t_it = t_mods.erase(t_it) : t_it++;
      }

      // If there are no more modifiers, remove the creature modifier entry.
      t_mods.empty() ? cm_it = creature_modifiers.erase(cm_it) : cm_it++;
    }
  }
}

void CreatureUtils::add_removal_message(CreaturePtr creature, const string& spell_id)
{
  if (!spell_id.empty() && creature != nullptr)
  {
    Game& game = Game::instance();
    string creature_id = creature->get_id();

    const SpellMap& spells = game.get_spells_ref();
    auto spell_it = spells.find(spell_id);

    if (spell_it != spells.end())
    {
      Spell spell = spell_it->second;
      string spell_wear_off_sid = spell.get_property(SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_WEAR_OFF_SID);

      // Check to see if the creature is the player, or in view of the player.
      bool affects_player = CreatureUtils::is_player_or_in_los(creature);

      // Get the appropriate message manager and set the appropriate message.
      // If the creature is the player, use the spell wear off sid.
      // Otherwise, use the generic spell wear off message for creatures.
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, affects_player);

      if (creature->get_is_player())
      {
        manager.add_new_message(StringTable::get(spell_wear_off_sid));
      }
      else
      {
        manager.add_new_message(ActionTextKeys::get_generic_wear_off_message(StringTable::get(creature->get_description_sid())));
      }

      manager.send();
    }
  }
}

bool CreatureUtils::has_status_ailment_from_wearable(CreaturePtr creature, const string& status_id)
{
  bool has_ailment = false;

  if (creature != nullptr)
  {
    Equipment& eq = creature->get_equipment();
    EquipmentMap em = eq.get_equipment();

    for (const auto eq_pair : em)
    {
      WearablePtr wearable = dynamic_pointer_cast<Wearable>(eq_pair.second);

      if (wearable != nullptr)
      {
        set<string> ailments = wearable->get_status_ailments().get_ailments();

        if (std::find(ailments.begin(), ailments.end(), status_id) != ailments.end())
        {
          has_ailment = true;
          break;
        }
      }
    }
  }

  return has_ailment;
}

MapPtr CreatureUtils::update_fov_map(MapPtr current_map, MapPtr v_map, CreaturePtr current_creature)
{
  MapPtr fov_map;

  if (current_map != nullptr && current_creature != nullptr)
  {
    Coordinate creature_coords = current_map->get_location(current_creature->get_id());
    MapPtr view_map = v_map;
    LineOfSightCalculator losc;
    Game& game = Game::instance();
    Date date = GameUtils::get_date(game);

    int los_len = losc.calculate_los_length(current_creature, date.get_time_of_day());

    if (view_map == nullptr)
    {
      view_map = ViewMapTranslator::create_view_map_around_tile(current_map, creature_coords, los_len);
    }

    FieldOfViewStrategyPtr fov_strategy = FieldOfViewStrategyFactory::create_field_of_view_strategy(current_creature->get_is_player());
    fov_map = fov_strategy->calculate(current_creature, view_map, creature_coords, los_len);
    DecisionStrategyPtr strategy = current_creature->get_decision_strategy();

    if (strategy)
    {
      strategy->set_fov_map(fov_map);
    }
  }

  return fov_map;
}

bool CreatureUtils::has_negative_status(CreaturePtr creature)
{
  bool has_neg = false;

  if (creature != nullptr)
  {
    CreatureStatusMap csm = creature->get_statuses();

    for (const auto& csm_pair : csm)
    {
      string status_id = csm_pair.first;
      StatusEffectPtr se = StatusEffectFactory::create_status_effect(status_id, "");

      if (se && se->is_negative())
      {
        has_neg = true;
        break;
      }
    }
  }

  return has_neg;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureUtils_test.cpp"
#endif
