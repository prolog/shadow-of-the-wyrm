#include "StatueGenerator.hpp"
#include "XMLDecorativeStatueReader.hpp"

using namespace std;

FeaturePtr XMLDecorativeStatueReader::create(const XMLNode& ds_node) const
{
  FeaturePtr ds;

  if (!ds_node.is_null())
  {
    DecorativeStatueType dst = static_cast<DecorativeStatueType>(XMLUtils::get_child_node_int_value(ds_node, "Type", 0));
    ds = StatueGenerator::generate_decorative_statue(dst);
  }

  return ds;
}

