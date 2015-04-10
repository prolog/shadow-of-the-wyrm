#include "Creature.hpp"
#include "CreatureUtils.hpp"
#include "Conversion.hpp"
#include "DisplayStatistics.hpp"
#include "ExperienceManager.hpp"
#include "CreatureTranslator.hpp"
#include "Game.hpp"
#include "Naming.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusAilmentTranslators.hpp"
#include "StatusTypes.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

vector<IStatusAilmentTranslatorPtr> CreatureTranslator::status_ailment_checkers;

CreatureTranslator::CreatureTranslator()
{
}

// Create a display-readable statistics object out of the main CreaturePtr.
DisplayStatistics CreatureTranslator::create_display_statistics(const CreaturePtr& creature, const MapPtr& map)
{
  DisplayStatistics ds;

  string name          = get_display_name(creature);
  string synopsis      = CreatureUtils::get_race_class_synopsis(creature);

  pair<string, Colour> strength      = get_display_strength(creature);
  pair<string, Colour> dexterity     = get_display_dexterity(creature);
  pair<string, Colour> agility       = get_display_agility(creature);
  pair<string, Colour> health        = get_display_health(creature);
  pair<string, Colour> intelligence  = get_display_intelligence(creature);
  pair<string, Colour> willpower     = get_display_willpower(creature);
  pair<string, Colour> charisma      = get_display_charisma(creature);

  string speed         = get_display_speed(creature);

  string level         = get_display_level(creature);
  string defence       = get_display_defence(creature);

  pair<string, Colour> alignment = get_display_alignment(creature);

  string hit_points    = get_display_hit_points(creature);
  string arcana_points = get_display_arcana_points(creature);
  
  string map_depth;
  if (map != nullptr)
  {
    map_depth = map->size().depth().str();
  }

  std::vector<std::pair<std::string, Colour>> status_ailments = get_display_status_ailments(creature);

  ds = DisplayStatistics::create(name,
                                 synopsis,
                                 strength,
                                 dexterity,
                                 agility,
                                 health,
                                 intelligence,
                                 willpower,
                                 charisma,
                                 speed,
                                 level,
                                 defence,
                                 alignment,
                                 hit_points,
                                 arcana_points,
                                 map_depth,
                                 status_ailments
                                 );

  return ds;
}

string CreatureTranslator::get_display_name(const CreaturePtr& c)
{
  string name = c->get_name();
  name = String::add_trailing_spaces(name, Naming::get_max_name_size());

  return name;
}

