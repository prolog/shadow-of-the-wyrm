#pragma once
#include <string>
#include <vector>

class InscriptionTextKeys
{
  public:
    static std::string get_random_inscription_sid();

  protected:
    InscriptionTextKeys();
    ~InscriptionTextKeys();

    static std::string get_random_useful_inscription_sid();
    static std::string get_random_useless_inscription_sid();

    static const std::vector<std::string> USEFUL_INSCRIPTION_SIDS;
    static const std::vector<std::string> USELESS_INSCRIPTION_SIDS;

    static const int PCT_CHANCE_USEFUL_INSCRIPTION;
};
