#pragma once
#include <string>

class SoundEffectID
{
  public:
    static const std::string SHOOT;
    static const std::string HIT;
    static const std::string MISS;
    static const std::string SPELL;
    static const std::string ZAP;
    static const std::string SHOP;
    static const std::string BUMP;
    static const std::string TELEPORT;
    static const std::string TIMEWALK;
    static const std::string RAGE;
    static const std::string DIG;
    static const std::string EXIT_MAP;
    static const std::string SPLASH;
    static const std::string ALARM;
    static const std::string DEAD;
    static const std::string MAP_EFFECT;
    static const std::string ITEM_EFFECT;
    static const std::string POSITIVE_EFFECT;
    static const std::string NEGATIVE_EFFECT;

  protected:
    SoundEffectID();
    ~SoundEffectID();
};

constexpr auto CSOUND_EFFECT_SHOOT = "_shoot";
constexpr auto CSOUND_EFFECT_HIT = "_hit";
constexpr auto CSOUND_EFFECT_MISS = "_miss";
constexpr auto CSOUND_EFFECT_SPELL = "_spell";
constexpr auto CSOUND_EFFECT_ZAP = "_zap";
constexpr auto CSOUND_EFFECT_SHOP = "_shop";
constexpr auto CSOUND_EFFECT_BUMP = "_bump";
constexpr auto CSOUND_EFFECT_TELEPORT = "_teleport";
constexpr auto CSOUND_EFFECT_TIMEWALK = "_timewalk";
constexpr auto CSOUND_EFFECT_RAGE = "_rage";
constexpr auto CSOUND_EFFECT_DIG = "_dig";
constexpr auto CSOUND_EFFECT_EXIT_MAP = "_exit_map";
constexpr auto CSOUND_EFFECT_SPLASH = "_splash";
constexpr auto CSOUND_EFFECT_ALARM = "_alarm";
constexpr auto CSOUND_EFFECT_DEAD = "_dead";
constexpr auto CSOUND_EFFECT_MAP_EFFECT = "_map_effect";
constexpr auto CSOUND_EFFECT_ITEM_EFFECT = "_item_effect";
constexpr auto CSOUND_EFFECT_POSITIVE_EFFECT = "_positive_effect";
constexpr auto CSOUND_EFFECT_NEGATIVE_EFFECT = "_negative_effect";
