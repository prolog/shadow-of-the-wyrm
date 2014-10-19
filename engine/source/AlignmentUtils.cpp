#include "AlignmentUtils.hpp"

AlignmentUtils::AlignmentUtils()
{
}

AlignmentUtils::~AlignmentUtils()
{
}

bool AlignmentUtils::are_alignments_opposites(const AlignmentRange a1, const AlignmentRange a2)
{
  return ((a1 == ALIGNMENT_RANGE_GOOD && a2 == ALIGNMENT_RANGE_EVIL) || (a1 == ALIGNMENT_RANGE_EVIL && a2 == ALIGNMENT_RANGE_GOOD));
}

#ifdef UNIT_TESTS
#include "unit_tests/AlignmentUtils_test.cpp"
#endif

