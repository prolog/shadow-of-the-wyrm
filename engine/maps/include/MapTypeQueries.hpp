#pragma once
#include "IMapTypeQuery.hpp"

class DepthlessMapTypeQuery : public IMapTypeQuery
{
  public:
    virtual bool should_update_depth() const override;
};

class DepthMapTypeQuery : public IMapTypeQuery
{
  public:
    virtual bool should_update_depth() const override;
};
