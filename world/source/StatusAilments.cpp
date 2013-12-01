#include "StatusAilments.hpp"
#include "Serialize.hpp"

using namespace std;

StatusAilments::StatusAilments()
: override_defaults(false)
{
}

bool StatusAilments::operator==(const StatusAilments& sa) const
{
  bool match = true;

  match = match && (override_defaults == sa.override_defaults);
  match = match && (ailments          == sa.ailments         );

  return match;
}

void StatusAilments::set_override_defaults(const bool new_override_defaults)
{
  override_defaults = new_override_defaults;
}

bool StatusAilments::get_override_defaults() const
{
  return override_defaults;
}

void StatusAilments::set_ailments(const set<string>& new_ailments)
{
  ailments = new_ailments;
}

set<string> StatusAilments::get_ailments() const
{
  return ailments;
}

bool StatusAilments::serialize(ostream& stream) const
{
  Serialize::write_bool(stream, override_defaults);
  Serialize::write_string_set(stream, ailments);

  return true;
}

bool StatusAilments::deserialize(istream& stream)
{
  Serialize::read_bool(stream, override_defaults);
  Serialize::read_string_set(stream, ailments);

  return true;
}

ClassIdentifier StatusAilments::internal_class_identifier() const
{
  return CLASS_ID_STATUS_AILMENTS;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatusAilments_test.cpp"
#endif