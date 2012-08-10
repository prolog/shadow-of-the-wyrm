#include <boost/make_shared.hpp>
#include "CreatureDescriber.hpp"
#include "DescriberFactory.hpp"
#include "FeatureDescriber.hpp"
#include "InventoryDescriber.hpp"
#include "TileDescriber.hpp"

using boost::make_shared;

DescriberFactory::DescriberFactory()
{
}

DescriberFactory::~DescriberFactory()
{
}

IDescriberPtr DescriberFactory::create_describer(TilePtr tile)
{
  IDescriberPtr describer = make_shared<TileDescriber>(tile);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(CreaturePtr creature)
{
  IDescriberPtr describer = make_shared<CreatureDescriber>(creature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(FeaturePtr feature)
{
  IDescriberPtr describer = make_shared<FeatureDescriber>(feature);
  return describer;
}

IDescriberPtr DescriberFactory::create_describer(const Inventory& inv)
{
  IDescriberPtr describer = make_shared<InventoryDescriber>(inv);
  return describer;
}
