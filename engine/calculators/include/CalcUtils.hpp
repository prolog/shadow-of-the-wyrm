#pragma once

class CalcUtils
{
  public:
    // Returns the parameter if between 0 and 100.  If less than 0,
    // returns 0.  If greater than 100, returns 100.
    static int pct_val(const int pct);
};

