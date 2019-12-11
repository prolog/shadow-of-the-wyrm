#include "DecorativeStatues.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

// Abstract base decorative statue class.
DecorativeStatue::DecorativeStatue(const string& new_description_sid, const Symbol& new_symbol)
: Feature(new_description_sid, MaterialType::MATERIAL_TYPE_MARBLE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

bool DecorativeStatue::get_is_blocking() const
{
  return true;
}

ClassIdentifier DecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DECORATIVE_STATUE;
}

// King
KingDecorativeStatue::KingDecorativeStatue(const Symbol& new_symbol)
: DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KING_STATUE, new_symbol)
{
}

Feature* KingDecorativeStatue::clone()
{
  return new KingDecorativeStatue(*this);
}

ClassIdentifier KingDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE;
}

// Queen
QueenDecorativeStatue::QueenDecorativeStatue(const Symbol& new_symbol)
: DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_QUEEN_STATUE, new_symbol)
{
}

Feature* QueenDecorativeStatue::clone()
{
  return new QueenDecorativeStatue(*this);
}

ClassIdentifier QueenDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE;
}

// Warlord
WarlordDecorativeStatue::WarlordDecorativeStatue(const Symbol& new_symbol)
: DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WARLORD_STATUE, new_symbol)
{
}

Feature* WarlordDecorativeStatue::clone()
{
  return new WarlordDecorativeStatue(*this);
}

ClassIdentifier WarlordDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE;
}

// Knight
KnightDecorativeStatue::KnightDecorativeStatue(const Symbol& new_symbol)
: DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KNIGHT_STATUE, new_symbol)
{
}

Feature* KnightDecorativeStatue::clone()
{
  return new KnightDecorativeStatue(*this);
}

ClassIdentifier KnightDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE;
}

// High Priest
HighPriestDecorativeStatue::HighPriestDecorativeStatue(const Symbol& new_symbol)
: DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE, new_symbol)
{
}

Feature* HighPriestDecorativeStatue::clone()
{
  return new HighPriestDecorativeStatue(*this);
}

ClassIdentifier HighPriestDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE;
}

// Sorceror
SorcerorDecorativeStatue::SorcerorDecorativeStatue(const Symbol& new_symbol)
: DecorativeStatue(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SORCEROR_STATUE, new_symbol)
{
}

Feature* SorcerorDecorativeStatue::clone()
{
  return new SorcerorDecorativeStatue(*this);
}

ClassIdentifier SorcerorDecorativeStatue::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DecorativeStatues_test.cpp"
#endif

