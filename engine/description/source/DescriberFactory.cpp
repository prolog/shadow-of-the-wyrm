#include <boost/make_shared.hpp>
#include "CreatureDescriber.hpp"
#include "DescriberFactory.hpp"
#include "FeatureDescriber.hpp"
#include "InventoryDescriber.hpp"
#include "TileDescriber.hpp"

DescriberFactory::DescriberFactory()
{
}

DescriberFactory::~DescriberFactory()
{
}

IDescriberPtr DescriberFactory::create_describer(TilePtr tile)
{
  IDescriberPtr describer = boost::make_shared<TileDescriber>(tile);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr creature)
{
  IDescriberPtr describer = boost::make_shared<CreatureDescriber>(creature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(FeaturePtr feature)
{
  IDescriberPtr describer = boost::make_shared<FeatureDescriber>(feature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(const Inventory& inv)
{
  IDescriberPtr describer = boost::make_shared<InventoryDescriber>(inv);
  return describer;
}
