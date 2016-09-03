#include "Marks.hpp"
#include "Serialize.hpp"

using namespace std;

Marks::Marks()
: marks(0)
{
}

Marks::Marks(const int new_marks)
: marks(new_marks)
{
}

bool Marks::operator==(const Marks& m) const
{
  return (marks == m.marks);
}

void Marks::set_value(const int new_marks)
{
  marks = new_marks;
}

int Marks::get_value() const
{
  return marks;
}

void Marks::incr()
{
  marks = marks + 1;
}

bool Marks::serialize(ostream& stream) const
{
  Serialize::write_int(stream, marks);
  return true;
}

bool Marks::deserialize(istream& stream)
{
  Serialize::read_int(stream, marks);
  return true;
}

ClassIdentifier Marks::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MARKS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Marks_test.cpp"
#endif