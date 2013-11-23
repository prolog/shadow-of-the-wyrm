#include "DecorativeStatues.hpp"
#include "RegularStatues.hpp"
#include "StatueGenerator.hpp"

using namespace std;

StatueGenerator::StatueGenerator()
{
}

// Generate a random decorative statue
FeaturePtr StatueGenerator::generate_decorative_statue(const DecorativeStatueType type)
{
  FeaturePtr statue;

  static_assert(DECORATIVE_STATUE_TYPE_LAST == 5, "Unexpected DECORATIVE_STATUE_TYPE_LAST value.");

  switch(type)
  {
    case DECORATIVE_STATUE_TYPE_KING:
      statue = std::make_shared<KingDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_QUEEN:
      statue = std::make_shared<QueenDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_WARLORD:
      statue = std::make_shared<WarlordDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_KNIGHT:
      statue = std::make_shared<KnightDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_HIGH_PRIEST:
      statue = std::make_shared<HighPriestDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_SORCEROR:
      statue = std::make_shared<SorcerorDecorativeStatue>();
      break;
    default:
      break;
  }

  return statue;
}

PetrifiedCorpseStatuePtr StatueGenerator::generate_petrified_corpse_statue(const string& corpse_description_sid)
{
  PetrifiedCorpseStatuePtr statue;
  statue = std::make_shared<PetrifiedCorpseStatue>(corpse_description_sid);
  
  return statue;
}