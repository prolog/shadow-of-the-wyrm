#include "Readable.hpp"
#include "Serialize.hpp"

using namespace std;

Readable::Readable()
: Item()
{
  readable = true;
}

Readable::~Readable()
{
}

bool Readable::operator==(const Readable& r) const
{
  bool result = true;

  result = result && Item::operator==(r);
  result = result && (text_sid == r.text_sid);

  return result;
}

void Readable::set_text_sid(const string& new_text_sid)
{
  text_sid = new_text_sid;
}

string Readable::get_text_sid() const
{
  return text_sid;
}

bool Readable::serialize(ostream& stream) const
{
  Item::serialize(stream);
  Serialize::write_string(stream, text_sid);

  return true;
}

bool Readable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_string(stream, text_sid);

  return true;
}
