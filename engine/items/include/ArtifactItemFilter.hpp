#pragma once
#include "IItemFilter.hpp"

// Used for displaying only artifacts
class ArtifactItemFilter : public IItemFilter
{
  public:
    bool passes_filter(ItemPtr item) const override;
};

