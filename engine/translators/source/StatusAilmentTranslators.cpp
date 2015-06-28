#include "Conversion.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusAilmentTranslators.hpp"
#include "StringTable.hpp"
#include "StatusTypes.hpp"

using namespace std;

// Hunger

map<HungerLevel, string> HungerStatusAilmentTranslator::text_sid_map;
map<HungerLevel, Colour> HungerStatusAilmentTranslator::colour_map;

// Initialize the text SIDs
void HungerStatusAilmentTranslator::initialize_text_sid_map()
{
  text_sid_map.clear();
  text_sid_map = map<HungerLevel, string>{{HungerLevel::HUNGER_LEVEL_STUFFED, StatusAilmentTextKeys::STATUS_HUNGER_STUFFED},
                                          {HungerLevel::HUNGER_LEVEL_FULL, StatusAilmentTextKeys::STATUS_HUNGER_FULL},
                                          {HungerLevel::HUNGER_LEVEL_NORMAL, StatusAilmentTextKeys::STATUS_HUNGER_NORMAL},
                                          {HungerLevel::HUNGER_LEVEL_HUNGRY, StatusAilmentTextKeys::STATUS_HUNGER_HUNGRY},
                                          {HungerLevel::HUNGER_LEVEL_STARVING, StatusAilmentTextKeys::STATUS_HUNGER_STARVING},
                                          {HungerLevel::HUNGER_LEVEL_DYING, StatusAilmentTextKeys::STATUS_HUNGER_DYING}};
}

// Initialize the colour mapping
void HungerStatusAilmentTranslator::initialize_colour_map()
{
  colour_map.clear();
  colour_map = map<HungerLevel, Colour>{{HungerLevel::HUNGER_LEVEL_STUFFED, Colour::COLOUR_WHITE},
                                        {HungerLevel::HUNGER_LEVEL_FULL, Colour::COLOUR_WHITE},
                                        {HungerLevel::HUNGER_LEVEL_NORMAL, Colour::COLOUR_WHITE},
                                        {HungerLevel::HUNGER_LEVEL_HUNGRY, Colour::COLOUR_WHITE},
                                        {HungerLevel::HUNGER_LEVEL_STARVING, Colour::COLOUR_BOLD_YELLOW},
                                        {HungerLevel::HUNGER_LEVEL_DYING, Colour::COLOUR_RED}};
}

// Check to see if the hunger level is anything other than normal.
bool HungerStatusAilmentTranslator::has_ailment(const CreaturePtr& creature) const
{
  bool ailment = false;

  if (creature)
  {
    HungerClock clock = creature->get_hunger_clock();

    ailment = (HungerLevelConverter::to_hunger_level(clock.get_hunger()) != HungerLevel::HUNGER_LEVEL_NORMAL);
  }

  return ailment;
}

string HungerStatusAilmentTranslator::get_status_ailment_text(const CreaturePtr& creature) const
{
  string hunger_text;

  if (text_sid_map.empty())
  {
    initialize_text_sid_map();
  }

  if (has_ailment(creature))
  {
    hunger_text = StringTable::get(text_sid_map[HungerLevelConverter::to_hunger_level(creature->get_hunger_clock().get_hunger())]);
  }

  return hunger_text;
}

Colour HungerStatusAilmentTranslator::get_status_ailment_colour(const CreaturePtr& creature) const
{
  Colour colour = Colour::COLOUR_WHITE;

  if (colour_map.empty())
  {
    initialize_colour_map();
  }

  return colour_map[HungerLevelConverter::to_hunger_level(creature->get_hunger_clock().get_hunger())];
}


// Weight
map<BurdenLevel, string> WeightStatusAilmentTranslator::text_sid_map;
map<BurdenLevel, Colour> WeightStatusAilmentTranslator::colour_map;

void WeightStatusAilmentTranslator::initialize_text_sid_map()
{
  text_sid_map.clear();
  text_sid_map = map<BurdenLevel, string>{{BurdenLevel::BURDEN_LEVEL_UNBURDENED, StatusAilmentTextKeys::STATUS_BURDEN_UNBURDENED},
                                          {BurdenLevel::BURDEN_LEVEL_BURDENED, StatusAilmentTextKeys::STATUS_BURDEN_BURDENED},
                                          {BurdenLevel::BURDEN_LEVEL_STRAINED, StatusAilmentTextKeys::STATUS_BURDEN_STRAINED},
                                          {BurdenLevel::BURDEN_LEVEL_OVERBURDENED, StatusAilmentTextKeys::STATUS_BURDEN_OVERBURDENED}};
}

void WeightStatusAilmentTranslator::initialize_colour_map()
{
  colour_map.clear();
  colour_map = map<BurdenLevel, Colour>{{BurdenLevel::BURDEN_LEVEL_UNBURDENED, Colour::COLOUR_WHITE},
                                        {BurdenLevel::BURDEN_LEVEL_BURDENED, Colour::COLOUR_WHITE},
                                        {BurdenLevel::BURDEN_LEVEL_STRAINED, Colour::COLOUR_WHITE},
                                        {BurdenLevel::BURDEN_LEVEL_OVERBURDENED, Colour::COLOUR_BOLD_RED}};
}

// Check to see if the burden level is not unburdened.
bool WeightStatusAilmentTranslator::has_ailment(const CreaturePtr& creature) const
{
  bool ailment = false;

  if (creature)
  {
    BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);
    ailment = (bl != BurdenLevel::BURDEN_LEVEL_UNBURDENED);
  }

  return ailment;
}

string WeightStatusAilmentTranslator::get_status_ailment_text(const CreaturePtr& creature) const
{
  string weight_text;

  if (text_sid_map.empty())
  {
    initialize_text_sid_map();
  }

  if (has_ailment(creature))
  {
    weight_text = StringTable::get(text_sid_map[BurdenLevelConverter::to_burden_level(creature)]);
  }

  return weight_text;
}

Colour WeightStatusAilmentTranslator::get_status_ailment_colour(const CreaturePtr& creature) const
{
  Colour colour = Colour::COLOUR_WHITE;

  if (colour_map.empty())
  {
    initialize_colour_map();
  }

  return colour_map[BurdenLevelConverter::to_burden_level(creature)];
}

// General status ailment.

StatusAilmentTranslator::StatusAilmentTranslator(const string& id, const string& t_sid, const Colour c)
: identifier(id), text_sid(t_sid), colour(c)
{
}

bool StatusAilmentTranslator::has_ailment(const CreaturePtr& creature) const
{
  bool ailment = creature && creature->has_status(identifier);

  return ailment;
}

string StatusAilmentTranslator::get_status_ailment_text(const CreaturePtr& creature) const
{
  return StringTable::get(text_sid);
}

Colour StatusAilmentTranslator::get_status_ailment_colour(const CreaturePtr& creature) const
{
  return colour;
}

