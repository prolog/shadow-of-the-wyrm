#pragma once
#include <map>
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

// Used to track the number of each creature killed.
// The amount killed is tracked by "count", and "max"
// is used to determine if the creature is unique or not.
struct MortuaryEntry
{
  bool operator==(const MortuaryEntry& me) const;

  int max = 0;
  int count = 0;
};

using MortuaryCountMap = std::map<std::string, MortuaryEntry>;

// Used to identify the number of each creature killed.  There is a game-
// level instance, as well as one for each creature generated.
class Mortuary : public ISerializable
{
  public:
    Mortuary();

    bool operator==(const Mortuary& m) const;

    void add_creature_kill(const std::string& creature_id, const bool is_unique = false);
    
    MortuaryCountMap get_creatures_killed() const;

    int get_num_creature_killed(const std::string& creature_id) const;
    int get_num_creatures_killed() const;
    int get_num_uniques_killed() const;

    void set_max_level_difference(const std::pair<int, std::string>& new_max_level_difference);
    std::pair<int, std::string> get_max_level_difference() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    MortuaryCountMap creatures_killed;
    std::pair<int, std::string> max_level_difference;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

