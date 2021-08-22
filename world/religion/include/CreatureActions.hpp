#pragma once
#include <map>
#include <string>
#include "ISerializable.hpp"

class CreatureActionKeys
{
  public:
    static const std::string ACTION_ATTACK_FRIENDLY;
    static const std::string ACTION_CANNIBALISM;
    static const std::string ACTION_DESECRATE_GOOD; // Kicking pews, altars, etc.
    static const std::string ACTION_DESECRATE_NEUTRAL;
    static const std::string ACTION_DESECRATE_EVIL;
  	static const std::string ACTION_GRAVEROBBING;
    static const std::string ACTION_SKIN_HUMANOID;
    static const std::string ACTION_BURY_REMAINS;
    static const std::string ACTION_PLANT_SEEDS;
    static const std::string ACTION_PACIFY;
    static const std::string ACTION_BLOODLETTING;
    static const std::string ACTION_SNEAK_ATTACK;
    static const std::string ACTION_RAGE;
    static const std::string ACTION_SMITE;
    static const std::string ACTION_PETRIFY;
    static const std::string ACTION_BURN;
    static const std::string ACTION_FREEZE;
    static const std::string ACTION_STUN;
    static const std::string ACTION_LEARN_SPELL;
};

using CreatureActionMap = std::map<std::string, bool>;

// Describes creature actions, which the deity can either like, dislike,
// or not care about.  Examples include using magic, attacking friendly
// creatures, eating one's own race, and so on.
class CreatureActions : public ISerializable
{
  public:
    bool operator==(const CreatureActions& ca) const;

    void set_action_value(const std::string& action, const bool val);
    bool get_action_value(const std::string& action) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    CreatureActionMap creature_action_map;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

