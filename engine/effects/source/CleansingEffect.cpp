#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "MessageManager.hpp"
#include "StatusEffectFactory.hpp"
#include "CleansingEffect.hpp"

using namespace std;

CleansingEffect::CleansingEffect()
{
}

string CleansingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature != nullptr)
  {
    effect_msg = StringTable::get(EffectTextKeys::EFFECT_CLEANSING);
  }

  return effect_msg;
}

Effect* CleansingEffect::clone()
{
  return new CleansingEffect(*this);
}

bool CleansingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return cleansing(creature, 0.0f);
}

bool CleansingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return cleansing(creature, 0.0f);
}

bool CleansingEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return cleansing(creature, 1.5f);
}

bool CleansingEffect::cleansing(CreaturePtr creature, const float map_creature_regen_multiplier)
{
  bool cleansed = false;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    // Set the multiplier on the current map.
    current_map->set_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE, to_string(map_creature_regen_multiplier));
    cleansed = true;
  }

  return cleansed;
}

