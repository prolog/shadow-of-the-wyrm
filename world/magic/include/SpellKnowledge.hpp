#pragma once
#include <map>
#include "common.hpp"
#include "ISerializable.hpp"
#include "IndividualSpellKnowledge.hpp"

typedef std::map<std::string, IndividualSpellKnowledge> SpellKnowledgeMap;

// A class that represents a particular creature's knowledge of the various
// spells defined in the configuration XML.
class SpellKnowledge : public ISerializable
{
  public:
    bool operator==(const SpellKnowledge& spell_k) const;

    void set_spell_knowledge(const std::string& spell_id, const IndividualSpellKnowledge& isk);
    IndividualSpellKnowledge get_spell_knowledge(const std::string& spell_id) const;
    uint count_spells_known() const;

    void set_most_recently_cast_spell_id(const std::string& spell_id);
    std::string get_most_recently_cast_spell_id() const;

    SpellKnowledgeMap get_known_spells() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    SpellKnowledgeMap spell_knowledge;
    std::string most_recently_cast_spell_id;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
