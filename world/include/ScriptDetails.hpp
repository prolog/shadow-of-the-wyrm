#pragma once
#include <string>
#include "ISerializable.hpp"

// Encapsulates the details of a particular script: where it is located,
// and the chance associated with running it.  For example, a particular
// attack script might have a 25% chance of being run on successful hit.
class ScriptDetails : public ISerializable
{
  public:
    ScriptDetails(const std::string& new_script, const int new_chance);
    ScriptDetails();
    bool operator==(const ScriptDetails& sd) const;

    void set_script(const std::string& new_script);
    std::string get_script() const;

    void set_chance(const int new_chance);
    int get_chance() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string script;
    int chance;

    ClassIdentifier internal_class_identifier() const override;
};
