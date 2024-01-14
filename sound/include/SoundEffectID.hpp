#pragma once
#include <string>

class SoundEffectID
{
  public:
    static const std::string SHOOT;
    static const std::string HIT;
    static const std::string MISS;
    static const std::string CAST;
    static const std::string ZAP;
    static const std::string SHOP;
    static const std::string BUMP;
    static const std::string TELEPORT;
    static const std::string TIMEWALK;
    static const std::string RECHARGING;
    static const std::string RAGE;
    static const std::string HEALING;
    static const std::string ETHER;
    static const std::string DIG;
    static const std::string DETECT_TRAPS;
    static const std::string GAIN_ATTRIBUTES;
    static const std::string EXIT_MAP;
    static const std::string SPLASH;
    static const std::string DROP;
    static const std::string ALARM;
    static const std::string LEARN_SPELL;
    static const std::string DRINK;
    static const std::string EAT;

  protected:
    SoundEffectID();
    ~SoundEffectID();
};

constexpr auto CSOUND_EFFECT_SHOOT = "_shoot";
constexpr auto CSOUND_EFFECT_HIT = "_hit";
constexpr auto CSOUND_EFFECT_MISS = "_miss";
constexpr auto CSOUND_EFFECT_CAST = "_cast";
constexpr auto CSOUND_EFFECT_ZAP = "_zap";
constexpr auto CSOUND_EFFECT_SHOP = "_shop";
constexpr auto CSOUND_EFFECT_BUMP = "_bump";
constexpr auto CSOUND_EFFECT_TELEPORT = "_teleport";
constexpr auto CSOUND_EFFECT_TIMEWALK = "_timewalk";
constexpr auto CSOUND_EFFECT_RECHARGING = "_recharging";
constexpr auto CSOUND_EFFECT_RAGE = "_rage";
constexpr auto CSOUND_EFFECT_HEALING = "_healing";
constexpr auto CSOUND_EFFECT_ETHER = "_ether";
constexpr auto CSOUND_EFFECT_DIG = "_dig";
constexpr auto CSOUND_EFFECT_DETECT_TRAPS = "_detect_traps";
constexpr auto CSOUND_EFFECT_GAIN_ATTRIBUTES = "_gain_attributes";
constexpr auto CSOUND_EFFECT_EXIT_MAP = "_exit_map";
constexpr auto CSOUND_EFFECT_SPLASH = "_splash";
constexpr auto CSOUND_EFFECT_DROP = "_drop";
constexpr auto CSOUND_EFFECT_ALARM = "_alarm";
constexpr auto CSOUND_EFFECT_LEARN_SPELL = "_learn_spell";
constexpr auto CSOUND_EFFECT_DRINK = "_drink";
constexpr auto CSOUND_EFFECT_EAT = "_eat";
