#pragma once
#include "AlignmentEnums.hpp"

class AlignmentCalculator
{
  public:
    int calculate_alignment_for_sacrifice_on_coaligned_altar(int current_alignment, const AlignmentRange altar_alignment_range);
};

