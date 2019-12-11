#include "FirePillar.hpp"
#include "FeatureDescriptionTextKeys.hpp"

using std::string;

FirePillar::FirePillar(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FIRE_PILLAR, MaterialType::MATERIAL_TYPE_STONE, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
  shimmer_colours = ShimmerColours({Colour::COLOUR_RED, Colour::COLOUR_BOLD_RED, Colour::COLOUR_BOLD_YELLOW}, 75);
}

Feature* FirePillar::clone()
{
  return new FirePillar(*this);
}

bool FirePillar::get_is_blocking() const
{
  return true;
}

ClassIdentifier FirePillar::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FIRE_PILLAR;
}
// FIXME: Still need to add lit/unlit state.

#ifdef UNIT_TESTS
#include "unit_tests/FirePillar_test.cpp"
#endif

