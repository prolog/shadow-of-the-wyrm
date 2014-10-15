#include "AlignmentUtils.hpp"
#include "Alignment.hpp"

AlignmentUtils::AlignmentUtils()
{
}

AlignmentUtils::~AlignmentUtils()
{
}

int AlignmentUtils::get_new_alignment_for_sacrifice_on_coaligned_altar(int current_alignment, const AlignmentRange altar_alignment_range)
{
  int new_alignment = current_alignment;
  int true_neutral = (Alignment::NEUTRAL_MIN + Alignment::NEUTRAL_MAX) / 2;

  switch (altar_alignment_range)
  {
    case ALIGNMENT_RANGE_EVIL:
      new_alignment -= 10;
      break;
    case ALIGNMENT_RANGE_GOOD:
      new_alignment += 10;
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      if (new_alignment > true_neutral)
      {
        new_alignment -= 10;
      }
      else if (new_alignment < true_neutral)
      {
        new_alignment += 10;
      }
      break;
    default:
      break;
  }
  
  return new_alignment;
}

#ifdef UNIT_TESTS
#include "unit_tests/AlignmentUtils_test.cpp"
#endif
