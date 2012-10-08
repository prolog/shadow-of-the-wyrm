#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "ITimeObserver.hpp"
#include "Serialize.hpp"

using namespace std;

ITimeObserver::ITimeObserver()
: minutes_elapsed(0), id(generate_id())
{
}

// Generate an ID using boost's facilities.
string ITimeObserver::generate_id()
{
  boost::uuids::uuid uuid_id = boost::uuids::random_generator()();
  return Uuid::to_string(uuid_id);
}

string ITimeObserver::get_id() const
{
  return id;
}

void ITimeObserver::update_minutes_elapsed(const ulonglong new_minutes_elapsed)
{
  minutes_elapsed += new_minutes_elapsed;
}

bool ITimeObserver::serialize(ostream& stream)
{
  Serialize::write_ulonglong(stream, minutes_elapsed);
  Serialize::write_string(stream, id);

  return true;
}

bool ITimeObserver::deserialize(istream& stream)
{
  Serialize::read_ulonglong(stream, minutes_elapsed);
  Serialize::read_string(stream, id);

  return true;
}

ClassIdentifier ITimeObserver::internal_class_identifier() const
{
  return CLASS_ID_TIME_OBSERVER;
}