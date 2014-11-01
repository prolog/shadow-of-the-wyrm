#include "Creature.hpp"
#include "CreatureUtils.hpp"
#include "EffectTextKeys.hpp"
#include "GainAttributesEffect.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

string GainAttributesEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  string creature_desc_sid;
  bool is_player = false;
  
  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }
  
  return EffectTextKeys::get_gain_attributes_effect_message(creature_desc_sid, is_player);
}

Effect* GainAttributesEffect::clone()
{
  return new GainAttributesEffect(*this);
}

bool GainAttributesEffect::gain_attributes(CreaturePtr creature, const vector<GainAttributesEnum>& attr_to_gain) const
{
  bool effect_identified = true;

  if (creature)
  {
    for (const GainAttributesEnum a : attr_to_gain)
    {
      switch (a)
      {
        case GAIN_ATTRIBUTES_STRENGTH:
          CreatureUtils::incr_str(creature, true);
          break;
        case GAIN_ATTRIBUTES_DEXTERITY:
          CreatureUtils::incr_dex(creature, true);
          break;
        case GAIN_ATTRIBUTES_AGILITY:
          CreatureUtils::incr_agi(creature, true);
          break;
        case GAIN_ATTRIBUTES_HEALTH:
          CreatureUtils::incr_hea(creature, true);
          break;
        case GAIN_ATTRIBUTES_INTELLIGENCE:
          CreatureUtils::incr_int(creature, true);
          break;
        case GAIN_ATTRIBUTES_WILLPOWER:
          CreatureUtils::incr_wil(creature, true);
          break;
        case GAIN_ATTRIBUTES_CHARISMA:
          CreatureUtils::incr_cha(creature, true);
        default:
          break;
      }
    }
  }

  return effect_identified;
}

bool GainAttributesEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  vector<GainAttributesEnum> to_gain = {GAIN_ATTRIBUTES_STRENGTH, GAIN_ATTRIBUTES_DEXTERITY, GAIN_ATTRIBUTES_AGILITY, GAIN_ATTRIBUTES_HEALTH, GAIN_ATTRIBUTES_INTELLIGENCE, GAIN_ATTRIBUTES_WILLPOWER, GAIN_ATTRIBUTES_CHARISMA};
  return gain_attributes(creature, to_gain);
}

bool GainAttributesEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  vector<GainAttributesEnum> to_gain = { GAIN_ATTRIBUTES_STRENGTH, GAIN_ATTRIBUTES_DEXTERITY, GAIN_ATTRIBUTES_AGILITY, GAIN_ATTRIBUTES_HEALTH, GAIN_ATTRIBUTES_INTELLIGENCE, GAIN_ATTRIBUTES_WILLPOWER, GAIN_ATTRIBUTES_CHARISMA };

  // Shuffle the stats.  Get rid of 4-5 stats so that there are 2-3 left to gain.
  random_shuffle(to_gain.begin(), to_gain.end());
  int to_remove = RNG::range(4, 5);
  for (int i = 0; i < to_remove; i++)
  {
    to_gain.pop_back();
  }

  return gain_attributes(creature, to_gain);
}

bool GainAttributesEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  vector<GainAttributesEnum> no_gain;
  return gain_attributes(creature, no_gain);
}


