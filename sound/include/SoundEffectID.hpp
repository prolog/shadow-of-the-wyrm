#pragma once
#include <string>

class SoundEffectID
{
  public:
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

  protected:
    SoundEffectID();
    ~SoundEffectID();
};

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