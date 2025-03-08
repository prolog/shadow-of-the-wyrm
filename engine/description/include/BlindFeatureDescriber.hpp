#pragma once
#include "FeatureDescriber.hpp"
#include "Feature.hpp"

class BlindFeatureDescriber : public FeatureDescriber
{
  public:
    BlindFeatureDescriber();
    virtual ~BlindFeatureDescriber() = default;

    virtual std::string describe() const override;
};

