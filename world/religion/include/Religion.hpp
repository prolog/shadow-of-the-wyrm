#pragma once
#include <map>
#include <string>
#include "DeityStatus.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// Religion describes a creature's religion.  A creature can only worship 
// one deity, but can be converted to other deities later on.  A container
// of relations to all deities is kept so that relations with the
// previous worshipped deities can be known.

// Typedef'd because typing C++ templates is hard
typedef std::map<std::string, DeityStatus> DeityRelations;

class Religion
{
  public:
    Religion(const std::string& new_deity_id = "");

    bool is_atheist() const;
    
    void set_active_deity_id(const std::string& new_deity_id);
    std::string get_active_deity_id() const;

    void set_deity_relations(const DeityRelations& new_deity_relations);
    DeityRelations get_deity_relations() const;
    DeityRelations& get_deity_relations_ref();
    
    void set_deity_status(const std::string& deity_id, const DeityStatus& new_deity_status);
    DeityStatus get_deity_status(const std::string& deity_id) const;

  protected:
    std::string deity_id;
    DeityRelations deity_relations;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & deity_id & deity_relations;
    }
};
