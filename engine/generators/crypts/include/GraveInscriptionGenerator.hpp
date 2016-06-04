#pragma once
#include <string>

// Generates an inscription for a grave.  Given the current year, it will
// select a death year, pick an age, and then select the start year.  Then,
// a name, and then the inscription is created.
class GraveInscriptionGenerator
{
  public:
    std::string generate_inscription(const int current_year, const int min_year = -1);

  protected:
    static const int MIN_GRAVE_YEAR;
    static const int PCT_CHANCE_DETAILS;
    static const int PCT_CHANCE_BIRTH_YEAR;
    static const int MAX_AGE;
};

