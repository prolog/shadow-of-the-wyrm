#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "ITimeObserver.hpp"

using std::string;

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

void ITimeObserver::update_minutes_elapsed(const int new_minutes_elapsed)
{
  minutes_elapsed += new_minutes_elapsed;
}
