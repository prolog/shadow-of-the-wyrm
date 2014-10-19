#pragma once
#include "Alignment.hpp"

class AlignmentUtils
{
  public:
    static bool are_alignments_opposites(const AlignmentRange a1, const AlignmentRange a2);

  protected:
    AlignmentUtils();
    ~AlignmentUtils();
};

