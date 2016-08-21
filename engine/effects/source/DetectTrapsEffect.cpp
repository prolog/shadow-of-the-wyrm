#include "Conversion.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "DetectTrapsEffect.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

DetectTrapsEffect::DetectTrapsEffect()
{
}

string DetectTrapsEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  string creature_desc_sid;
  bool is_player = false;

  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }

  return EffectTextKeys::get_detect_traps_effect_message(creature_desc_sid, is_player);
}

Effect* DetectTrapsEffect::clone()
{
  return new DetectTrapsEffect(*this);
}

bool DetectTrapsEffect::detect_traps(CreaturePtr creature, const DetectTrapsEffectType dtet)
{
  bool effect_identified = false;

  if (creature)
  {
    Game& game = Game::instance();
    MapPtr trap_map = game.get_current_map();

    // Only SHOW_ALL_TRAPS works on the full map.  The other effect types
    // show or hide traps in the creature's FOV.
    if (dtet != DetectTrapsEffectType::DETECT_TRAPS_SHOW_ALL_TRAPS)
    {
      trap_map = creature->get_decision_strategy()->get_fov_map();
    }

    show_or_hide_traps(trap_map, dtet);
    effect_identified = true;
  }

  return effect_identified;
}

void DetectTrapsEffect::show_or_hide_traps(MapPtr trap_map, const DetectTrapsEffectType dtet)
{
  if (trap_map != nullptr)
  {
    TilesContainer tc = trap_map->get_tiles();

    for (auto& tile_pair : tc)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr)
      {
        if (tile->has_feature())
        {
          FeaturePtr feature = tile->get_feature();
          TrapPtr trap = dynamic_pointer_cast<Trap>(feature);

          if (trap != nullptr)
          {
            trap->set_triggered(dtet != DetectTrapsEffectType::DETECT_TRAPS_HIDE_TRAPS);
          }
        }
      }
    }
  }
}

bool DetectTrapsEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  return detect_traps(creature, DetectTrapsEffectType::DETECT_TRAPS_SHOW_ALL_TRAPS);
}

bool DetectTrapsEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return detect_traps(creature, DetectTrapsEffectType::DETECT_TRAPS_SHOW_LOCAL_TRAPS);
}

bool DetectTrapsEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  return detect_traps(creature, DetectTrapsEffectType::DETECT_TRAPS_HIDE_TRAPS);
}
