#include "Conversion.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "CreatureUtils.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "PlayerConstants.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "StatisticTextKeys.hpp"
#include "StatusAilmentTextKeys.hpp"

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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    if (hunger_message_sid_map.empty())
    {
      initialize_hunger_message_sid_map();
    }

    string message_sid = hunger_message_sid_map[new_level];

    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
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
    const DeityMap& deities = game.get_deities_ref();

    if (range_before != range_after)
    {
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

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

    if (creature_id == PlayerConstants::PLAYER_CREATURE_ID)
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(StatisticTextKeys::STATISTIC_GAIN_CHARISMA));
    manager.send();
  }
}

bool CreatureUtils::can_pick_up(CreaturePtr c, ItemPtr i)
{
  bool can_pu = false;

  if (c != nullptr && i != nullptr)
  {
    CarryingCapacityCalculator ccc;
    uint total_items = ccc.calculate_carrying_capacity_total_items(c);

    can_pu = (i->get_type() == ItemType::ITEM_TYPE_CURRENCY || c->count_items() + i->get_quantity() <= total_items);
  }

  return can_pu;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureUtils_test.cpp"
#endif
