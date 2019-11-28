#include "RemoveStatusEffect.hpp"
#include "BlessEffect.hpp"
#include "CleansingEffect.hpp"
#include "DetectTrapsEffect.hpp"
#include "DiggingEffect.hpp"
#include "EffectFactory.hpp"
#include "EtherEffect.hpp"
#include "EnchantingEffect.hpp"
#include "FlyingEffect.hpp"
#include "FruitJuiceEffect.hpp"
#include "GainAttributesEffect.hpp"
#include "GlowEffect.hpp"
#include "HasteEffect.hpp"
#include "HealingEffect.hpp"
#include "IdentifyEffect.hpp"
#include "IncorporealEffect.hpp"
#include "IncreaseMaxHPAPEffect.hpp"
#include "MappingEffect.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "NullEffect.hpp"
#include "RageEffect.hpp"
#include "RepelEffect.hpp"
#include "RechargingEffect.hpp"
#include "StatusTypes.hpp"
#include "SummonMonstersEffect.hpp"
#include "TeleportEffect.hpp"
#include "TimewalkEffect.hpp"
#include "UncursingEffect.hpp"
#include "WarpEffect.hpp"

using namespace std;

EffectFactory::EffectFactory()
{
}

EffectFactory::~EffectFactory()
{
}

EffectPtr EffectFactory::create_effect(const EffectType effect_type, const Modifier& m, const map<string, string>& properties, const string& spell_id, const string& source_id)
{
  static_assert(EffectType::EFFECT_TYPE_LAST == EffectType(33), "Unexpected EFFECT_TYPE_LAST value.");

  EffectPtr effect;

  switch(effect_type)
  {
    case EffectType::EFFECT_TYPE_HEALING:
      effect = std::make_shared<HealingEffect>();
      break;
    case EffectType::EFFECT_TYPE_IDENTIFY:
      effect = std::make_shared<IdentifyEffect>();
      break;
    case EffectType::EFFECT_TYPE_ETHER:
      effect = std::make_shared<EtherEffect>();
      break;
    case EffectType::EFFECT_TYPE_FRUIT_JUICE:
      effect = std::make_shared<FruitJuiceEffect>();
      break;
    case EffectType::EFFECT_TYPE_TELEPORT:
      effect = std::make_shared<TeleportEffect>();
      break;
    case EffectType::EFFECT_TYPE_ANTIDOTE:
      effect = std::make_shared<RemoveStatusEffect>(StatusIdentifiers::STATUS_ID_POISON);
      break;
    case EffectType::EFFECT_TYPE_AMUT:
      effect = std::make_shared<RemoveStatusEffect>(StatusIdentifiers::STATUS_ID_MUTE);
      break;
    case EffectType::EFFECT_TYPE_SPEED:
      effect = std::make_shared<HasteEffect>();
      break;
    case EffectType::EFFECT_TYPE_UNSTONING:
      effect = std::make_shared<RemoveStatusEffect>(StatusIdentifiers::STATUS_ID_STONE);
      break;
    case EffectType::EFFECT_TYPE_UNBINDING:
      effect = std::make_shared<RemoveStatusEffect>(StatusIdentifiers::STATUS_ID_SPELLBOUND);
      break;
    case EffectType::EFFECT_TYPE_RESTORE_STATISTICS:
      effect = std::make_shared<RemoveStatusEffect>(StatusIdentifiers::STATUS_ID_DISFIGURED);
      break;
    case EffectType::EFFECT_TYPE_UNBLINDING:
      effect = std::make_shared<RemoveStatusEffect>(StatusIdentifiers::STATUS_ID_BLINDED);
      break;
    case EffectType::EFFECT_TYPE_RECHARGING:
      effect = std::make_shared<RechargingEffect>();
      break;
    case EffectType::EFFECT_TYPE_INCORPOREAL:
      effect = std::make_shared<IncorporealEffect>();
      break;
    case EffectType::EFFECT_TYPE_ENCHANTING:
      effect = std::make_shared<EnchantingEffect>();
      break;
    case EffectType::EFFECT_TYPE_FLYING:
      effect = std::make_shared<FlyingEffect>();
      break;
    case EffectType::EFFECT_TYPE_GAIN_ATTRIBUTES:
      effect = std::make_shared<GainAttributesEffect>();
      break;
    case EffectType::EFFECT_TYPE_MODIFY_STATISTICS:
    {
      shared_ptr<ModifyStatisticsEffect> ms_effect = std::make_shared<ModifyStatisticsEffect>();
      ms_effect->set_modifier(m);
      ms_effect->set_spell_id(spell_id);

      effect = ms_effect;
      break;
    }
    case EffectType::EFFECT_TYPE_TIMEWALK:
      effect = std::make_shared<TimewalkEffect>();
      break;
    case EffectType::EFFECT_TYPE_CLEANSING:
      effect = std::make_shared<CleansingEffect>();
      break;
    case EffectType::EFFECT_TYPE_UNCURSING:
      effect = std::make_shared<UncursingEffect>();
      break;
    case EffectType::EFFECT_TYPE_DETECT_TRAPS:
      effect = std::make_shared<DetectTrapsEffect>();
      break;
    case EffectType::EFFECT_TYPE_BLESS:
      effect = std::make_shared<BlessEffect>();
      break;
    case EffectType::EFFECT_TYPE_MAPPING:
      effect = std::make_shared<MappingEffect>();
      break;
    case EffectType::EFFECT_TYPE_SUMMON_MONSTERS:
      effect = std::make_shared<SummonMonstersEffect>();
      break;
    case EffectType::EFFECT_TYPE_DIGGING:
      effect = std::make_shared<DiggingEffect>();
      break;
    case EffectType::EFFECT_TYPE_RAGE:
      effect = std::make_shared<RageEffect>();
      break;
    case EffectType::EFFECT_TYPE_INCREASE_MAX_HP:
      effect = std::make_shared<IncreaseMaxHPEffect>();
      break;
    case EffectType::EFFECT_TYPE_INCREASE_MAX_AP:
      effect = std::make_shared<IncreaseMaxAPEffect>();
      break;
    case EffectType::EFFECT_TYPE_REPEL:
      effect = std::make_shared<RepelEffect>();
      break;
    case EffectType::EFFECT_TYPE_WARP:
      effect = std::make_shared<WarpEffect>();
      break;
    case EffectType::EFFECT_TYPE_GLOW:
      effect = std::make_shared<GlowEffect>();
      break;
    case EffectType::EFFECT_TYPE_NULL:
    default:
      effect = std::make_shared<NullEffect>();
      break;
  }

  if (effect != nullptr)
  {
    effect->set_source_id(source_id);
    effect->read_properties(properties);
  }

  return effect;
}

#ifdef UNIT_TESTS
#include "unit_tests/EffectFactory_test.cpp"
#endif