#include "AgeTimeObserver.hpp"

using std::string;

AgeTimeObserver::AgeTimeObserver()
{
}

void AgeTimeObserver::notify(const ulonglong minutes_passed)
{
  // ...
}

ITimeObserver* AgeTimeObserver::clone() 
{
  return new AgeTimeObserver(*this);
}

ClassIdentifier AgeTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AGE_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/AgeTimeObserver_test.cpp"
#endif

