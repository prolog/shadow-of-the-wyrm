#include "Bench.hpp"
#include "MaterialFactory.hpp"
#include "StringConstants.hpp"

Bench::Bench()
: Feature(MaterialFactory::create_material(MATERIAL_TYPE_IRON))
{
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