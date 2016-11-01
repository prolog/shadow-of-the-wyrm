#pragma once
#include <string>
#include "Creature.hpp"
#include "Feature.hpp"

class DeityDecisionImplications
{
  public:
    DeityDecisionImplications();
    DeityDecisionImplications(const int new_piety, const std::string new_message_sid);

    // Returns the increase in piety as the result of the sacrifice.
    int adjust_creature_piety(CreaturePtr creature, FeaturePtr feature);

    void set_piety_loss(const int new_piety);
    int get_piety_loss() const;

    // This is just (piety_loss * -1)
    int get_piety_gain() const;

    void set_message_sid(const std::string& new_message_sid);
    std::string get_message_sid() const;

  protected:
    int piety_loss;
    std::string message_sid;
};
