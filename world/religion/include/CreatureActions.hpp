#pragma once
#include <map>
#include <string>

class CreatureActionKeys
{
  public:
    static const std::string ACTION_ATTACK_FRIENDLY;
    static const std::string ACTION_CANNIBALISM;
};

typedef std::map<std::string, bool> CreatureActionMap;

// Describes creature actions, which the deity can either like, dislike,
// or not care about.  Examples include using magic, attacking friendly
// creatures, eating one's own race, and so on.
class CreatureActions
{
  public:
    void set_action_value(const std::string& action, const bool val);
    bool get_action_value(const std::string& action) const;

  protected:
    CreatureActionMap creature_action_map;
};

