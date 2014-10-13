#pragma once

class ReligionConstants
{
  public:
    static const int MIN_PIETY_FOR_DEGENERATION;
    static const int MAX_PIETY_FOR_REGENERATION;
    static const int BASIC_PIETY_INCREMENT;
    static const int CROWNED_PIETY_INCREMENT;
    static const int PIETY_MAX;
    static const int PIETY_MIN;

    // Used by the deities to determine messages when sacrificing, when
    // a creature is ready for crowning, etc.
    static const int PIETY_TIER_1;
    static const int PIETY_TIER_2;
    static const int PIETY_TIER_3;
    static const int PIETY_TIER_4;
    static const int PIETY_CROWNING;

  protected:
    ReligionConstants();
    ~ReligionConstants();
};
