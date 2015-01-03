#include "FieldOfViewStrategyFactory.hpp"
#include "RayCastingFieldOfViewStrategy.hpp"

FieldOfViewStrategyFactory::FieldOfViewStrategyFactory()
{
}

FieldOfViewStrategyFactory::~FieldOfViewStrategyFactory()
{
}

FieldOfViewStrategyPtr FieldOfViewStrategyFactory::create_field_of_view_strategy(const bool set_fov_tiles_view_flags, const FieldOfViewAlgorithmType fov_type)
{
  FieldOfViewStrategyPtr strategy;

  switch (fov_type)
  {
    case FieldOfViewAlgorithmType::FOV_RAY_CASTING:
    default:
      strategy = std::make_shared<RayCastingFieldOfViewStrategy>(set_fov_tiles_view_flags);
      break;
  }

  return strategy;
}
