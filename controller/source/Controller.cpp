#include "Controller.hpp"

using namespace std;

// Controllers are stateless.
bool Controller::serialize(ostream& stream)
{
  return true;
}

bool Controller::deserialize(istream& stream)
{
  return true;
}

