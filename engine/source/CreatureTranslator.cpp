#include "Creature.hpp"
#include "Conversion.hpp"
#include "DisplayStatistics.hpp"
#include "CreatureTranslator.hpp"
#include "StringTable.hpp"
#include "StringConstants.hpp"

using namespace std;

CreatureTranslator::CreatureTranslator()
{
}

// Create a display-readable statistics object out of the main CreaturePtr.
DisplayStatistics CreatureTranslator::create_display_statistics(const CreaturePtr& creature)
{
  DisplayStatistics ds;

  string name         = get_display_name(creature);
  string strength     = get_display_strength(creature);
  string dexterity    = get_display_dexterity(creature);
  string agility      = get_display_agility(creature);
  string health       = get_display_health(creature);
  string intelligence = get_display_intelligence(creature);
  string willpower    = get_display_willpower(creature);
  string charisma     = get_display_charisma(creature);

  ds = DisplayStatistics::create(name,
                                 strength,
                                 dexterity,
                                 agility,
                                 health,
                                 intelligence,
                                 willpower,
                                 charisma);

  return ds;
}

string CreatureTranslator::get_display_name(const CreaturePtr& c)
{
  string name = c->get_name();
  return name;
}

string CreatureTranslator::get_display_strength(const CreaturePtr& c)
{
  string strength = StringTable::get(TextKeys::STRENGTH_ABRV) + ":" + Integer::to_string(c->get_strength().get_current());
  return strength;
}

string CreatureTranslator::get_display_dexterity(const CreaturePtr& c)
{
  string dexterity = StringTable::get(TextKeys::DEXTERITY_ABRV) + ":" + Integer::to_string(c->get_dexterity().get_current());
  return dexterity;
}

string CreatureTranslator::get_display_agility(const CreaturePtr& c)
{
  string agility = StringTable::get(TextKeys::AGILITY_ABRV) + ":" + Integer::to_string(c->get_agility().get_current());
  return agility;
}

string CreatureTranslator::get_display_health(const CreaturePtr& c)
{
  string health = StringTable::get(TextKeys::HEALTH_ABRV) + ":" + Integer::to_string(c->get_health().get_current());
  return health;
}

string CreatureTranslator::get_display_intelligence(const CreaturePtr& c)
{
  string intelligence = StringTable::get(TextKeys::INTELLIGENCE_ABRV) + ":" + Integer::to_string(c->get_intelligence().get_current());
  return intelligence;
}

string CreatureTranslator::get_display_willpower(const CreaturePtr& c)
{
  string willpower = StringTable::get(TextKeys::WILLPOWER_ABRV) + ":" + Integer::to_string(c->get_willpower().get_current());
  return willpower;
}

string CreatureTranslator::get_display_charisma(const CreaturePtr& c)
{
  string charisma = StringTable::get(TextKeys::CHARISMA_ABRV) + ":" + Integer::to_string(c->get_charisma().get_current());
  return charisma;
}
