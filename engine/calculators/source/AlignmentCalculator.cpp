#include "AlignmentCalculator.hpp"
#include "Alignment.hpp"

const int AlignmentCalculator::BASE_ALIGNMENT_DELTA_COALIGNED = 10;
const int AlignmentCalculator::BASE_ALIGNMENT_DELTA_CROSSALIGNED = 250;
const float AlignmentCalculator::BASE_ALIGNMENT_MULTIPLIER_CROSSALIGNED = 1.0;

// Sacrificing on a co-aligned altar adjusts a creature's alignment slightly,
// drawing the alignment closer to the absolute value for the range.
int AlignmentCalculator::calculate_alignment_for_sacrifice_on_coaligned_altar(int current_alignment, const AlignmentRange altar_alignment_range)
{
  int new_alignment = current_alignment;
  int true_neutral = (Alignment::NEUTRAL_MIN + Alignment::NEUTRAL_MAX) / 2;

  switch (altar_alignment_range)
  {
    case ALIGNMENT_RANGE_EVIL:
      new_alignment -= BASE_ALIGNMENT_DELTA_COALIGNED;
      break;
    case ALIGNMENT_RANGE_GOOD:
      new_alignment += BASE_ALIGNMENT_DELTA_COALIGNED;
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      if (new_alignment > true_neutral)
      {
        new_alignment -= BASE_ALIGNMENT_DELTA_COALIGNED;
      }
      else if (new_alignment < true_neutral)
      {
        new_alignment += BASE_ALIGNMENT_DELTA_COALIGNED;
      }
      break;
    default:
      break;
  }
  
  return new_alignment;
}

// Sacrificing on a cross-aligned altar is risky, because it changes the
// creature's alignment; this can cause the creature to cross an alignment
// barrier, causing them to forsake their deity, become a fallen champion
// (if applicable), etc.
int AlignmentCalculator::calculate_alignment_for_sacrifice_on_crossaligned_altar(int current_alignment, const AlignmentRange current_alignment_range, const AlignmentRange altar_alignment_range)
{
  int new_alignment = current_alignment;
  float multiplier = BASE_ALIGNMENT_MULTIPLIER_CROSSALIGNED;

  if (current_alignment_range == altar_alignment_range)
  {
    return current_alignment;
  }

  // Crossing two alignment barriers causes a greater drift.
  if ((current_alignment_range == ALIGNMENT_RANGE_GOOD && altar_alignment_range == ALIGNMENT_RANGE_EVIL) ||
      (current_alignment_range == ALIGNMENT_RANGE_EVIL && altar_alignment_range == ALIGNMENT_RANGE_GOOD))
  {
    multiplier *= 1.5;
  }

  switch (current_alignment_range)
  {
    case ALIGNMENT_RANGE_GOOD:
      new_alignment -= static_cast<int>(BASE_ALIGNMENT_DELTA_CROSSALIGNED * multiplier);
      break;
    case ALIGNMENT_RANGE_EVIL:
      new_alignment += static_cast<int>(BASE_ALIGNMENT_DELTA_CROSSALIGNED * multiplier);
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      if (altar_alignment_range == ALIGNMENT_RANGE_GOOD)
      {
        new_alignment += static_cast<int>(BASE_ALIGNMENT_DELTA_CROSSALIGNED * multiplier);
      }
      else
      {
        new_alignment -= static_cast<int>(BASE_ALIGNMENT_DELTA_CROSSALIGNED * multiplier);
      }
      break;
    default:
      break;
  }

  return new_alignment;
}

#ifdef UNIT_TESTS
#include "unit_tests/AlignmentCalculator_test.cpp"
#endif