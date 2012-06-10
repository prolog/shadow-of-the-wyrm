#include <boost/make_shared.hpp>
#include "FieldOfViewStrategyFactory.hpp"
#include "RayCastingFieldOfViewStrategy.hpp"

using boost::make_shared;

FieldOfViewStrategyFactory::FieldOfViewStrategyFactory()
{
}

FieldOfViewStrategyFactory::~FieldOfViewStrategyFactory()
{
}

FieldOfViewStrategyPtr FieldOfViewStrategyFactory::create_field_of_view_strategy(const FieldOfViewAlgorithmType fov_type)
{
  FieldOfViewStrategyPtr strategy;

  switch (fov_type)
  {
    case FOV_RAY_CASTING:
    default:
      strategy = make_shared<RayCastingFieldOfViewStrategy>();
      break;
  }

  return strategy;
}
