#include <sstream>
#include <boost/algorithm/string.hpp>
#include "GraveInscriptionGenerator.hpp"
#include "Naming.hpp"
#include "RNG.hpp"

using namespace std;

const int GraveInscriptionGenerator::MIN_GRAVE_YEAR = 10;
const int GraveInscriptionGenerator::PCT_CHANCE_DETAILS = 66;
const int GraveInscriptionGenerator::PCT_CHANCE_BIRTH_YEAR = 70;
const int GraveInscriptionGenerator::MAX_AGE = 100;

string GraveInscriptionGenerator::generate_inscription(const int current_year, const int min_death_year)
{
  ostringstream ss;
  CreatureSex sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));

  ss << boost::to_upper_copy<std::string>(Naming::generate_name(sex));

  if (RNG::percent_chance(PCT_CHANCE_DETAILS))
  {
    ss << ". ";

    int min_year = min_death_year;

    if (min_year == -1)
    {
      min_year = MIN_GRAVE_YEAR;
    }

    if (min_year <= current_year)
    {
      int death_year = RNG::range(min_year, current_year);

      if (RNG::percent_chance(PCT_CHANCE_BIRTH_YEAR))
      {
        int birth_year = std::max(min_year, death_year - RNG::range(1, MAX_AGE));
        ss << birth_year << " - ";
      }

      ss << death_year << ".";
    }
  }

  string inscription = ss.str();
  return inscription;
}

