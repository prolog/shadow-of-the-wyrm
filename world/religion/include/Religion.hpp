#pragma once
#include <map>
#include <string>
#include "DeityStatus.hpp"
#include "ISerializable.hpp"

// Religion describes a creature's religion.  A creature can only worship 
// one deity, but can be converted to other deities later on.  A container
// of relations to all deities is kept so that relations with the
// previous worshipped deities can be known.

// Typedef'd because typing C++ templates is hard
typedef std::map<std::string, DeityStatus> DeityRelations;

class Religion : public ISerializable
{
  public:
    Religion(const std::string& new_deity_id = "");
    virtual bool operator==(const Religion& religion) const;

    bool is_atheist() const;
    
    void set_active_deity_id(const std::string& new_deity_id);
    std::string get_active_deity_id() const;

    void set_deity_relations(const DeityRelations& new_deity_relations);
    DeityRelations get_deity_relations() const;
    DeityRelations& get_deity_relations_ref();
    
    void set_deity_status(const std::string& deity_id, const DeityStatus& new_deity_status);
    DeityStatus get_deity_status(const std::string& deity_id) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string deity_id;
    DeityRelations deity_relations;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
