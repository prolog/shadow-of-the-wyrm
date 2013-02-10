#pragma once
#include <map>
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

typedef std::map<std::string, uint> MortuaryCountMap;

// Used to identify the number of each creature killed.  There is a game-
// level instance, as well as one for each creature generated.
class Mortuary : public ISerializable
{
  public:
    bool operator==(const Mortuary& m);

    void add_creature_kill(const std::string& creature_id);
    
    MortuaryCountMap get_creatures_killed() const;

    uint get_num_creature_killed(const std::string& creature_id) const;
    uint get_num_creatures_killed() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    MortuaryCountMap creatures_killed;

  private:
    ClassIdentifier internal_class_identifier() const;
};

