#include "IDescriber.hpp"

IDescriber::~IDescriber()
{
}

std::string IDescriber::describe_for_tile_selection() const
{
  return describe();
}