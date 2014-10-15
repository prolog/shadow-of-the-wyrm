#pragma once
#include "AlignmentEnums.hpp"

class AlignmentUtils
{
  public:
    int get_new_alignment_for_sacrifice_on_coaligned_altar(int current_alignment, const AlignmentRange altar_alignment_range);

  protected:
    AlignmentUtils();
    ~AlignmentUtils();
};

