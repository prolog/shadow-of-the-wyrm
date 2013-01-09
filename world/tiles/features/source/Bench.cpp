#include "Bench.hpp"
#include "StringConstants.hpp"

Bench::Bench()
: Feature(MATERIAL_TYPE_IRON)
{
}

Feature* Bench::clone()
{
  return new Bench(*this);
}

bool Bench::handle()
{
  return true;
}

bool Bench::kick()
{
  return true;
}

std::string Bench::get_description_sid() const
{
  return FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_BENCH;
}

uchar Bench::get_symbol() const
{
  return '-';
}

ClassIdentifier Bench::internal_class_identifier() const
{
  return CLASS_ID_BENCH;
}

#ifdef UNIT_TESTS
#include "unit_tests/Bench_test.cpp"
#endif

