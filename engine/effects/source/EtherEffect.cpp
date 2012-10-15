#include <boost/make_shared.hpp>
#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EtherEffect.hpp"

using std::string;

EtherEffect::EtherEffect()
{
  AdditionalEffectMessagePtr sweet_taste = boost::make_shared<SweetTasteEffectMessage>();
  additional_effect_messages.push_back(sweet_taste);
}

string EtherEffect::get_effect_identification_message(boost::shared_ptr<Creature> creature) const
{
  bool is_player = (creature && creature->get_is_player());
  string creature_desc_sid = (creature ? creature->get_description_sid() : "");

  return EffectTextKeys::get_ether_effect_message(creature_desc_sid, is_player);
}

Effect* EtherEffect::clone()
{
  return new EtherEffect(*this);
}

// Restore AP in a similar way to HP
bool EtherEffect::heal(CreaturePtr creature, const float healing_multiplier) const
{
  bool effect_identified = false;

  if (creature)
  {
    int ether_amount = static_cast<int>(get_random_healing_amount() * healing_multiplier);

    Statistic ap = creature->get_arcana_points();

    int base_ap = ap.get_base();
    int current_ap = ap.get_current();

    if (current_ap < base_ap)
    {
      ap.set_current(std::min(base_ap, (current_ap + ether_amount)));
      creature->set_arcana_points(ap);

      // Some magical healing was performed; return true.
      effect_identified = true;
    }
  }

  return effect_identified;
}

ClassIdentifier EtherEffect::internal_class_identifier() const
{
  return CLASS_ID_ETHER_EFFECT;
}