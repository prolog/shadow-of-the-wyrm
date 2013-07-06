#include "IDamageEffect.hpp"
#include "Damage.hpp"

class DamageEffectFactory
{
  public:
    static IDamageEffectPtr create_damage_effect(const DamageType damage_type);

  protected:
    DamageEffectFactory();
    ~DamageEffectFactory();
};
