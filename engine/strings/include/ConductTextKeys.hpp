#pragma once
#include <string>
#include <vector>
#include "ConductTypes.hpp"

class ConductTextKeys
{
  public:
    static std::string get_conduct_message_sid(const ConductType ct);

    static const std::string CONDUCT_TITLE;

  protected:
    ConductTextKeys();
    ~ConductTextKeys();

    static void initialize_message_sids();
    static std::vector<std::string> conduct_message_sids;
};

