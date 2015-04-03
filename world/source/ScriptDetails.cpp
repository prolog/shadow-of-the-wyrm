#include "ScriptDetails.hpp"
#include "Serialize.hpp"

using namespace std;

ScriptDetails::ScriptDetails(const string& new_script, const int new_chance)
: script(new_script), chance(new_chance)
{
}

ScriptDetails::ScriptDetails()
: chance(0)
{
}

bool ScriptDetails::operator==(const ScriptDetails& sd) const
{
  bool result = true;

  result = result && (script == sd.get_script());
  result = result && (chance == sd.get_chance());

  return result;
}

void ScriptDetails::set_script(const string& new_script)
{
  script = new_script;
}

string ScriptDetails::get_script() const
{
  return script;
}

void ScriptDetails::set_chance(const int new_chance)
{
  chance = new_chance;
}

int ScriptDetails::get_chance() const
{
  return chance;
}

bool ScriptDetails::serialize(ostream& stream) const
{
  Serialize::write_string(stream, script);
  Serialize::write_int(stream, chance);

  return true;
}

bool ScriptDetails::deserialize(istream& stream)
{
  Serialize::read_string(stream, script);
  Serialize::read_int(stream, chance);

  return true;
}

ClassIdentifier ScriptDetails::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCRIPT_DETAILS;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScriptDetails_test.cpp"
#endif