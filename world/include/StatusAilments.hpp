#pragma once
#include <set>
#include "ISerializable.hpp"

// A set of status ailments, typically attached to a particular Damage
// instance.
class StatusAilments : public ISerializable
{
  public:
    StatusAilments();
    bool operator==(const StatusAilments& sa) const;

    void set_override_defaults(const bool new_override_defaults);
    bool get_override_defaults() const;

    void set_ailments(const std::set<std::string>& new_ailments);
    std::set<std::string> get_ailments() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
  protected:
    // Whether or not to override the actual default for a particular
    // damage type.
    bool override_defaults;

    // The status ailments - when "override_defaults" is true, this
    // set should be used to determine the status ailments to attempt to
    // apply.
    std::set<std::string> ailments;

    ClassIdentifier internal_class_identifier() const override;
};

