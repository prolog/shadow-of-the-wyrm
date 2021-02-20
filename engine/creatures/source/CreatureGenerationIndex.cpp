#include <algorithm>
#include <iterator>
#include "CreatureGenerationIndex.hpp"

CreatureGenerationIndex::CreatureGenerationIndex()
{
}

CreatureGenerationIndex::CreatureGenerationIndex(const CreatureGenerationList& new_creature_list)
: creature_list(new_creature_list)
{
  initialize_index(creature_list);
}

void CreatureGenerationIndex::initialize_index(const CreatureGenerationList& cgl)
{
  for (const auto& cgl_val : cgl)
  {
    int danger_level = cgl_val.get_creature_generation_values().get_danger_level();
    auto idx_it = index.find(danger_level);

    if (idx_it != index.end())
    {
      idx_it->second.push_back(cgl_val);
    }
    else
    {
      index[danger_level] = {cgl_val};
    }
  }
}

CreatureGenerationList CreatureGenerationIndex::get() const
{
  return creature_list;
}

CreatureGenerationList CreatureGenerationIndex::get(const int danger) const
{
  auto idx_it = index.find(danger);

  if (idx_it != index.end())
  {
    return idx_it->second;
  }

  return {};
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureGenerationIndex_test.cpp"
#endif
