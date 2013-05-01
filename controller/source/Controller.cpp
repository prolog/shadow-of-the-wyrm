#include "Controller.hpp"

using namespace std;

// Just check the class identifier.
bool Controller::operator==(const Controller& c) const
{
  return (internal_class_identifier() == c.internal_class_identifier());
}

// Controllers are stateless.
bool Controller::serialize(ostream& stream)
{
  return true;
}

bool Controller::deserialize(istream& stream)
{
  return true;
}

