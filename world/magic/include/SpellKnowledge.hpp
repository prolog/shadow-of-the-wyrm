#pragma once
#include <map>
#include "common.hpp"
#include "ISerializable.hpp"

typedef std::map<std::string, uint> SpellKnowledgeMap;

// A class that represents a particular creature's knowledge of the various
// spells defined in the configuration XML.
class SpellKnowledge : public ISerializable
{
  public:
    bool operator==(const SpellKnowledge& spell_k);

    void set_spell_knowledge(const std::string& spell_id, const uint cast_count);
    uint get_spell_knowledge(const std::string& spell_id) const;
    uint count_spells_known() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    SpellKnowledgeMap spell_knowledge;

  private:
    ClassIdentifier internal_class_identifier() const;
};
