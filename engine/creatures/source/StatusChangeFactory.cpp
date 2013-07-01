#include <boost/make_shared.hpp>
#include "StatusChangeFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

StatusChangeFactory::StatusChangeFactory()
{
}

StatusChangeFactory::~StatusChangeFactory()
{
}

StatusChangePtr StatusChangeFactory::create_status_change(const string& status_id)
{
  StatusChangePtr status_change;

  if (status_id == StatusIdentifiers::STATUS_ID_POISON)
  {
    // JCD FIXME...
  }
  else
  {
    // Default case - this basically does nothing for each callable
    // method.
    status_change = boost::make_shared<StatusChange>();
  }

  return status_change;
}
