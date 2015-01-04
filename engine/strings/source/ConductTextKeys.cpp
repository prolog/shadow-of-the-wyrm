#include "ConductTextKeys.hpp"

using namespace std;

vector<string> ConductTextKeys::conduct_message_sids;

const string ConductTextKeys::CONDUCT_TITLE = "CONDUCT_TITLE";

ConductTextKeys::ConductTextKeys()
{
}

ConductTextKeys::~ConductTextKeys()
{
}

string ConductTextKeys::get_conduct_message_sid(const ConductType ct)
{
  static_assert(ConductType::CONDUCT_SIZE == ConductType(5), "Unexpected number of conducts.");

  if (conduct_message_sids.empty())
  {
    initialize_message_sids();
  }

  return conduct_message_sids.at(static_cast<int>(ct));
}

void ConductTextKeys::initialize_message_sids()
{
  conduct_message_sids = {"CONDUCT_MESSAGE_FOODLESS", "CONDUCT_MESSAGE_VEGETARIAN", "CONDUCT_MESSAGE_AGNOSTIC", "CONDUCT_MESSAGE_ILLITERATE", "CONDUCT_MESSAGE_WEAPONLESS"};
}


