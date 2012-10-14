#include "Trap.hpp"

using namespace std;

Trap::Trap()
{
}

bool Trap::serialize(std::ostream& stream)
{
  return true;
}

bool Trap::deserialize(istream& stream)
{
  return true;
}

ClassIdentifier Trap::internal_class_identifier() const
{
  return CLASS_ID_TRAP;
}