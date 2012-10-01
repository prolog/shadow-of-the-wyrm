#include <boost/make_shared.hpp>
#include "DecorativeStatues.hpp"
#include "StatueGenerator.hpp"

StatueGenerator::StatueGenerator()
{
}

// Generate a random decorative statue
FeaturePtr StatueGenerator::generate_decorative_statue(const DecorativeStatueType type)
{
  FeaturePtr statue;

  switch(type)
  {
    case DECORATIVE_STATUE_TYPE_KING:
      statue = boost::make_shared<KingDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_QUEEN:
      statue = boost::make_shared<QueenDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_WARLORD:
      statue = boost::make_shared<WarlordDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_KNIGHT:
      statue = boost::make_shared<KnightDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_HIGH_PRIEST:
      statue = boost::make_shared<HighPriestDecorativeStatue>();
      break;
    case DECORATIVE_STATUE_TYPE_SORCEROR:
      statue = boost::make_shared<SorcerorDecorativeStatue>();
      break;
    default:
      break;
  }

  return statue;
}
