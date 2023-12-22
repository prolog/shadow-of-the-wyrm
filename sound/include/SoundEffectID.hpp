#pragma once
#include <string>

class SoundEffectID
{
  public:
    static const std::string HIT;
    static const std::string MISS;
    static const std::string CAST;
    static const std::string ZAP;

  protected:
    SoundEffectID();
    ~SoundEffectID();
};

