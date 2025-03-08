#pragma once
#include "IItemFilter.hpp"

// Used for displaying only artifacts
class ArtifactItemFilter : public IItemFilter
{
  public:
    virtual ~ArtifactItemFilter() = default;

    bool passes_filter(ItemPtr item) const override;
};

