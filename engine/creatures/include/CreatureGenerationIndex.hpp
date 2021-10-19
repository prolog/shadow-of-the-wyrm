#pragma once
#include <vector>
#include "CreatureGenerationListValue.hpp"

using CreatureGenerationList = std::vector<CreatureGenerationListValue>;

class CreatureGenerationIndex
{
  public:
    CreatureGenerationIndex();
    CreatureGenerationIndex(const CreatureGenerationList& new_creature_list);

    CreatureGenerationList get() const;
    CreatureGenerationList get(const int danger_level) const;
    bool empty() const;

  protected:
    void initialize_index(const CreatureGenerationList& cgl);

    std::unordered_map<int, CreatureGenerationList> index;
    CreatureGenerationList creature_list;
};