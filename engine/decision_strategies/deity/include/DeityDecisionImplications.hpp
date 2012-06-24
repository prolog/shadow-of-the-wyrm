#pragma once
#include <string>

class DeityDecisionImplications
{
  public:
    DeityDecisionImplications();
    DeityDecisionImplications(const int new_piety, const std::string new_message_sid);

    void set_piety_loss(const int new_piety);
    int get_piety_loss() const;

    void set_message_sid(const std::string& new_message_sid);
    std::string get_message_sid() const;

  protected:
    int piety_loss;
    std::string message_sid;
};
