#include "DecorativeStatues.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

using std::string;

// Abstract base decorative statue class.
DecorativeStatue::DecorativeStatue()
: Feature(MaterialFactory::create_material(MATERIAL_TYPE_MARBLE))
{
}

bool DecorativeStatue::kick()
{
  return true;
}

bool DecorativeStatue::handle()
{
  return true;
}

bool DecorativeStatue::get_is_blocking() const
{
  return true;
}

uchar DecorativeStatue::get_symbol() const
{
  return 'I';
}

// King
KingDecorativeStatue::KingDecorativeStatue()
: DecorativeStatue()
{
}

string KingDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KING_STATUE;
}

// Queen
QueenDecorativeStatue::QueenDecorativeStatue()
: DecorativeStatue()
{
}

string QueenDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_QUEEN_STATUE;
}

// Warlord
WarlordDecorativeStatue::WarlordDecorativeStatue()
: DecorativeStatue()
{
}

string WarlordDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WARLORD_STATUE;
}

// Knight
KnightDecorativeStatue::KnightDecorativeStatue()
: DecorativeStatue()
{
}

string KnightDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KNIGHT_STATUE;
}

// High Priest
HighPriestDecorativeStatue::HighPriestDecorativeStatue()
: DecorativeStatue()
{
}

string HighPriestDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE;
}

// Sorceror
SorcerorDecorativeStatue::SorcerorDecorativeStatue()
: DecorativeStatue()
{
}

string SorcerorDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SORCEROR_STATUE;
}