pair<string, Colour> CreatureTranslator::get_display_strength(const CreaturePtr& c)
{
  Statistic str = c->get_strength();
  string strength = StringTable::get(TextKeys::STRENGTH_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_strength().get_current()), 2);
  return make_pair(strength, (str.get_current() == str.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

pair<string, Colour> CreatureTranslator::get_display_dexterity(const CreaturePtr& c)
{
  Statistic dex = c->get_dexterity();
  string dexterity = StringTable::get(TextKeys::DEXTERITY_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_dexterity().get_current()), 2);
  return make_pair(dexterity, (dex.get_current() == dex.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

pair<string, Colour> CreatureTranslator::get_display_agility(const CreaturePtr& c)
{
  Statistic agi = c->get_agility();
  string agility = StringTable::get(TextKeys::AGILITY_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_agility().get_current()), 2);
  return make_pair(agility, (agi.get_current() == agi.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

pair<string, Colour> CreatureTranslator::get_display_health(const CreaturePtr& c)
{
  Statistic hea = c->get_health();
  string health = StringTable::get(TextKeys::HEALTH_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_health().get_current()), 2);
  return make_pair(health, (hea.get_current() == hea.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

pair<string, Colour> CreatureTranslator::get_display_intelligence(const CreaturePtr& c)
{
  Statistic intl = c->get_intelligence();
  string intelligence = StringTable::get(TextKeys::INTELLIGENCE_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_intelligence().get_current()), 2);
  return make_pair(intelligence, (intl.get_current() == intl.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

pair<string, Colour> CreatureTranslator::get_display_willpower(const CreaturePtr& c)
{
  Statistic wil = c->get_willpower();
  string willpower = StringTable::get(TextKeys::WILLPOWER_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_willpower().get_current()), 2);
  return make_pair(willpower, (wil.get_current() == wil.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

pair<string, Colour> CreatureTranslator::get_display_charisma(const CreaturePtr& c)
{
  Statistic cha = c->get_charisma();
  string charisma = StringTable::get(TextKeys::CHARISMA_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_charisma().get_current()), 2);
  return make_pair(charisma, (cha.get_current() == cha.get_base()) ? Colour::COLOUR_WHITE : Colour::COLOUR_RED);
}

string CreatureTranslator::get_display_speed(const CreaturePtr& c)
{
  string speed = StringTable::get(TextKeys::SPEED_ABRV) + ":" + String::add_trailing_spaces(std::to_string(c->get_speed().get_current()), 2);
  return speed;
}

string CreatureTranslator::get_display_level(const CreaturePtr& c)
{
  string level = StringTable::get(TextKeys::LEVEL_ABRV) + std::to_string(c->get_level().get_current()) + ",";

  ExperienceManager em;
  string expct = std::to_string(em.get_pct_to_next_level(c));

  // Display %tnl after the level.  This is a Crawl-ism/MUD-ism I really enjoy.
  level = level + expct + "%%";
  return level;
}

string CreatureTranslator::get_display_defence(const CreaturePtr& c)
{
  string evade_text  = StringTable::get(TextKeys::EVADE_ABRV);
  string soak_text   = StringTable::get(TextKeys::SOAK_ABRV);
  string evade_value = std::to_string(c->get_evade().get_current());
  string soak_value  = std::to_string(c->get_soak().get_current());

  string defence = evade_text + "/" + soak_text + ": " + evade_value + "/" + soak_value;
  return defence;
}

pair<string, Colour> CreatureTranslator::get_display_alignment(const CreaturePtr& creature)
{
  AlignmentRange range = creature->get_alignment().get_alignment_range();
  Alignment a;
  pair<string, Colour> align = make_pair(StringTable::get(a.get_abbreviation_sid(range)), Colour::COLOUR_WHITE);

  return align;
}

string CreatureTranslator::get_display_hit_points(const CreaturePtr& c)
{
  Statistic hp = c->get_hit_points();
  string hit_points = StringTable::get(TextKeys::HIT_POINTS_ABRV) + ":" + std::to_string(hp.get_current()) + "/" + std::to_string(hp.get_base());
  return hit_points;
}

string CreatureTranslator::get_display_arcana_points(const CreaturePtr& c)
{
  Statistic ap = c->get_arcana_points();
  string arcana_points = StringTable::get(TextKeys::ARCANA_POINTS_ABRV) + ":" + std::to_string(ap.get_current()) + "/" + std::to_string(ap.get_base());
  return arcana_points;
}

vector<pair<string, Colour>> CreatureTranslator::get_display_status_ailments(const CreaturePtr& c)
{
  vector<pair<string, Colour>> status_ailments;

  if (status_ailment_checkers.empty())
  {
    initialize_status_ailment_checkers();
  }

  for (IStatusAilmentTranslatorPtr status_ailment_checker : status_ailment_checkers)
  {
    if (status_ailment_checker && status_ailment_checker->has_ailment(c))
    {
      pair<string, Colour> ailment = status_ailment_checker->get_status_ailment(c);
      status_ailments.push_back(ailment);
    }
  }

  return status_ailments;
}

void CreatureTranslator::initialize_status_ailment_checkers()
{
  status_ailment_checkers.clear();

  IStatusAilmentTranslatorPtr hunger_checker = std::make_shared<HungerStatusAilmentTranslator>();
  IStatusAilmentTranslatorPtr poison_checker = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_POISON, StatusAilmentTextKeys::STATUS_POISON, Colour::COLOUR_GREEN);
  IStatusAilmentTranslatorPtr muteness_chekr = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_MUTE, StatusAilmentTextKeys::STATUS_MUTE, Colour::COLOUR_BLUE);
  IStatusAilmentTranslatorPtr paralysis_chkr = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_PARALYSIS, StatusAilmentTextKeys::STATUS_PARALYSIS, Colour::COLOUR_BOLD_YELLOW);
  IStatusAilmentTranslatorPtr slowness_chekr = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_SLOWNESS, StatusAilmentTextKeys::STATUS_SLOWNESS, Colour::COLOUR_WHITE);
  IStatusAilmentTranslatorPtr haste_checker = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_HASTE, StatusAilmentTextKeys::STATUS_HASTE, Colour::COLOUR_BOLD_WHITE);
  IStatusAilmentTranslatorPtr stone_checker = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_STONE, StatusAilmentTextKeys::STATUS_STONE, Colour::COLOUR_BOLD_BLACK);
  IStatusAilmentTranslatorPtr bloodied_chkr = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_BLOODIED, StatusAilmentTextKeys::STATUS_BLOODIED, Colour::COLOUR_RED);
  IStatusAilmentTranslatorPtr stunned_chekr = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_STUNNED, StatusAilmentTextKeys::STATUS_STUNNED, Colour::COLOUR_BOLD_CYAN);
  IStatusAilmentTranslatorPtr exposed_chekr = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_EXPOSED, StatusAilmentTextKeys::STATUS_EXPOSED, Colour::COLOUR_CYAN);
  IStatusAilmentTranslatorPtr disfigured_ck = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_DISFIGURED, StatusAilmentTextKeys::STATUS_DISFIGURED, Colour::COLOUR_BOLD_GREEN);
  IStatusAilmentTranslatorPtr spellbound_ck = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_SPELLBOUND, StatusAilmentTextKeys::STATUS_SPELLBOUND, Colour::COLOUR_BOLD_MAGENTA);
  IStatusAilmentTranslatorPtr blinded_check = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_BLINDED, StatusAilmentTextKeys::STATUS_BLINDED, Colour::COLOUR_BOLD_BLUE);
  IStatusAilmentTranslatorPtr incorporeal_ck = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_INCORPOREAL, StatusAilmentTextKeys::STATUS_INCORPOREAL, Colour::COLOUR_WHITE);
  IStatusAilmentTranslatorPtr drunk_checker = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_DRUNK, StatusAilmentTextKeys::STATUS_DRUNK, Colour::COLOUR_WHITE);
  IStatusAilmentTranslatorPtr flying_checker = std::make_shared<StatusAilmentTranslator>(StatusIdentifiers::STATUS_ID_FLYING, StatusAilmentTextKeys::STATUS_FLYING, Colour::COLOUR_WHITE);

  status_ailment_checkers.push_back(hunger_checker);
  status_ailment_checkers.push_back(poison_checker);
  status_ailment_checkers.push_back(muteness_chekr);
  status_ailment_checkers.push_back(paralysis_chkr);
  status_ailment_checkers.push_back(slowness_chekr);
  status_ailment_checkers.push_back(haste_checker );
  status_ailment_checkers.push_back(stone_checker );
  status_ailment_checkers.push_back(bloodied_chkr );
  status_ailment_checkers.push_back(stunned_chekr );
  status_ailment_checkers.push_back(exposed_chekr );
  status_ailment_checkers.push_back(disfigured_ck );
  status_ailment_checkers.push_back(spellbound_ck );
  status_ailment_checkers.push_back(blinded_check );
  status_ailment_checkers.push_back(incorporeal_ck);
  status_ailment_checkers.push_back(drunk_checker );
  status_ailment_checkers.push_back(flying_checker);
}
