#pragma once
#include "IDescriber.hpp"
#include "Feature.hpp"

class FeatureDescriber : public IDescriber
{
  public:
    FeatureDescriber(FeaturePtr new_feature);

    std::string describe() const override;

  protected:
    FeaturePtr feature;
};
