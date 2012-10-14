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

ClassIdentifier DecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_DECORATIVE_STATUE;
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

ClassIdentifier KingDecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_KING_DECORATIVE_STATUE;
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

ClassIdentifier QueenDecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_QUEEN_DECORATIVE_STATUE;
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

ClassIdentifier WarlordDecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_WARLORD_DECORATIVE_STATUE;
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

ClassIdentifier KnightDecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_KNIGHT_DECORATIVE_STATUE;
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

ClassIdentifier HighPriestDecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE;
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

ClassIdentifier SorcerorDecorativeStatue::internal_class_identifier() const
{
  return CLASS_ID_SORCEROR_DECORATIVE_STATUE;
}
