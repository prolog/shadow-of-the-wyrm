#pragma once
#include "IMapTypeQuery.hpp"

class OverworldMapTypeQuery : public IMapTypeQuery
{
  public:
    virtual bool should_update_depth() const override;
};

class UnderworldMapTypeQuery : public IMapTypeQuery
{
  public:
    virtual bool should_update_depth() const override;
};

