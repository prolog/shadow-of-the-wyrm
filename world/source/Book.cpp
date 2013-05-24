#include "Book.hpp"
#include "Serialize.hpp"

using namespace std;

Book::Book()
{
  type = ITEM_TYPE_BOOK;
  symbol = '\"';
}

Book::~Book()
{
}

bool Book::operator==(const Book& rhs) const
{
  bool result = Readable::operator==(rhs);

  result = result && (spell_id == rhs.spell_id);

  return result;
}

bool Book::destroy_on_read() const
{
  return false;
}

void Book::set_spell_id(const string& new_spell_id)
{
  spell_id = new_spell_id;
}

string Book::get_spell_id() const
{
  return spell_id;
}

Item* Book::clone()
{
  return new Book(*this);
}

bool Book::serialize(ostream& stream)
{
  Readable::serialize(stream);

  Serialize::write_string(stream, spell_id);

  return true;
}

bool Book::deserialize(istream& stream)
{
  Readable::deserialize(stream);

  Serialize::read_string(stream, spell_id);

  return true;
}

ClassIdentifier Book::internal_class_identifier() const
{
  return CLASS_ID_BOOK;
}

#ifdef UNIT_TESTS
#include "unit_tests/Book_test.cpp"
#endif

