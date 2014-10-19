#include <algorithm>
#include "AlignmentCalculator.hpp"
#include "Alignment.hpp"
#include "AlignmentUtils.hpp"

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
  if (AlignmentUtils::are_alignments_opposites(current_alignment_range, altar_alignment_range))
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

// Get the percent chance that an altar
int AlignmentCalculator::calculate_pct_chance_for_altar_conversion(ItemPtr item, const AlignmentRange current_alignment_range, const AlignmentRange altar_alignment_range)
{
  int pct_chance = 0;
  int numerator = 0;

  if (item)
  {
    numerator = item->get_value() * item->get_quantity();

    pct_chance = (numerator / 10);
    pct_chance = std::min<int>(pct_chance, 100);

    // Harder to convert an altar of a more extreme alignment.
    if (AlignmentUtils::are_alignments_opposites(current_alignment_range, altar_alignment_range))
    {
      pct_chance = static_cast<int>(pct_chance * 0.75);
    }

    // There's always a slim chance to convert an altar.
    pct_chance = std::max<int>(pct_chance, 1);
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/AlignmentCalculator_test.cpp"
#endif