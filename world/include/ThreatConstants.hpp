#pragma once

class ThreatConstants
{
  public:
    // "Dislike" threat rating: the creature is not hostile,
    // but neither is it friendly.  NPCs will not attack
    // threats with this rating.
    //
    // "Initial" threat rating: the creature is hostile,
    // and will attack threats with this rating.
    static const int DISLIKE_THREAT_RATING;
    static const int INITIAL_THREAT_RATING;
    static const int THREAT_RATING_INCREMENT;

  protected:
    ThreatConstants();
    ~ThreatConstants();
};