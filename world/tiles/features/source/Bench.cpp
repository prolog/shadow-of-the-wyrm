#include "Bench.hpp"
#include "FeatureDescriptionTextKeys.hpp"

Bench::Bench(const Symbol& new_symbol)
: Feature(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BENCH, MaterialType::MATERIAL_TYPE_IRON, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Bench::clone()
{
  return new Bench(*this);
}

ClassIdentifier Bench::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BENCH;
}

#ifdef UNIT_TESTS
#include "unit_tests/Bench_test.cpp"
#endif

