#pragma once
#include "AlignmentEnums.hpp"
#include "Item.hpp"

class AlignmentCalculator
{
  public:
    int calculate_alignment_for_sacrifice_on_coaligned_altar(int current_alignment, const AlignmentRange altar_alignment_range);
    int calculate_alignment_for_sacrifice_on_crossaligned_altar(int current_alignment, const AlignmentRange current_alignment_range, const AlignmentRange altar_alignment_range);
    int calculate_pct_chance_for_altar_conversion(ItemPtr item, const AlignmentRange current_alignment_range, const AlignmentRange altar_alignment_range);
  protected:
    static const int BASE_ALIGNMENT_DELTA_COALIGNED;
    static const int BASE_ALIGNMENT_DELTA_CROSSALIGNED;
    static const float BASE_ALIGNMENT_MULTIPLIER_CROSSALIGNED;
};

