#include "DeityUtils.hpp"
#include "RNG.hpp"

using namespace std;

DeityUtils::DeityUtils()
{
}

DeityUtils::~DeityUtils()
{
}

pair<DeityPtr, AlignmentRange> DeityUtils::get_random_deity_with_align(const Game& game)
{
  DeityPtr rando;
  AlignmentRange arange = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL;

  const DeityMap& dm = game.get_deities_cref();
  vector<DeityPtr> rand_deities;

  for (const auto& dm_pair : dm)
  {
    if (!dm_pair.first.empty() && dm_pair.second != nullptr)
    {
      rand_deities.push_back(dm_pair.second);
    }
  }

  if (!rand_deities.empty())
  {
    rando = rand_deities.at(RNG::range(0, rand_deities.size()-1));

    if (rando != nullptr)
    {
      arange = rando->get_alignment_range();
    }
  }

  return make_pair(rando, arange);
}
