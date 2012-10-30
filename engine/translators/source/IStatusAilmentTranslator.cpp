#include "IStatusAilmentTranslator.hpp"

using namespace std;

pair<string, Colour> IStatusAilmentTranslator::get_status_ailment(const CreaturePtr& c) const
{
  string description = get_status_ailment_text(c);
  Colour colour = get_status_ailment_colour(c);

  pair<string, Colour> status_ailment(description, colour);
  return status_ailment;
}

