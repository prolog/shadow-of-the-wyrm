#include "FeatureGenerator.hpp"
#include "XMLBedReader.hpp"

using namespace std;

FeaturePtr XMLBedReader::create(const XMLNode& bed_node) const
{
  FeaturePtr bed = FeatureGenerator::generate_bed();

  return bed;
}

