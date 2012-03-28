#pragma once
#include "AlignmentEnums.hpp"
#include "Feature.hpp"

class FeatureGenerator
{
  public:
    static FeaturePtr generate_altar(const std::string& deity_id, const AlignmentRange range);
    static FeaturePtr generate_door();
    static FeaturePtr generate_pew();

  protected:
    FeatureGenerator();
    ~FeatureGenerator();
};
