#include "FeatureGenerator.hpp"
#include "XMLSignReader.hpp"

using namespace std;

FeaturePtr XMLSignReader::create(const XMLNode& sign_node) const
{
  string text_sid = XMLUtils::get_child_node_value(sign_node, "TextSID");
  FeaturePtr sign = FeatureGenerator::generate_sign(text_sid);
  return sign;
}

