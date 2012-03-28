#pragma once
#include "AlignmentEnums.hpp"

class Alignment
{
  public:
    Alignment();
    Alignment(const int new_alignment);

    void set_alignment(const int new_alignment);
    int get_alignment() const;
    int& get_alignment_ref();

    AlignmentRange get_alignment_range() const;

  protected:
    // This is just an integer rather than a Statistic because there
    // will be no spells, etc., that affect alignment - only actions
    // will affect alignment, and these are all permanent, so no
    // temporary/current values are needed, only the single, actual
    // value.
    int alignment;
    static const int ALIGNMENT_MIN;
    static const int ALIGNMENT_MAX;
    static const int EVIL_MIN;
    static const int EVIL_MAX;
    static const int NEUTRAL_MIN;
    static const int NEUTRAL_MAX;
    static const int GOOD_MIN;
    static const int GOOD_MAX;
};
