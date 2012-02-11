#pragma once
#include "Generator.hpp"

class DesertGenerator : public Generator
{
  public:
    virtual MapPtr generate(const Dimensions& dim);
};
