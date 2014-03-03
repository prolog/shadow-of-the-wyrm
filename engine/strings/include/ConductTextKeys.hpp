#pragma once
#include <vector>
#include "ConductTypes.hpp"

class ConductTextKeys
{
  public:
    std::string get_conduct_message_sid(const ConductType ct);

  protected:
    ConductTextKeys();
    ~ConductTextKeys();

    void initialize_message_sids();
    std::vector<std::string> conduct_message_sids;
};

