#include "DecorativeStatues.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

// Abstract base decorative statue class.
DecorativeStatue::DecorativeStatue()
: Feature(MATERIAL_TYPE_MARBLE, ALIGNMENT_RANGE_NEUTRAL)
{
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
  return ClassIdentifier::CLASS_ID_DECORATIVE_STATUE;
}

// King
KingDecorativeStatue::KingDecorativeStatue()
: DecorativeStatue()
{
}

Feature* KingDecorativeStatue::clone()
{
  return new KingDecorativeStatue(*this);
}

string KingDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KING_STATUE;
}

ClassIdentifier KingDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE;
}

// Queen
QueenDecorativeStatue::QueenDecorativeStatue()
: DecorativeStatue()
{
}

Feature* QueenDecorativeStatue::clone()
{
  return new QueenDecorativeStatue(*this);
}

string QueenDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_QUEEN_STATUE;
}

ClassIdentifier QueenDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE;
}

// Warlord
WarlordDecorativeStatue::WarlordDecorativeStatue()
: DecorativeStatue()
{
}

Feature* WarlordDecorativeStatue::clone()
{
  return new WarlordDecorativeStatue(*this);
}

string WarlordDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WARLORD_STATUE;
}

ClassIdentifier WarlordDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE;
}

// Knight
KnightDecorativeStatue::KnightDecorativeStatue()
: DecorativeStatue()
{
}

Feature* KnightDecorativeStatue::clone()
{
  return new KnightDecorativeStatue(*this);
}

string KnightDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KNIGHT_STATUE;
}

ClassIdentifier KnightDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE;
}

// High Priest
HighPriestDecorativeStatue::HighPriestDecorativeStatue()
: DecorativeStatue()
{
}

Feature* HighPriestDecorativeStatue::clone()
{
  return new HighPriestDecorativeStatue(*this);
}

string HighPriestDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE;
}

ClassIdentifier HighPriestDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE;
}

// Sorceror
SorcerorDecorativeStatue::SorcerorDecorativeStatue()
: DecorativeStatue()
{
}

Feature* SorcerorDecorativeStatue::clone()
{
  return new SorcerorDecorativeStatue(*this);
}

string SorcerorDecorativeStatue::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SORCEROR_STATUE;
}

ClassIdentifier SorcerorDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DecorativeStatues_test.cpp"
#endif

