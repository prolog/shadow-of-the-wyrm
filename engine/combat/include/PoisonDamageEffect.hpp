#include "IDamageEffect.hpp"

class PoisonDamageEffect : public IDamageEffect
{
  public:
    virtual void apply(CreaturePtr creature, const int damage_dealt) const;
    virtual std::string get_player_application_message() const;

  protected:
    static const int BASE_PCT_CHANCE_POISON;
    static const int BASE_POISON_DURATION;
    static const int MAX_POISON_DURATION;
};
