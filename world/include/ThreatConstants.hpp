#pragma once

class ThreatConstants
{
  public:
    // "Dislike" threat rating: the creature is not hostile,
    // but neither is it friendly.  NPCs will not attack
    // threats with this rating.
    //
    // "Initial" threat rating: the creature is hostile,
    // and will attack threats with this rating. Some
    // factors (same religion, etc) might end up removing
    // this.
    //
    // "Active" threat rating: the creature is hostile
    // due to some active threat (like being attacked)
    // and mitigating factors for the initial threat
    // rating won't remove this one.
    static const int DISLIKE_THREAT_RATING;
    static const int INITIAL_THREAT_RATING;
    static const int THREAT_RATING_INCREMENT;
    static const int ACTIVE_THREAT_RATING;

  protected:
    ThreatConstants();
    ~ThreatConstants();
};