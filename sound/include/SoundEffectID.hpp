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
