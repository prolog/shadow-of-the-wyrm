#include <sstream>
#include "DeathDumper.hpp"

using namespace std;

DeathDumper::DeathDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string DeathDumper::str() const
{
  ostringstream ss;

  if (creature != nullptr)
  {
    // ...
  }

  return ss.str();
}

