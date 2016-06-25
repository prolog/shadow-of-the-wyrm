#include "InscriptionTextKeys.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"

using namespace std;

const vector<string> InscriptionTextKeys::USEFUL_INSCRIPTION_SIDS
= {"INSCRIPTION_USEFUL_1",
   "INSCRIPTION_USEFUL_2",
   "INSCRIPTION_USEFUL_3",
   "INSCRIPTION_USEFUL_4",
   "INSCRIPTION_USEFUL_5",
   "INSCRIPTION_USEFUL_6",
   "INSCRIPTION_USEFUL_7",
   "INSCRIPTION_USEFUL_8",
   "INSCRIPTION_USEFUL_9",
   "INSCRIPTION_USEFUL_10",
   "INSCRIPTION_USEFUL_11",
   "INSCRIPTION_USEFUL_12",
   "INSCRIPTION_USEFUL_13",
   "INSCRIPTION_USEFUL_14"};
const vector<string> InscriptionTextKeys::USELESS_INSCRIPTION_SIDS
= {"INSCRIPTION_USELESS_1",
   "INSCRIPTION_USELESS_2",
   "INSCRIPTION_USELESS_3",
   "INSCRIPTION_USELESS_4",
   "INSCRIPTION_USELESS_5",
   "INSCRIPTION_USELESS_6",
   "INSCRIPTION_USELESS_7",
   "INSCRIPTION_USELESS_8",
   "INSCRIPTION_USELESS_9",
   "INSCRIPTION_USELESS_10",
   "INSCRIPTION_USELESS_11",
   "INSCRIPTION_USELESS_12",
   "INSCRIPTION_USELESS_13",
   "INSCRIPTION_USELESS_14"};

const int InscriptionTextKeys::PCT_CHANCE_USEFUL_INSCRIPTION = 50;

InscriptionTextKeys::InscriptionTextKeys()
{
}

InscriptionTextKeys::~InscriptionTextKeys()
{
}

string InscriptionTextKeys::get_random_inscription_sid()
{
  if (RNG::percent_chance(PCT_CHANCE_USEFUL_INSCRIPTION))
  {
    return get_random_useful_inscription_sid();
  }
  else
  {
    return get_random_useless_inscription_sid();
  }
}

string InscriptionTextKeys::get_random_useful_inscription_sid()
{
  return USEFUL_INSCRIPTION_SIDS.at(RNG::range(0, USEFUL_INSCRIPTION_SIDS.size()-1));
}

string InscriptionTextKeys::get_random_useless_inscription_sid()
{
  return USELESS_INSCRIPTION_SIDS.at(RNG::range(0, USELESS_INSCRIPTION_SIDS.size()-1));
}

